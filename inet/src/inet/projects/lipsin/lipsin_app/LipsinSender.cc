/*
 * lipsinapp.cc
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#include <fstream>
#include "LipsinSender.h"
#include "inet/common/Protocol.h"
#include "inet/common/packet/Packet.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/projects/lipsin/lipsin_packets/BloomFilter.h"
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"
#include "inet/projects/lipsin/lipsin_packets/LipsinHeader_m.h"
#include "inet/projects/lipsin/const_vars/LipsinConstVar.h"
#include "inet/projects/lipsin/lipsin_operator_reload/LipsinOperatorReload.h"
#include "inet/projects/lipsin/lipsin_optimal_encoding/lipsin_optimal_encoding.h"

namespace inet {
    Define_Module(LipsinSender);


    /**
     * lipsin destructor
     */
    LipsinSender::~LipsinSender(){
        if(this->sendTimer!=nullptr){
            if(this->sendTimer->isSelfMessage()){
                if(this->sendTimer->isScheduled()){
                    this->cancelEvent(this->sendTimer);
                }
            }
            delete sendTimer;
        }
        for(auto item : this->multicastGroups){
            delete item.second;
        }
    }

    /**
     * lipsin finish - write the statistic to the file
     */
    void LipsinSender::finish() {
        // if no response packet received, we do not need to write the statistics
        if (this->transmissionPattern == TransmissionPattern::UNICAST) {
            std::stringstream ss;
            std::ofstream countFile;
            ss << "received packet count: " << this->recorder->packetReceivedCount << std::endl;
            ss << "received packet size: " << this->recorder->totalReceivedSize << " Bytes" << std::endl;
            ss << "throughput: " << this->recorder->throughput << " Mbps" << std::endl;
            ss << "ratio: " << this->recorder->transmissionRatio << " %" << std::endl;
            ss << "total delay: " << this->recorder->sumDelay << " s" << std::endl;
            ss << "average delay: " << this->recorder->averageDelay << " s" << std::endl;
            std::string outputFileName = this->getParentModule()->getFullName() + std::string("_sender") + std::string("_statistic.txt");
            countFile.open(outputFileName, std::ios::out | std::ios::trunc);
            countFile.write(ss.str().c_str(), int(ss.str().length()));
            countFile.close();
        } else if ((this->transmissionPattern == TransmissionPattern::MULTI_UNICAST) ||
                   (this->transmissionPattern == TransmissionPattern::MULTICAST)) {
            // we should record the packet we send
            std::stringstream ss;
            std::ofstream countFile;
            ss << "send packet number: " << this->recorder->packetSentCount << std::endl;
            std::string outputFileName = this->getParentModule()->getFullName() + std::string("_sender") +std::string("_statistic.txt");
            countFile.open(outputFileName, std::ios::out | std::ios::trunc);
            countFile.write(ss.str().c_str(), int(ss.str().length()));
        } else {
            throw cRuntimeError("unknown transmission pattern"); // NOLINT
        }
    }
    /**
     * load destination satellites xml
     */
    void LipsinSender::loadDestinationSatellitesXml() {
        if (strcmp(this->destinationSatellitesXml->getTagName(), "Satellites") != 0) {
            throw cRuntimeError("LipsinSender::loadDestinationSatellitesXml: wrong xml tag name: %s", // NOLINT
                                destinationSatellitesXml->getTagName());
        } else {
            // get the inside tags of the top tag
            cXMLElementList sourceSatelliteTags = this->destinationSatellitesXml->getChildren();
            // traverse the satellite tag
            for(auto sourceSatelliteTag : sourceSatelliteTags){
                int tagSatId = std::stoi(LipsinTools::getStrAttr(*sourceSatelliteTag, "id"));
                // only handle the satellites
                if(tagSatId == this->satelliteId){
                    // judge the children tag name
                    cXMLElement* innerTag = sourceSatelliteTag->getFirstChild();
                    std::string innerTagName = innerTag->getTagName();
                    // judge the name of the child
                    if(innerTagName == LipsinConstVar::DESTINATION_TAG_NAME){
                        for(auto destinationSatelliteTag : sourceSatelliteTag->getChildren()){
                            int destinationSatelliteId = std::stoi(destinationSatelliteTag->getNodeValue());
                            this->destinationSatelliteIds.push_back(destinationSatelliteId);
                        }
                        break;
                    } else if(innerTagName == LipsinConstVar::MULTICAST_GROUP_TAG_NAME){
                        for(auto multicastGroupTag : sourceSatelliteTag->getChildren()){
                            // create a vector to store destination list
                            auto* destinationList = new std::vector<int>();
                            std::string multicastGroupName = LipsinTools::getStrAttr(*multicastGroupTag, "name");
                            for(auto destinationSatelliteTag : multicastGroupTag->getChildren()){
                                int destinationSatelliteId = std::stoi(destinationSatelliteTag->getNodeValue());
                                destinationList->push_back(destinationSatelliteId);
                                this->destinationSatelliteIds.push_back(destinationSatelliteId);
                            }
                            this->multicastGroups[multicastGroupName] = destinationList;
                        }
                    }
                }
            }
        }
    }



    /**
     * lipsin initialize
     * @param stage the stage of the initialization
     */
    void LipsinSender::initialize(int stage){
        // there are so many stages, we only setting our parameters in the local stage
        if(stage == INITSTAGE_LOCAL){
            this->setCurrentSatelliteIdAndName();
            this->packetLength = int(this->par("packetLength").intValue());
            this->startTime = this->par("startTime").doubleValue();
            this->stopTime = this->par("stopTime").doubleValue();
            this->sendInterval = this->par("sendInterval").doubleValue();
            this->destinationSatellitesXml = this->par("destinationSatellites");
            this->loadDestinationSatellitesXml();
            this->bloomFilterSize = int(this->par("bloomFilterSize").intValue());
            this->numberOfHashFunctions = int(this->par("numberOfHashFunctions").intValue());
            this->sendTimer = new cMessage("sendTimer");
            this->singleTimeEncapsulationCount = int(this->getParentModule()->par("singleTimeEncapsulationCount").intValue());
            this->enableOptimalEncoding = this->par("enableOptimalEncoding").boolValue();
            this->setLipsinRecorder();
            this->loadAvailableBloomFilterSeed();
            this->setLinkInfoTable();
            this->setTransmissionPattern();
            this->setMulticastPattern();
            this->registerLipsinSenderProtocols();
            this->start();
        } else if (stage == INITSTAGE_LAST)
        {
            this->addWatches();
        }
    }

    void LipsinSender::setMulticastPattern() {
        std::string multicastPatternTmp = this->par("multicastPattern").stringValue();
        if(multicastPatternTmp == "PRIMARY"){
            this->multicastPattern = MulticastPattern::PRIMARY;
        } else if(multicastPatternTmp == "SPF"){
            this->multicastPattern = MulticastPattern::SPF;
        } else{
            throw cRuntimeError("unknown multicast pattern"); // NOLINT
        }
    }

    /**
     * set transmission pattern
     */
    void LipsinSender::setTransmissionPattern(){
        // get the par
        std::string transmissionPatternStr = this->par("transmissionPattern").stringValue();
        if(transmissionPatternStr == "UNICAST"){
            this->transmissionPattern = TransmissionPattern::UNICAST;
        } else if(transmissionPatternStr == "MULTICAST"){
            this->transmissionPattern = TransmissionPattern::MULTICAST;
        } else if(transmissionPatternStr == "MULTI_UNICAST"){
            this->transmissionPattern = TransmissionPattern::MULTI_UNICAST;
        }
        else {
            throw cRuntimeError("unknow transmission pattern"); // NOLINT
        }
    }

    /**
     * register lipsin sender protocols
     */
    void LipsinSender::registerLipsinSenderProtocols() {
        registerProtocol(Protocol::lipsin_sender_app, gate("appOut"), gate("appIn"));
    }

    /**
     * add watch to the variables
     */
    void LipsinSender::addWatches() {
        WATCH_VECTOR(this->destinationSatelliteIds);
        WATCH_MAP(this->multicastGroups); // only support pointer
        WATCH(this->satelliteId);
        WATCH(this->satelliteName);
    }

    /**
     * set current satellite id and name
     */
    void LipsinSender::setCurrentSatelliteIdAndName() {
        this->satelliteName = this->getParentModule()->getFullName();
        this->satelliteId = LipsinTools::getSatelliteId(this->satelliteName);
    }

    /**
     * lipsin handle message
     * @param message the message to be handled
     */
    void LipsinSender::handleMessage(cMessage * message){
        if(message->isSelfMessage()){
            // handle timer
            handleTimer(message);
        } else if (message->arrivedOn("appIn")){
            // handle incoming packets
            handleResponsePacket(message);
        }
    }

    /**
     * lipsin handle timer
     * @param message the timer message
     */
    void LipsinSender::handleTimer(cMessage* message){
        // schedule the next packet sending
        if(message == this->sendTimer){
            double currentTime = simTime().dbl();
            if(this->stopTime > currentTime){
                std::vector<Packet*> generatedPackets = generateNewPackets();
                // traverse all the generated packets
                for(auto singlePacket : generatedPackets){
                    this->send(singlePacket, "appOut");
                    this->recorder->packetSentCount += 1;
                    if(this->emptyStoredBloomFilterSize){
                        this->currentBloomFilterSeed += 100;
                    } else {
                        this->currentBloomFilterSeed = this->recorder->storedBloomFilterSeed[(this->recorder->packetSentCount) % this->recorder->storedBloomFilterSeed.size()];
                        std::cout << this->currentBloomFilterSeed << std::endl;
                    }
                }
                this->scheduleAt(currentTime + this->sendInterval, this->sendTimer);
            }
        }
    }

    /**
     * lipsin handle response packet
     * @param message the response packet
     */
    void LipsinSender::handleResponsePacket(cMessage* message){
        // convert to the packet
        auto* packet = check_and_cast<Packet*>(message);
        // update recorder
        updateRecorder(packet);
        // delete the packet
        LipsinTools::delete_lipsin_packet(packet);
    }

    /**
     * lipsin start (for start sending packets)
     */
    void LipsinSender::start(){
        if(this->startTime < 0 || this->stopTime < 0 || (this->stopTime - this->startTime) <= 0){
            return;
        } else {
            this->scheduleAt(startTime, this->sendTimer);
        }
    }

    /**
     * generate new packet
     * @return the new generate packet
     */
    std::vector<Packet*> LipsinSender::generateNewPackets(){
        std::vector<Packet*> result = {};
        // judge the current transmission pattern
        if(this->transmissionPattern == TransmissionPattern::MULTICAST){
            if(this->multicastPattern == MulticastPattern::PRIMARY){
                // traverse the multicast groups
                for(const auto& item : this->multicastGroups){
                    auto* packet = new Packet(LipsinConstVar::LIPSIN_MULTICAST_PACKET_NAME.c_str());
                    // encapsulate the destination ids in single bloom filter
                    encapsulateLipsin(packet, *(item.second), LipsinConstVar::LIPSIN_MULTICAST_PACKET_TYPE);
                    // add protocol tag
                    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_sender_app); // set packet protocol
                    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::lipsin_network); // next layer protocol
                    // put the packet into the result
                    result.push_back(packet);
                }
                return result;
            } else if(this->multicastPattern == MulticastPattern::SPF){
                throw cRuntimeError("current not support this protocol"); // NOLINT
            }
            else {
                throw cRuntimeError("unknown multicast protocol"); // NOLINT
            }
        } else if(this->transmissionPattern == TransmissionPattern::MULTI_UNICAST){
            for(int currentDest : this->destinationSatelliteIds){
                std::vector<int> singleDestList = {currentDest};
                // create new packet
                auto* packet = new Packet(LipsinConstVar::LIPSIN_MULTI_UNICAST_PACKET_NAME.c_str());
                // encapsulate the current destination satellite id
                encapsulateLipsin(packet, singleDestList, LipsinConstVar::LIPSIN_MULTI_UNICAST_PACKET_TYPE);
                // add protocol payload
                packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_sender_app); // set packet protocol
                packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::lipsin_network); // next layer protocol
                // put the packet into the result
                result.push_back(packet);
            }
            return result;
        } else if(this->transmissionPattern == TransmissionPattern::UNICAST){
            int firstDestination = this->destinationSatelliteIds[0];
            std::vector<int> singleDestList = {firstDestination};
            auto* packet = new Packet(LipsinConstVar::LIPSIN_UNICAST_PACKET_NAME.c_str());
            encapsulateLipsin(packet, singleDestList, LipsinConstVar::LIPSIN_UNICAST_PACKET_TYPE);
            // add protocol payload
            packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_sender_app); // set packet protocol
            packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::lipsin_network); // next layer protocol
            // put the packet into the result
            result.push_back(packet);
            return result;
        } else {
            throw cRuntimeError("unknown transmission pattern hello"); // NOLINT
        }
    }

    void LipsinSender::addPayload(inet::Packet *packet) const {
        const auto& payload = makeShared<ByteCountChunk>(B(this->packetLength));
        packet->insertAtBack(payload);
    }

    void LipsinSender::encapsulateLipsin(Packet* packet, std::set<int> insertIds, std::vector<int> destinationIdList){
        // seed for the bloom filter
        int seed = 0;

        // create lipsin header
        const auto& lipsinHeader = makeShared<LipsinHeader>();

        // get lipsin routing table
        cModule* lipsinRoutingTableCmodule = this->getParentModule()->getSubmodule("lipsinRoutingTable");
        auto* lipsinRoutingTable = dynamic_cast<LipsinRoutingTable*>(lipsinRoutingTableCmodule);

        // set the packet type to indicate packet
        lipsinHeader->setPacketType(LipsinConstVar::LIPSIN_MULTICAST_PACKET_TYPE);

        // set the uuid in the packet
        std::string generateUuid = LipsinTools::generate_uuid();
        lipsinHeader->setUuid(generateUuid.c_str());

        lipsinHeader->setSource(this->getParentModule()->getFullName());
        lipsinHeader->setDestinationListArraySize(destinationIdList.size());
        for(int i = 0 ; i < destinationIdList.size(); i++){
            lipsinHeader->setDestinationList(i, destinationIdList[i]);
        }

        // generate nonce and set it
        lipsinHeader->setNonce(LipsinTools::generate_nonce());

        // create real lids bloom filter
        auto* realLidsBf = new BloomFilter(this->bloomFilterSize, this->numberOfHashFunctions, seed);
        lipsinHeader->setRealLidsBf(realLidsBf);

        for(auto linkId : insertIds){
            realLidsBf->insert(linkId);
        }

        // create virtual lids bloom filter
        auto* virtualLidsBf = new BloomFilter(this->bloomFilterSize, this->numberOfHashFunctions, seed);
        lipsinHeader->setVirtualLidsBf(virtualLidsBf);

        // create the path header
        auto* pathHeader = new PathHeader();
        lipsinHeader->setPathHeader(pathHeader);

        if((this->transmissionPattern == TransmissionPattern::MULTICAST) ||
           (this->transmissionPattern == TransmissionPattern::MULTI_UNICAST)){
            addPayload(packet);
        }

        packet->insertAtFront(lipsinHeader);
    }


    /**
     * encapsulate lipsin header
     * @param packet
     */
    void LipsinSender::encapsulateLipsin(Packet* packet, const std::vector<int>& destIds, int packetType) {
        // seed for the bloom filter
        int seed = this->currentBloomFilterSeed;

        // create lipsin Header
        const auto& lipsinHeader = makeShared<LipsinHeader>();

        // set start time
        lipsinHeader->setPacketCreatedTime(simTime().dbl());

        // set the packet type to indicate packet is (MUTLICAST | MULTIUNICAST | UNICAST | LSA)
        lipsinHeader->setPacketType(packetType);

        // set the uuid in the packet
        std::string generateUuid = LipsinTools::generate_uuid();
        lipsinHeader->setUuid(generateUuid.c_str());

        // set the packet source and packet destination
        // -------------------------------------------------------------
        lipsinHeader->setSource(this->getParentModule()->getFullName());
        lipsinHeader->setDestinationListArraySize(int(destIds.size()));
        for(int i = 0 ; i < destIds.size(); i++){
            lipsinHeader->setDestinationList(i, destIds[i]);
        }
        // -------------------------------------------------------------

        // generate nonce and set it
        // -------------------------------------------------------------
        lipsinHeader->setNonce(LipsinTools::generate_nonce());
        // -------------------------------------------------------------

        // create real lids bloom filter
        // ---------------------------------------------------------------------------------------------
        BloomFilter* realLidsBf = nullptr;
        // lipsinHeader->setRealLidsBf(realLidsBf);
        // ---------------------------------------------------------------------------------------------

        // create virtual lids bloom filter
        // ---------------------------------------------------------------------------------------------
        auto* virtualLidsBf = new BloomFilter(this->bloomFilterSize, this->numberOfHashFunctions, seed);
        lipsinHeader->setVirtualLidsBf(virtualLidsBf);
        // ---------------------------------------------------------------------------------------------

        // create the path header
        // ---------------------------------------------------------------------------------------------
        auto* pathHeader = new PathHeader();
        lipsinHeader->setPathHeader(pathHeader);
        // ---------------------------------------------------------------------------------------------

        // if transmission pattern equals to the TransmissionPattern::MULTICAST
        // we need to add the payload
        if((this->transmissionPattern == TransmissionPattern::MULTICAST) ||
        (this->transmissionPattern == TransmissionPattern::MULTI_UNICAST) || (this->transmissionPattern == TransmissionPattern::UNICAST)){
            addPayload(packet);
        }

        // get linkInfoTable
        // ---------------------------------------------------------------------------------------------
        cModule* lipsinRoutingTableCmodule = this->getParentModule()->getSubmodule("lipsinRoutingTable");
        auto* lipsinRoutingTable = dynamic_cast<LipsinRoutingTable*>(lipsinRoutingTableCmodule);
        // ---------------------------------------------------------------------------------------------

        // store routes
        std::vector<LinkInfo*> routes;

        // get the corresponding routes & insert the elements into the table
        // ---------------------------------------------------------------------------------------------
        // insert according too the current transmission pattern
        if(this->transmissionPattern == TransmissionPattern::MULTICAST){
            routes = lipsinRoutingTable->getMulticastRoutesByDestIds(destIds);
            // create real lids bloom filter
            // ---------------------------------------------------------------------------------------------
            realLidsBf = new BloomFilter(this->bloomFilterSize, this->numberOfHashFunctions, seed);
            lipsinHeader->setRealLidsBf(realLidsBf);
            // ---------------------------------------------------------------------------------------------
            // traverse the link info and insert them
            for(auto& link: routes){
                realLidsBf->insert(link->getId());
            }
        } else {
            // check if destIds.size() is larger than 1
            if(destIds.size() != 1){
                throw cRuntimeError("in END-TO-END or MULTI-UNICAST transmission pattern (destIds has only one id)"); // NOLINT
            }
            int singleDestinationId = destIds[0];
            routes = lipsinRoutingTable->getRouteForUnicast(singleDestinationId);
            // traverse the lipsinRoutingTable
            // std::cout << "max length: " << lipsinRoutingTable->findMaxLinkLength();
            // --------------------------optimal-encoding----------------------------------
            lipsinHeader->setChunkLength(b(this->bloomFilterSize));
            // calculate encoding nodes
            if(enableOptimalEncoding){

                std::deque<int> encapsulationHops = {};
                encapsulationHops = OptimalEncoding::calculateEncodingNodes(1000 * 8, this->numberOfHashFunctions, int(routes.size()), 10 * 1000 * 1000, 0.00001);
                pathHeader->encapsulationNodeCount = int(encapsulationHops.size());
                int encapsulationCount = encapsulationHops.front();
                encapsulationHops.pop_front();
                int nextIntermediateNode = routes[encapsulationCount-1]->getDest();
                // find optimal M for encapsulation Hops
                // int optimalM = OptimalEncoding::findOptimalM(1000*8, this->numberOfHashFunctions, encapsulationCount);
                // this->globalRecorder->optimizedBloomFilterSize = optimalM;
                // std::cout << "optimalM = " << optimalM << std::endl;
                // create real lids bloom filter
                // ---------------------------------------------------------------------------------------------
                realLidsBf = new BloomFilter(this->bloomFilterSize, this->numberOfHashFunctions, seed);
                lipsinHeader->setRealLidsBf(realLidsBf);
                // ---------------------------------------------------------------------------------------------
                while(!encapsulationHops.empty()){
                    int encapsulationCountTmp = encapsulationHops.front();
                    encapsulationHops.pop_front();
                    pathHeader->encodingPointVector->push_back(encapsulationCountTmp);
                }
                int i;
                for(i = 0; i < routes.size() ;i++){
                    if(i < encapsulationCount){
                        pathHeader->getSourceDecideLinkSetNonConst()->addLink(routes[i]);
                        realLidsBf->insert(routes[i]->getId());
                    } else {
                        break;
                    }
                }
                // encapsulate to the end
                if(i == routes.size()){
                    // set the intermediate node to negative
                    lipsinHeader->setIntermediateNode(-1);
                } else {
                    // lipsinHeader->setIntermediateNode(routes[i]->getSrc());
                    lipsinHeader->setIntermediateNode(nextIntermediateNode);
                }
            } else {
                // create real lids bloom filter
                // ---------------------------------------------------------------------------------------------
                // int optimalM = OptimalEncoding::findOptimalM(1000*8, this->numberOfHashFunctions, routes.size());
                // this->globalRecorder->optimizedBloomFilterSize = optimalM;
                pathHeader->encapsulationNodeCount = 1;
                realLidsBf = new BloomFilter(this->bloomFilterSize, this->numberOfHashFunctions, seed);
                lipsinHeader->setRealLidsBf(realLidsBf);
                lipsinHeader->setIntermediateNode(-1);
                // ---------------------------------------------------------------------------------------------
                // 遍历所有的路由条目并且添加到布隆过滤器和pathHeader之中去
                for(auto& link : routes){
                    pathHeader->getSourceDecideLinkSetNonConst()->addLink(link);
                    realLidsBf->insert(link->getId());
                }
            }
            // --------------------------optimal-encoding----------------------------------
        }
        // ---------------------------------------------------------------------------------------------

        // insert the lipsin header
        // ---------------------------------------------------------------------------------------------
        packet->insertAtFront(lipsinHeader);
        // ---------------------------------------------------------------------------------------------

        // print the bit set rate of this packet
        double bitSetRate = realLidsBf->getBitSetRate();
        this->recorder->sumBitSetRate += bitSetRate;

        // calculate real fpr
        auto linkInfoTableByIdMap = this->linkInfoTable->getLinkInfoTableById();
        int falsePositives = 0;
        double falsePositiveRate = 0;
        for(auto single_pair : linkInfoTableByIdMap){
            int tempLinkId = single_pair.second->getId();
            bool inserted = false;
            bool isFalsePositive = false;
            for(auto linkInfo  : routes){
                if(tempLinkId == linkInfo->getId()){
                    inserted = true;
                    break;
                }
            }
            if(!inserted){
                isFalsePositive = realLidsBf->query(tempLinkId);
                if(isFalsePositive){
                    falsePositives++;
                }
            }
        }

        falsePositiveRate = double(falsePositives) / double(linkInfoTableByIdMap.size());
        // std::cout << falsePositiveRate << std::endl;
        this->recorder->sumFalsePositiveRate += falsePositiveRate;
    }

    /**
     * update recorder
     * @param packet the packet to be updated
     */
    void LipsinSender::updateRecorder(Packet* packet){
        // get the lipsin header
        auto lipsinHeader = packet->peekAtFront<LipsinHeader>();
        // update the total delay
        this->recorder->sumDelay += simTime().dbl() - packet->getCreationTime().dbl();
        // update the average delay
        this->recorder->averageDelay = this->recorder->sumDelay / this->recorder->packetReceivedCount;
        // packet number increase
        this->recorder->packetReceivedCount++;
        // packet total size increase
        this->recorder->totalReceivedSize += int(packet->getByteLength());
        // update the throughput
        this->recorder->throughput = (this->recorder->totalReceivedSize * 8) / (simTime().dbl() - this->startTime) / 1000 / 1000;
        // update the transimissionRatio
        this->recorder->transmissionRatio = (double(this->recorder->packetReceivedCount) / double(this->recorder->packetSentCount)) * 100;
    }

    SendRecorder* LipsinSender::getSendRecorder(){
        return this->recorder;
    }

    void LipsinSender::setLipsinRecorder() {
        this->globalRecorder = dynamic_cast<LipsinGlobalRecorder*>(this->getSystemModule()->getSubmodule("lipsinGlobalRecorder"));
        this->globalRecorder->settedBloomFilterSize = this->bloomFilterSize;
    }

    std::string LipsinSender::getTransmissionPatternStr(){
        std::stringstream ss;
        if(this->transmissionPattern == TransmissionPattern::MULTICAST){
            ss << "Multicast";
        } else if(this->transmissionPattern == TransmissionPattern::MULTI_UNICAST){
            ss << "MultiUnicast";
        } else if(this->transmissionPattern == TransmissionPattern::UNICAST){
            ss << "Unicast";
        }
        if(this->singleTimeEncapsulationCount != -1){
            ss << " Optimal Encoding";
        } else {
            ss << " Source Encoding";
        }
        return ss.str();
    }

    void LipsinSender::setLinkInfoTable() {
        this->linkInfoTable = dynamic_cast<LinkInfoTable*>(this->getParentModule()->getSubmodule("linkInfoTable"));
    }

    void LipsinSender::loadAvailableBloomFilterSeed() {
        std::string line;
        std::ifstream file;
        std::string fileName = "bloom_filter_seed.txt";
        if(access(fileName.c_str(), 0) == -1){
            emptyStoredBloomFilterSize = true;
            return;
        }
        // 读取文件
        file.open(fileName, std::ios::in);
        while(std::getline(file, line)) {
            std::vector<std::string> lineSplit = LipsinTools::splitString(line, ',');
            for(const auto& item : lineSplit){
                this->recorder->storedBloomFilterSeed.push_back(std::atoi(item.c_str()));
            }
        }
        for(auto item : this->recorder->storedBloomFilterSeed){
            std::cout << item << ",";
        }

        std::cout << std::endl;
        file.close();
    }

} /* namespace inet */

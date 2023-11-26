/*
 * LipsinForwarder.cc
 *
 *  Created on: Sep 2, 2023
 *      Author: zhf
 */

#include "LipsinForwarder.h"
#include "inet/common/Protocol.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/networklayer/common/NetworkInterface.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/projects/lipsin/lipsin_table/LinkInfo.h"
#include "inet/projects/lipsin/lipsin_table/LipsinRoutingTable.h"
#include "inet/projects/lipsin/const_vars/LipsinConstVar.h"

namespace inet {
    Define_Module(LipsinForwarder);

    LipsinForwarder::~LipsinForwarder(){
        if(this->helloTimer != nullptr){
            if(this->helloTimer->isSelfMessage()) {
                cancelAndDelete(this->helloTimer);
            } else {
                delete this->helloTimer;
            }
        }
    }

    /**
     * initialize the module
     * @param stage current initialize stage
     */
    void LipsinForwarder::initialize(int stage){
        if(stage == INITSTAGE_LOCAL){
            registerService(Protocol::lipsin_network,gate("transportIn"),gate("transportOut"));
            registerProtocol(Protocol::lipsin_network,gate("queueOut"),gate("queueIn"));
            subscribeSignals();
            setLsaUp();
            setThreeTables();
            setLipsinRoutingTable();
            setLinkInfoTable();
            setCurrentSatelliteId();
            setGlobalRecorder();
            setSingleTimeEncapsulationCount();
            setLinkFailureMechanism();
        } else if (stage == INITSTAGE_LAST){
            if(this->lsaUp) {
                setLipsinNeighborsUp();
            }
            addWatches();
        }
    }

    void LipsinForwarder::finish(){
        this->lsaUp = false;
    }

    void LipsinForwarder::addWatches(){
        WATCH_MAP(this->neighborMap);
    }

    void LipsinForwarder::setLipsinNeighborsUp() {
        // get the linkInfos
        std::vector<LinkInfo*> linkInfos = this->linkInfoTable->getNodeLinkTable()[currentSatelliteId];
        // get containing module
        cModule* containingModule = this->getParentModule()->getParentModule();
        // set up the hello timer and hello interval
        this->helloTimer = new cMessage("helloTimer");
        this->helloInterval = int(this->par("helloInterval").intValue());
        // add neighbors
        for(auto linkInfo : linkInfos){
            // create new LipsinNeighbor
            auto newLipsinNeighbor = new LipsinNeighbor(linkInfo, containingModule, this->helloInterval);
            this->neighborMap[linkInfo->getId()] = newLipsinNeighbor;
        }
        // schedule the hello time
        this->scheduleAt(simTime(), this->helloTimer);
    }

    void LipsinForwarder::setLsaUp() {
        this->lsaUp = int(this->par("lsaUp").intValue());
    }

    /**
     * set up the linkInfoTable
     */
    void LipsinForwarder::setLinkInfoTable() {
        this->linkInfoTable = dynamic_cast<LinkInfoTable*>(this->getParentModule()->getParentModule()->getSubmodule("linkInfoTable"));
    }

    /**
     * set up the lipsin routing table
     */
    void LipsinForwarder::setLipsinRoutingTable() {
        this->lipsinRoutingTable = dynamic_cast<LipsinRoutingTable*>(this->getParentModule()->getParentModule()->getSubmodule("lipsinRoutingTable"));
    }

    /**
     * set up the link failure mechanism (BACKUPLINK | REROUTING)
     */
    void LipsinForwarder::setLinkFailureMechanism(){
        std::string linkFailureMachismStr = this->par("linkFailureMechanism").stringValue();
        if(linkFailureMachismStr == LipsinConstVar::LINK_FAILURE_MECHANISM_BACKUPLINK){
            this->linkFailureMechanism = LinkFailureMechanism::BACKUPLINK;
        } else if(linkFailureMachismStr == LipsinConstVar::LINK_FAILURE_MECHANISM_REROUTING){
            this->linkFailureMechanism = LinkFailureMechanism::REROUTING;
        } else if(linkFailureMachismStr == LipsinConstVar::LINK_FAILURE_MECHANISM_DIRECT_FORWARDING){
            this->linkFailureMechanism = LinkFailureMechanism::DIRECT_FORWARDING;
        }
        else {
            throw cRuntimeError("unknown link failure mechanism"); // NOLINT
        }
    }

    /**
     * set up the global recorder
     */
    void LipsinForwarder::setGlobalRecorder(){
        this->globalRecorder = dynamic_cast<LipsinGlobalRecorder*>(this->getParentModule()->getParentModule()->getParentModule()->getSubmodule("lipsinGlobalRecorder"));
    }

    /**
     * set the current satellite id
     */
    void LipsinForwarder::setCurrentSatelliteId() {
        std::string current_satellite_name = this->getParentModule()->getParentModule()->getFullName();
        this->currentSatelliteId = LipsinTools::getSatelliteId(current_satellite_name);
    }

    /**
     * set the single time encapsulation count
     */
    void LipsinForwarder::setSingleTimeEncapsulationCount() {
        this->singleTimeEncapsulationCount = int(this->getParentModule()->getParentModule()->par("singleTimeEncapsulationCount").intValue());
    }

    /**
     * subscribe the signals
     */
    void LipsinForwarder::subscribeSignals() {
        cModule* satelliteModule = this->getParentModule()->getParentModule();
        satelliteModule->subscribe(interfaceStateChangedSignal, this);
    }

    /**
     * initialize the three tables
     */
    void LipsinForwarder::setThreeTables() {
        auto* pltCmodule = this->getParentModule()->getSubmodule("plt");
        auto* physicalLinkTable = dynamic_cast<LipsinLinkTable*>(pltCmodule);
        auto* vltCmodule = this->getParentModule()->getSubmodule("vlt");
        auto* virtualLinkTable = dynamic_cast<LipsinLinkTable*>(vltCmodule);
        auto* dltCmodule = this->getParentModule()->getSubmodule("dlt");
        auto* downLinkTable = dynamic_cast<LipsinLinkTable*>(dltCmodule);
        this->plt = physicalLinkTable;
        this->vlt = virtualLinkTable;
        this->dlt = downLinkTable;
    }

    /**
     * handle the message
     * @param message the message received
     */
    void LipsinForwarder::handleMessage(cMessage * message){
        if(message->isSelfMessage()){
            this->handleTimer(message);
        } else if (message->arrivedOn("transportIn")){
            handlePacketFromHighLayer(message);
        } else if (message->arrivedOn("queueIn")){
            handlePacketFromLowLayer(message);
        } else {
            LipsinTools::module_log(this, "received unknown message");
        }
    }

    void LipsinForwarder::handleTimer(cMessage* timer){
        if(timer == this->helloTimer){
            // traverse all the interfaces to send hello packet
            for(auto entry : this->neighborMap){
                // get the lipsin neighbor
                LipsinNeighbor* lipsinNeighbor = std::get<1>(entry);
                // check if the neighbor reach router dead interval
                lipsinNeighbor->checkNeighborReachedRouterDeadInterval();
                // judge the state of lipsin neighbor
                bool isInterfaceUp = lipsinNeighbor->correspondingLinkInfo->getNetworkInterface()->isUp();
                if(!isInterfaceUp){
                    continue;
                }
                // generate the packet
                Packet* generatedHelloPacket = lipsinNeighbor->generateHelloPacket();
                // send the packet out
                this->send(generatedHelloPacket, "queueOut");
            }
            // schdule the next hello sending event
            this->scheduleAt(simTime().dbl()+this->helloInterval, this->helloTimer);
        }
    }

    /**
     * handle packet transmit from the application layer
     * @param message the packet received
     */
    void LipsinForwarder::handlePacketFromHighLayer(cMessage * message){
        // convert the message to the packet
        auto packet = check_and_cast<Packet *>(message);

        // remove the tag (protocol tag and dispatch tag added in the application layer)
        // -----------------------------------------------------------------------------
        packet->removeTag<PacketProtocolTag>();
        packet->removeTag<DispatchProtocolReq>();
        // -----------------------------------------------------------------------------

        if(this->linkFailureMechanism == LinkFailureMechanism::BACKUPLINK){
            // get the (lipsinheader, realBf, virtualBf, pathheader) from the packet
            // -------------------------------------------------------------------------------------
            auto lipsinHeaderOld = packet->peekAtFront<LipsinHeader>();
            auto* oldRealLidsBf = const_cast<BloomFilter *>(lipsinHeaderOld->getRealLidsBf());
            auto* oldVirtualLidsBf = const_cast<BloomFilter *>(lipsinHeaderOld->getVirtualLidsBf());
            auto* pathHeaderOld = lipsinHeaderOld->getPathHeader();
            // -------------------------------------------------------------------------------------

            // first we need to traverse the down link table and update bloom filter
            std::set<int> dontForwardInterfaceIds = traverseDownLinkTableAndUpdateBf(oldRealLidsBf, oldVirtualLidsBf);


            // second we need to traverse the physical lipsin link table and forward the packet
            // -----------------------------------------------------------------------------------------
            std::vector<LinkInfo*> pltEntries = plt->findOutputLinkIdentifiers(oldRealLidsBf);
            traverseAndForwardPackets(pltEntries, -1, lipsinHeaderOld,
                                      const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);
            // -----------------------------------------------------------------------------------------


            // finally we will traverse the virtual link table to forward the packet
            // -----------------------------------------------------------------------------------------
            std::vector<LinkInfo*> vltEntries = vlt->findOutputLinkIdentifiers(oldVirtualLidsBf);
            traverseAndForwardPackets(vltEntries, -1, lipsinHeaderOld,
                                      const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);
            // -----------------------------------------------------------------------------------------
        } else if (this->linkFailureMechanism == LinkFailureMechanism::REROUTING){
            // get the lipsin header and the bloom filter in the header
            auto lipsinHeaderOld = packet->peekAtFront<LipsinHeader>();
            auto* oldRealLidsBf = const_cast<BloomFilter *>(lipsinHeaderOld->getRealLidsBf());
            auto* pathHeaderOld = lipsinHeaderOld->getPathHeader();
            // traverse the interface table
            traverseDownLinkTableAndRerouting(lipsinHeaderOld, oldRealLidsBf);
            // second we need to traverse the physical lipsin link table and forward the packet
            // -----------------------------------------------------------------------------------------
            std::vector<LinkInfo*> pltEntries = plt->findOutputLinkIdentifiers(oldRealLidsBf);
            std::set<int> dontForwardInterfaceIds = {};
            traverseAndForwardPackets(pltEntries, -1, lipsinHeaderOld,
                                      const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);
            // -----------------------------------------------------------------------------------------
        } else if(this->linkFailureMechanism == LinkFailureMechanism::DIRECT_FORWARDING){
            // get the lipsin header and the bloom filter in the header
            auto lipsinHeaderOld = packet->peekAtFront<LipsinHeader>();
            auto* oldRealLidsBf = const_cast<BloomFilter *>(lipsinHeaderOld->getRealLidsBf());
            auto* pathHeaderOld = lipsinHeaderOld->getPathHeader();
            // second we need to traverse the physical lipsin link table and forward the packet
            // -----------------------------------------------------------------------------------------
            std::vector<LinkInfo*> pltEntries = plt->findOutputLinkIdentifiers(oldRealLidsBf);
            std::set<int> dontForwardInterfaceIds = {};
            traverseAndForwardPackets(pltEntries, -1, lipsinHeaderOld,
                                      const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);
            // -----------------------------------------------------------------------------------------
        } else {
            throw cRuntimeError("unknown link failure mechanism"); // NOLINT
        }
        // we need to delete original packet
        LipsinTools::delete_lipsin_packet(packet);
    }

    /**
     * handle the packet from the low layer
     * @param message the message received
     */
    void LipsinForwarder::handlePacketFromLowLayer(omnetpp::cMessage *message) {

        // record the total forwarding directions & upload to the application layer
        bool uploadToTheApplicationLayer = false;
        int totalForwardDirections = 0;

        // convert the message to the packet and get the lipsin header
        auto packet = check_and_cast<Packet *>(message);

        // get the packet name
        std::string packetName = packet->getName();

        // get the incoming interface
        auto incomingInterfaceId = packet->getTag<InterfaceInd>()->getInterfaceId();

        // get the original lipsin header
        auto lipsinHeaderOld = packet->removeAtFront<LipsinHeader>();

        // get the packet type
        int packetType = lipsinHeaderOld->getPacketType();
        if((packetType != LipsinConstVar::LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_TYPE) && (packetType != LipsinConstVar::LIPSIN_HELLO_PACKET_TYPE)){
            auto* oldRealLidsBf = const_cast<BloomFilter *>(lipsinHeaderOld->getRealLidsBf());

            // check if current node is the intermediate node
            // ------------------------------------------------------------------------------
            int packetIndicateIntermediateNode = lipsinHeaderOld->getIntermediateNode();
            if(packetIndicateIntermediateNode == this->currentSatelliteId){
                // reset the bloom filter
                oldRealLidsBf->reset();
                // we need to insert more link identifiers into the packets
                std::vector<LinkInfo*> routes = lipsinRoutingTable->getSourceRoutesByDestId(lipsinHeaderOld->getDestinationList(0));
                int i;
                for(i = 0; i < routes.size() ;i++){
                    if(i < this->singleTimeEncapsulationCount){
                        oldRealLidsBf->insert(routes[i]->getId());
                    } else {
                        break;
                    }
                }
                // encapsulate to the end
                if(i == routes.size()){
                    // set the intermediate node to negative
                    lipsinHeaderOld->setIntermediateNode(-1);
                } else {
                    lipsinHeaderOld->setIntermediateNode(routes[i]->getSrc());
                }
            }
            packet->insertAtFront(lipsinHeaderOld);
            // ------------------------------------------------------------------------------

            // remove the tag in the old packet
            packet->removeTagIfPresent<PacketProtocolTag>();
            packet->removeTagIfPresent<DispatchProtocolReq>();

            if(this->linkFailureMechanism == LinkFailureMechanism::BACKUPLINK){
                // forward packet process
                // get the bloom filter in the old lipsin header
                auto* oldVirtualLidsBf = const_cast<BloomFilter *>(lipsinHeaderOld->getVirtualLidsBf());
                auto* pathHeaderOld = lipsinHeaderOld->getPathHeader();

                // first we need to traverse the down link table and update bloom filter
                std::set<int> dontForwardInterfaceIds = traverseDownLinkTableAndUpdateBf(oldRealLidsBf, oldVirtualLidsBf);

                // second we need to traverse the physical lipsin link table and forward the packet
                std::vector<LinkInfo*> pltEntries = plt->findOutputLinkIdentifiers(oldRealLidsBf);
                totalForwardDirections += traverseAndForwardPackets(pltEntries, incomingInterfaceId, lipsinHeaderOld,
                                                                    const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);



                // finally we will traverse the virtual link table to forward the packet
                std::vector<LinkInfo*> vltEntries = vlt->findOutputLinkIdentifiers(oldVirtualLidsBf);
                totalForwardDirections += traverseAndForwardPackets(vltEntries, incomingInterfaceId, lipsinHeaderOld,
                                                                    const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);
            } else if (this->linkFailureMechanism == LinkFailureMechanism::REROUTING){
                // forward packet process
                auto* pathHeaderOld = lipsinHeaderOld->getPathHeader();
                traverseDownLinkTableAndRerouting(lipsinHeaderOld, oldRealLidsBf);
                // second we need to traverse the physical lipsin link table and forward the packet
                // -----------------------------------------------------------------------------------------
                std::vector<LinkInfo*> pltEntries = plt->findOutputLinkIdentifiers(oldRealLidsBf);
                std::set<int> dontForwardInterfaceIds = {};
                totalForwardDirections += traverseAndForwardPackets(pltEntries, incomingInterfaceId, lipsinHeaderOld,
                                                                    const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);
                // -----------------------------------------------------------------------------------------
            } else if(this->linkFailureMechanism == LinkFailureMechanism::DIRECT_FORWARDING){
                // forward packet process
                auto* pathHeaderOld = lipsinHeaderOld->getPathHeader();
                // second we need to traverse the physical lipsin link table and forward the packet
                // -----------------------------------------------------------------------------------------
                std::vector<LinkInfo*> pltEntries = plt->findOutputLinkIdentifiers(oldRealLidsBf);
                std::set<int> dontForwardInterfaceIds = {};
                totalForwardDirections += traverseAndForwardPackets(pltEntries, incomingInterfaceId, lipsinHeaderOld,
                                                                    const_cast<PathHeader *>(pathHeaderOld), packet, dontForwardInterfaceIds);
                // -----------------------------------------------------------------------------------------
            } else {
                throw cRuntimeError("unknown link failure mechanism"); // NOLINT
            }
            // pass the packet to the upper layer
            if(this->checkIsDestination(lipsinHeaderOld)){
                // judge the app number
                if(this->getParentModule()->getParentModule()->par("hasLipsinReceiver").boolValue()){
                    // add the tag --> sender or receiver
                    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_app);
                    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::lipsin_app);
                    // set the uploadToTheApplicationLayer to true
                    uploadToTheApplicationLayer = true;
                    // transmit the packet to the upper layer
                    send(packet, "transportOut");
                }
            }

            // record the redundant forward count
            if((totalForwardDirections == 0) && (!uploadToTheApplicationLayer)){
                // get the global recorder
                auto* pathHeader = const_cast<PathHeader*>(lipsinHeaderOld->getPathHeader());
                int redundantForwardingHops = pathHeader->getActualLinkSet()->getLinkSetSize();
                this->globalRecorder->redundantForwardCount += redundantForwardingHops;
            }

            // if we don't need to pass the packet to the application layer
            // then we need to delete the packet
            if(!uploadToTheApplicationLayer){
                LipsinTools::delete_lipsin_packet(packet);
            }
        } else if(packetType == LipsinConstVar::LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_TYPE){
            // we need to recover the head
            packet->insertAtFront(lipsinHeaderOld);
            packet->removeTagIfPresent<DispatchProtocolReq>();
            packet->removeTagIfPresent<PacketProtocolTag>();
            packet->removeTagIfPresent<InterfaceReq>();
            // we need to analyze the packet first
            this->analyzeLsaPacket(lipsinHeaderOld);
            // -----------------create new packet and forward the packet to other interfaces-----------
            // traverse all the interfaces in plt
            for(auto linkInfo : plt->getInnerList()){
                if(linkInfo->getNetworkInterface()->getInterfaceId() == incomingInterfaceId){
                    continue;
                } else if(!linkInfo->getNetworkInterface()->isUp()){
                    continue;
                } else if(linkInfo->getNetworkInterface()->findNonce(lipsinHeaderOld->getNonce())){
                    continue;
                }
                else {
                    // create new packet
                    Packet *newPacket = packet->dup();
                    // remove the tag in the old packet
                    // copy the bloom filter and pathHeader
                    auto lipsinHeaderNew = newPacket->removeAtFront<LipsinHeader>();
                    BloomFilter* newRealLidsBloomFilter = lipsinHeaderOld->getRealLidsBf()->getCopy();
                    lipsinHeaderNew->setRealLidsBf(newRealLidsBloomFilter);
                    // copy the old virtual bloom filter to create new virtual bloom filter
                    BloomFilter* newVirtualLidsBloomFilter = lipsinHeaderOld->getVirtualLidsBf()->getCopy();
                    lipsinHeaderNew->setVirtualLidsBf(newVirtualLidsBloomFilter);
                    auto* newPathHeader = new PathHeader();
                    lipsinHeaderNew->setPathHeader(newPathHeader);
                    // add the tag
                    newPacket->addTagIfAbsent<InterfaceReq>()->setInterfaceId(linkInfo->getNetworkInterface()->getInterfaceId());
                    newPacket->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
                    newPacket->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_network);
                    // insert back the header
                    newPacket->insertAtFront(lipsinHeaderNew);
                    // send the packet out
                    this->send(newPacket, "queueOut");
                    // insert nonce
                    linkInfo->getNetworkInterface()->insertNonce(lipsinHeaderNew->getNonce());
                }
            }
            // -----------------forward the packet to other interfaces-----------

            // delete the packet
            LipsinTools::delete_lipsin_packet(packet);
        } else if(packetType == LipsinConstVar::LIPSIN_HELLO_PACKET_TYPE){
            // analyze the lipsinHeaderOld
            int neighborSatelliteId = LipsinTools::getSatelliteId(lipsinHeaderOld->getSource());
            // find the corresponding lipsin neighbor
            LinkInfo* correspondingLinkInfo = this->linkInfoTable->getLinkInfoTable()[std::make_tuple(this->currentSatelliteId, neighborSatelliteId)];
            LipsinNeighbor* correspondingLipsinNeighbor = this->neighborMap[correspondingLinkInfo->getId()];
            // update the packet received timer of hello packet
            correspondingLipsinNeighbor->lastTimeReceivedHelloPacket = simTime().dbl();
            // set the neighbor id
            correspondingLipsinNeighbor->neighborSatelliteId = neighborSatelliteId;
            // process the event
            bool twoWayReceived = (lipsinHeaderOld->getNeighborSatelliteId() == this->currentSatelliteId);
            if(twoWayReceived){
                correspondingLipsinNeighbor->processEvent(LipsinNeighborState::LipsinNeighborEventType::HELLO_WITH_MY_ID_RECEIVED);
            } else {
                correspondingLipsinNeighbor->processEvent(LipsinNeighborState::LipsinNeighborEventType::HELLO_WITHOUT_MY_ID_RECEIVED);
            }
            // reconstruct the packet
            packet->insertAtFront(lipsinHeaderOld);
            // delete the packet
            LipsinTools::delete_lipsin_packet(packet);
        }
    }

    /**
     * this function is used to analyze the header of the lsa packet
     * @param lipsinHeader
     */
    void LipsinForwarder::analyzeLsaPacket(const Ptr<LipsinHeader>& lipsinHeader){
        // first we need to check whether the packet is already been analyzed
        std::string uuid = lipsinHeader->getUuid();
        // if it is the first time we have this packet, we need to record that we have received this packet
        if(this->receivedLsaMap.find(uuid) == this->receivedLsaMap.end()){
            this->receivedLsaMap[uuid] = simTime().dbl();
            int generatorSatId = LipsinTools::getSatelliteId(lipsinHeader->getSource());
            std::vector<LinkInfo*> linkInfos = (this->linkInfoTable->getNodeLinkTable())[generatorSatId];
            // get the up bloom filters and down bloom filters
            BloomFilter* upLinkBf = lipsinHeader->getRealLidsBfNonConst();
            BloomFilter* downLinkBf = lipsinHeader->getVirtualLidsBfNonConst();
            // we need to traverse the linkInfos to test whether the link is
            for(auto linkInfo : linkInfos)
            {
                if(upLinkBf->query(linkInfo->getId())){
                    if(linkInfo->getState() != LinkState::UP){
                        this->linkInfoTable->updateLinkCostAndState(linkInfo, 1, LinkState::UP);
                    }
                }
                if(downLinkBf->query(linkInfo->getId())){
                    if(linkInfo->getState() != LinkState::DOWN){
                        this->linkInfoTable->updateLinkCostAndState(linkInfo, INT_MAX, LinkState::DOWN);
                    }
                }
            }
            // here we gonna add a judgement: if any update we need to recalculate the routing table
            if(linkInfoTable->isLinkUpdated){
                // recalculate the routing table
                linkInfoTable->reCalculateRouteByDijkstra();
            }
        } else {
            return;
        }
    }

    /**
     * check if the current satellite is the destination
     * @param lipsinHeader
     */
    bool LipsinForwarder::checkIsDestination(Ptr<const inet::LipsinHeader> lipsinHeader) const {
        bool result = false;
        // traverse the destination satellite id
        for(int i = 0; i < lipsinHeader->getDestinationListArraySize(); i++){
            // get single destination satellite id
            int destinationSatelliteId = lipsinHeader->getDestinationList(i);
            // check if the destination satellite id equals the current satellite id
            if(this->currentSatelliteId == destinationSatelliteId){
                result = true;
                break;
            }
        }
        return result;
    }

    void LipsinForwarder::traverseDownLinkTableAndRerouting(Ptr<const LipsinHeader> lipsinHeader, inet::BloomFilter *oldRealLidsBf) {  // NOLINT
        std::vector<LinkInfo*> dltEntries = dlt->getInnerList();
        bool containsDownLinkIdInReal = false;
        for(auto dltEntry : dltEntries){
            if(dltEntry->getLinkType() == LinkType::PHYSICAL){
                int currentDownPhysicalLinkId = dltEntry->getId();
                if(oldRealLidsBf->query(currentDownPhysicalLinkId)){
                    containsDownLinkIdInReal = true;
                    break;
                }
            }
        }
        // then we need to get the rerouting routes and used it to update the bloom filter
        if(containsDownLinkIdInReal){
            std::vector<int> destinationList = {};
            destinationList.reserve(lipsinHeader->getDestinationListArraySize());
            for(int index = 0;index < lipsinHeader->getDestinationListArraySize(); index++){
                destinationList.push_back(lipsinHeader->getDestinationList(index));
            }
            std::vector<LinkInfo*> routes = lipsinRoutingTable->getSourceRoutesByDestIds(destinationList);
            // reset the bloom filter
            oldRealLidsBf->reset();
            // insert the routes into the bloom filter
            for(auto route : routes){
                oldRealLidsBf->insert(route->getId());
            }
        }
    }

    /**
     * according to the down link table to update the bloom filter
     * @param oldRealLidsBf the old real lids bloom filter
     * @param oldVirtualLidsBf  the old virtual lids bloom filter
     */
    std::set<int> LipsinForwarder::traverseDownLinkTableAndUpdateBf(BloomFilter* oldRealLidsBf, // NOLINT
                                                           BloomFilter* oldVirtualLidsBf){
        std::set<int> dontForwardInterfaceIds = {};
        std::vector<LinkInfo*> dltEntries = dlt->getInnerList();
        for(auto dltEntry : dltEntries){
            // get the current down link entry id
            int currentDownLinkId = dltEntry->getId();
            // judge if the current lipsin header contains the down link id
            bool containsDownLinkIdInReal = oldRealLidsBf->query(currentDownLinkId);
            // if contains add corresponding virtual
            if(containsDownLinkIdInReal){
                // the LinkType is LinkType::Physical
                if(dltEntry->getLinkType() == LinkType::PHYSICAL){
                    oldVirtualLidsBf->insert(currentDownLinkId);
                    dontForwardInterfaceIds.insert(dltEntry->getNetworkInterface()->getInterfaceId());
                }
            }
            bool containsDownLinkIdInVirtual = oldVirtualLidsBf->query(currentDownLinkId);
            if(containsDownLinkIdInVirtual)
            {
                if(dltEntry->getLinkType() == LinkType::VIRTUAL){
                    // find the virtual link corresponding interface
                    NetworkInterface* networkInterface = dltEntry->getNetworkInterface();
                    // get the corresponding physical link id
                    auto result = plt->getLinkInfoVectorByInterface(networkInterface, LinkType::PHYSICAL);
                    if(!result.empty()){
                        dontForwardInterfaceIds.insert(networkInterface->getInterfaceId());
                        oldVirtualLidsBf->insert(result[0]->getId());
                    }
                }
            }
        }
        return dontForwardInterfaceIds;
    }

    /**
     * traverse the entries and forwarrd the packets
     * @param entries the entries may from plt or vlt
     * @param incomingInterfaceId the incoming interface id for loop prevention
     * @param lipsinHeaderOld the orginal lipsin header
     * @param pathHeaderOld the orginal path header
     * @param packet the orginal packet
     */
    int LipsinForwarder::traverseAndForwardPackets(std::vector<LinkInfo*> entries, // NOLINT
                                                    int incomingInterfaceId,
                                                    Ptr<const LipsinHeader> lipsinHeaderOld, // NOLINT
                                                    PathHeader* pathHeaderOld,
                                                    Packet* packet,
                                                    const std::set<int>& dontForwardInterfaceIds){
        int realForwardEntries = 0;
        for(auto entry: entries){

            if(dontForwardInterfaceIds.find(entry->getNetworkInterface()->getInterfaceId()) != dontForwardInterfaceIds.end()){
                continue;
            }

            // we will not send the packet back to the incoming interface
            // to prevent the follow case
            /*             5 - 6 - 9
             *             |   |   |
             * 1 - 2 - 3 - 4   7   8 - 10
             * the pre scudeduled route is (1->2)(2->3)(3->4)(4->7)(7->8)(8->10)
             * however the 4->7 link is down and 7->8 link is down
             * so the backup link 4->5->6->7 is activated, when packet reach node 7,
             * it need to forward to the packet to node 8 , but the link 7->8 is down,
             * it want to activate the backup link 7->6->9->8, however the packet will
             * not forward to the incoming interface, so the packet will be dropped.
             */
             if((incomingInterfaceId != -1) && (entry->getNetworkInterface()->getInterfaceId() == incomingInterfaceId)){
               continue;
             }

            // loop prevention
            if(entry->getNetworkInterface()->findNonce(lipsinHeaderOld->getNonce())){
                // LipsinTools::module_log(this,"loop prevention");
                continue;
            }

            // after the check before, the packet will definitely be forwarded
            realForwardEntries += 1;

            // copy the packet about to be forwarded
            Packet *newPacket = packet->dup();

            // add the tags to indicate the lower layer
            newPacket->addTagIfAbsent<InterfaceReq>()->setInterfaceId(entry->getNetworkInterface()->getInterfaceId());
            newPacket->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
            newPacket->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_network);

            // copy the old real bloom filter to create new real bloom filter
            auto lipsinHeaderNew = newPacket->removeAtFront<LipsinHeader>();
            BloomFilter* newRealLidsBloomFilter = lipsinHeaderOld->getRealLidsBf()->getCopy();
            lipsinHeaderNew->setRealLidsBf(newRealLidsBloomFilter);

            // copy the old virtual bloom filter to create new virtual bloom filter
            BloomFilter* newVirtualLidsBloomFilter = lipsinHeaderOld->getVirtualLidsBf()->getCopy();
            lipsinHeaderNew->setVirtualLidsBf(newVirtualLidsBloomFilter);

            // copy the old pathe header and add the forward link to create the new path header
            auto newPathHeader = new PathHeader(*(pathHeaderOld));
            newPathHeader->getActualLinkSet()->addLink(entry);
            lipsinHeaderNew->setPathHeader(newPathHeader);

            // insert back the lipsin header
            newPacket->insertAtFront(lipsinHeaderNew);

            // send out the packet
            this->send(newPacket, "queueOut");

            // set the nonce at corresponding interface
            entry->getNetworkInterface()->insertNonce(lipsinHeaderOld->getNonce());
        }
        return realForwardEntries;
    }

    /**
     * signal listener
     * @param source  the source emit the signal
     * @param signalID  the signal id
     * @param obj  the object transmit
     * @param details  the details of the object
     */
    void LipsinForwarder::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
        Enter_Method("receiveSignal");
        if (signalID == interfaceStateChangedSignal) {
            auto *changeDetails = dynamic_cast<NetworkInterfaceChangeDetails *>(obj);
            NetworkInterface *interface = changeDetails->getNetworkInterface();
            // interface from up to down
            if (!interface->isUp()) {
                // get the interface corresponding link from plt and vlt into dlt
                std::vector<LinkInfo *> pltDownLinkInfos = plt->getLinkInfoVectorByInterface(interface,
                                                                                             LinkType::PHYSICAL);
                // std::cout << "the size of the plt down link info: " << pltDownLinkInfos.size() << std::endl; this line always output 1
                // ----------------------we need to update the cost and recalculate routing table-------------------------------
                if (!pltDownLinkInfos.empty()) {
                    this->linkInfoTable->updateLinkCostAndState(pltDownLinkInfos[0], INT_MAX, LinkState::DOWN);
                    if (this->linkFailureMechanism == LinkFailureMechanism::REROUTING) {
                        this->linkInfoTable->reCalculateRouteByDijkstra();
                    }
                }
                // ----------------------we need to update the cost and recalculate routing table-------------------------------
                std::vector<LinkInfo *> vltDownLinkInfos = vlt->getLinkInfoVectorByInterface(interface,
                                                                                             LinkType::VIRTUAL);

                // add the link into the dlt
                for (auto linkInfo: pltDownLinkInfos) { dlt->addEntry(linkInfo); }
                for (auto linkInfo: vltDownLinkInfos) { dlt->addEntry(linkInfo); }

            }
            // interface from down to up
            else {
                // ----------------------we need to update the cost and recalculate routing table-------------------------------
                std::vector<LinkInfo *> downLinkInfo = plt->getLinkInfoVectorByInterface(interface, LinkType::PHYSICAL);
                linkInfoTable->updateLinkCostAndState(downLinkInfo[0], 1, LinkState::UP);
                if (this->linkFailureMechanism == LinkFailureMechanism::BACKUPLINK) {
                    linkInfoTable->reCalculateRouteByDijkstra();
                }
                // ----------------------we need to update the cost and recalculate routing table-------------------------------

                // remove the interface corresponding link from dlt
                dlt->removeLinkInfosByInterface(interface);
            }
            // we cannot have the global vision
            // if current linkFailureMechanism is LSA generation
            /*
            if(this->lsaUp == 1){
                // generate lsa packets
                std::vector<Packet*> generatedLsaPackets = generateLsaPackets(interface);
                // send the packets out
                for(auto lsaPacket : generatedLsaPackets){
                    // when finishing , all the interfaces will down, and we will send the lsa packet
                    this->send(lsaPacket, "queueOut");
                }
            }
             */
        }
    }

    /**
     * generate the link state announcement packet
     * @param changedInterface this is the state changed interface
     */
    std::vector<Packet*> LipsinForwarder::generateLsaPackets(NetworkInterface* changedInterface) { // NOLINT
        // bloom filter seed
        int seed = 0;
        // store the generated lsa packets
        std::vector<Packet*> lsaPackets = {};
        // find all the interfaces
        std::map<int, std::vector<LinkInfo*>> nodeLinkTable = this->linkInfoTable->getNodeLinkTable();
        // set nonce
        uint64_t nonce = LipsinTools::generate_nonce();
        for(auto link : nodeLinkTable[this->currentSatelliteId]){
            if(link->getNetworkInterface()->isUp()){
                auto* newLsaPacket = new Packet(LipsinConstVar::LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_NAME.c_str());
                // get the link info
                std::vector<LinkInfo *> downLinkInfo = plt->getLinkInfoVectorByInterface(changedInterface, LinkType::PHYSICAL);
                LinkInfo* changedLinkInfo = downLinkInfo[0];
                // ---------------------------------add tags-----------------------------------------------
                newLsaPacket->addTagIfAbsent<InterfaceReq>()->setInterfaceId(link->getNetworkInterface()->getInterfaceId());
                newLsaPacket->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
                newLsaPacket->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_network);
                // ---------------------------------add tags-----------------------------------------------

                // ---------------------------------encapsulate lipsin ------------------------------------
                const auto& lipsinHeader = makeShared<LipsinHeader>();
                lipsinHeader->setPacketType(LipsinConstVar::LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_TYPE);
                lipsinHeader->setUuid(LipsinTools::generate_uuid().c_str());
                lipsinHeader->setSource(this->getParentModule()->getParentModule()->getFullName());
                lipsinHeader->setNonce(nonce);
                auto* realLidsBf = new BloomFilter(40, 5, seed);
                lipsinHeader->setRealLidsBf(realLidsBf);
                auto* virtualLidsBf = new BloomFilter(40, 5, seed);
                lipsinHeader->setVirtualLidsBf(virtualLidsBf);
                auto* pathHeader = new PathHeader();
                lipsinHeader->setPathHeader(pathHeader);
                const auto& payload = makeShared<ByteCountChunk>(B(40));
                newLsaPacket->insertAtBack(payload);
                newLsaPacket->insertAtFront(lipsinHeader);
                // judge the interface type
                if(changedInterface->isUp()){
                    realLidsBf->insert(changedLinkInfo->getId());
                } else {
                    virtualLidsBf->insert(changedLinkInfo->getId());
                }
                // ---------------------------------encapsulate lipsin ------------------------------------
                lsaPackets.push_back(newLsaPacket);
                link->getNetworkInterface()->insertNonce(lipsinHeader->getNonce());
            }
        }
        // return the generated lsa packets
        return lsaPackets;
    }

} /* namespace inet */

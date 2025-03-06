//
// Created by 张贺凡 on 2024/5/4.
//
#include <sstream>
#include "inet/projects/sr/sr_app/SRSender.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/projects/sr/sr_packet/SRHeader_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"

namespace inet{
    Define_Module(SRSender);

    SRSender::~SRSender(){
        if(this->sendTimer != nullptr){
            if(this->sendTimer->isSelfMessage()){
                if(this->sendTimer->isScheduled()){
                    this->cancelEvent(this->sendTimer);
                }
            }
            delete sendTimer;
        }
    }

    /**
     * SRSender 的初始化器
     * @param stage 当前的初始化阶段
     */
    void SRSender::initialize(int stage){
        if(stage == INITSTAGE_LOCAL) {
            // -----------------      initialize the data     -----------------
            this->sendPacketCount = 0;
            // -----------------      initialize the data     -----------------
            // ----------------- read params from ini and ned -----------------
            this->startTime = this->par("startTime").doubleValue();
            this->stopTime = this->par("stopTime").doubleValue();
            this->sendInterval = this->par("sendInterval").doubleValue();
            this->packetLength = int(this->par("packetLength").intValue());
            this->destinationSatelliteId = int(this->par("destinationSatelliteId").intValue());
            // ----------------- read params from ini and ned -----------------
            // -----------------     initialize the timer     -----------------
            this->sendTimer = new cMessage("sendTimer");
            // -----------------     initialize the timer     -----------------
            // -----------------       register protocol      -----------------
            this->registerSRSenderProtocol();
            // -----------------       register protocol      -----------------
            // -----------------        resolve params        -----------------
            this->resolveTables();
            this->resolveCurrentSatelliteId();
            // -----------------        resolve params        -----------------
            // -----------------     schedule self message    -----------------
            this->startSendMessage();
            // -----------------     schedule self message    -----------------
        }
    }

    /**
     * resolveLipsinRoutingTable
     */
    void SRSender::resolveTables() {
        // resolve lipsin routing table
        cModule* satelliteModule = this->getParentModule();
        this->lipsinRoutingTable = dynamic_cast<LipsinRoutingTable*>(satelliteModule->getSubmodule("lipsinRoutingTable"));
        // resolve the physical link table
        this->plt = dynamic_cast<LipsinLinkTable*>(satelliteModule->getSubmodule("plt"));
    }

    /**
     * 解析当前卫星的id
     */
    void SRSender::resolveCurrentSatelliteId() {
        cModule* satelliteModule = this->getParentModule();
        std::string satelliteName = satelliteModule->getFullName();                                                  // get the containing modules's satellite name
        int currentSatelliteIdTmp = std::stoi(satelliteName.substr(satelliteName.find("SAT")+3, 5));     // extract the id from the satellite name
        this->currentSatelliteId = currentSatelliteIdTmp;
    }

    /**
     * 注册协议
     */
    void SRSender::registerSRSenderProtocol() {
        registerProtocol(Protocol::sr_sender_app, gate("appOut"), gate("appIn"));
    }

    /**
     * 处理自消息
     * @param message 自消息
     */
    void SRSender::handleMessage(cMessage* message){
        // handle sendTimer
        if(message->isSelfMessage())
        {
            this->handleSendTimer(message);
        }
    }

    /**
     * 处理数据包发送计时器
     * @param message 数据包发送计时器
     */
    void SRSender::handleSendTimer(cMessage* message){
        if(message == this->sendTimer){
            double currentSimTime = simTime().dbl();
            if(this->stopTime > currentSimTime){
                Packet* generatedPacket = this->generatePacket();
                this->send(generatedPacket, "appOut");
                this->scheduleAt(currentSimTime + this->sendInterval, this->sendTimer);
            }
        }
    }

    /**
     * 计划最开始的自消息
     */
    void SRSender::startSendMessage() {
        if((this->startTime < 0) || (this->stopTime < 0) || (this->stopTime < this->startTime) || (this->destinationSatelliteId == -1)){
            LipsinTools::module_log(this, "don't forward packet");
        } else {
            this->scheduleAt(this->startTime, this->sendTimer);
        }
    }

    /**
     * 产生数据包
     * @return
     */
    Packet* SRSender::generatePacket(){
        // generate packet name
        std::stringstream ss;
        ss << this->sendPacketCount << " SR packet sended by " << this->getParentModule()->getFullName();
        // create omnetpp packet
        auto* packet = new Packet(ss.str().c_str());
        // create sr packet
        this->createSRPacket(packet);
        // add payload
        this->addPayload(packet);
        // return the packet
        return packet;
    }


    /**
     * 为 packet 添加 SR 的头部
     * @param packet
     */
    void SRSender::createSRPacket(Packet* packet) {
        const auto& srHeader = makeShared<SRHeader>();                                                                 // create sr header
        int lengthOfRoute;
        std::vector<LinkInfo*> routeToDestination;
        int firstLinkIdentifier;
        srHeader->setSource_node_id(this->currentSatelliteId);                                                                             // set the current satellite id
        srHeader->setDestination_node_id(this->destinationSatelliteId);                                                                    // set the destination id
        routeToDestination = this->lipsinRoutingTable->getRouteForUnicast(this->destinationSatelliteId);                            // find the route to destination
        lengthOfRoute = int(routeToDestination.size());                                                                                    // get the length of route
        srHeader->setSidsArraySize(lengthOfRoute);                                                                                    // set the length into header
        for(int index = 0; index < lengthOfRoute; index++){                                                                                // traverse the routeToDestination
            srHeader->setSids(index, routeToDestination[index]->getId());
        }
        firstLinkIdentifier = routeToDestination[0]->getId();                                                                              // get first link identifier
        NetworkInterface* outputNetworkInterface = this->resolveOutputNetworkInterface(firstLinkIdentifier);                         // get the first link identifier corresponding interface
        packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(outputNetworkInterface->getInterfaceId());
        packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);                                            // set the mac address to BROADCAST
        packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::sr_sender_app);                                                // set the current protocol
        packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::sr_network);                                                 // set the deliver protocol
        srHeader->setSid_index(1);
        srHeader->setChunkLength(B(this->getSRV6PacketLengthInBytes(lengthOfRoute)));
        srHeader->setPacket_created_time(omnetpp::simTime().dbl());                                                                        // set the current time
        packet->insertAtBack(srHeader);                                                                                             // insert the header
    }

    /**
     * 为 packet 添加载荷
     * @param packet
     */
    void SRSender::addPayload(Packet* packet){
        const auto& payload = makeShared<ByteCountChunk>(B(this->packetLength));
        packet->insertAtBack(payload);
    }

    /**
     * 找到对应的出接口
     */
    NetworkInterface* SRSender::resolveOutputNetworkInterface(int linkId){
        NetworkInterface* outputNetworkInterface = nullptr;
        std::vector<LinkInfo*> pltLinkInfos = this->plt->getInnerList();
        for(auto* linkInfo : pltLinkInfos){  // traverse the plt
            if(linkId == linkInfo->getId()){
                outputNetworkInterface = linkInfo->getNetworkInterface();
                break;
            }
        }
        return outputNetworkInterface;
    }

    int SRSender::getSRV6PacketLengthInBytes(int lengthOfPath) {
        int STANDARD_IPV6_HEADER = 40;
        int SEGMENT_HEADER_LENGTH = 8;
        int SEGMENT_LIST_LENGTH = lengthOfPath * 16;
        int TOTAL_LENGTH = STANDARD_IPV6_HEADER + SEGMENT_HEADER_LENGTH + SEGMENT_LIST_LENGTH;
        std::cout << "TOTAL LENGTH: " << TOTAL_LENGTH << std::endl;
        return TOTAL_LENGTH;
    }

}
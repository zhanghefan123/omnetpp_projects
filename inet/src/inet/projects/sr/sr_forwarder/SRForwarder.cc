//
// Created by 张贺凡 on 2024/5/4.
//
#include "inet/projects/sr/sr_forwarder/SRForwarder.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/projects/sr/sr_packet/SRHeader_m.h"
#include "inet/projects/sr/sr_tools/SRTools.h"


namespace inet{
    Define_Module(SRForwarder);

    void SRForwarder::initialize(int stage){
        if(stage == INITSTAGE_LOCAL) {
            this->registerProtocolAndService();
            this->resolvePltTable();
            this->resolveCurrentSatelliteId();
        } else if(stage == INITSTAGE_LAST){

        }
    }

    void SRForwarder::resolvePltTable(){
        cModule* satelliteModule = this->getParentModule()->getParentModule();
        std::cout << satelliteModule->getFullPath() << std::endl;
        this->plt = dynamic_cast<LipsinLinkTable*>(satelliteModule->getSubmodule("plt"));
    }

    void SRForwarder::resolveCurrentSatelliteId() {
        cModule* satelliteModule = this->getParentModule()->getParentModule();
        std::string satelliteName = satelliteModule->getFullName();                                                  // get the containing modules's satellite name
        int currentSatelliteIdTmp = std::stoi(satelliteName.substr(satelliteName.find("SAT")+3, 5));     // extract the id from the satellite name
        this->currentSatelliteId = currentSatelliteIdTmp;
    }

    void SRForwarder::handleMessage(cMessage* message){
        if(message->isSelfMessage()){
            std::cout << "self message" << std::endl;
        } else if (message->arrivedOn("transportIn")){
            this->handlePacketFromHighLayer(message);
        } else if (message->arrivedOn("queueIn")){
            this->handlePacketFromLowLayer(message);
        } else {
            LipsinTools::module_log(this, "received unknown message");
        }
    }

    void SRForwarder::handlePacketFromHighLayer(omnetpp::cMessage *message) {
        std::cout << "handle packet from high layer" << std::endl;
        auto packet = check_and_cast<Packet*>(message);
        updatePacketTag(packet);
        this->send(packet, "queueOut");
    }

    void SRForwarder::handlePacketFromLowLayer(omnetpp::cMessage *message) {
        std::cout << "handle packet from low layer" << std::endl;
        auto* packet = check_and_cast<Packet*>(message);
        auto srHeader = packet->removeAtFront<SRHeader>();   // if we use remove, then we can update the header
        int destinationSatelliteId = srHeader->getDestination_node_id();   // get destination satellite id
        // if current satellite id == destination satellite id upload to upper layer
        if(this->currentSatelliteId == destinationSatelliteId){
            packet->insertAtFront(srHeader);
            packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::sr_app);
            packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::sr_app);
            send(packet, "transportOut");
        }
        // if current satellite id != destiantion satellite id then foward the packet
        else {
            int sidIndex = srHeader->getSid_index();                           // get the sid index
            int currentLinkIdentifier = srHeader->getSids(sidIndex);        // get the current link identifier
            NetworkInterface* outputNetworkInterface = nullptr;
            SRTools::PRINT_SR_HEADER(srHeader);
            for(auto& linkInfo : this->plt->getInnerList()){
                if(linkInfo->getId() == currentLinkIdentifier){
                    outputNetworkInterface = linkInfo->getNetworkInterface();
                    break;
                }
            }
            srHeader->setSid_index(sidIndex + 1);
            packet->addTagIfAbsent<InterfaceReq>()->setInterfaceId(outputNetworkInterface->getInterfaceId());
            packet->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
            packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_network);
            packet->insertAtFront(srHeader);                            // after we modify the header, we should insert it back
            send(packet, "queueOut");
        }

    }

    void SRForwarder::registerProtocolAndService(){
        registerService(Protocol::sr_network,gate("transportIn"),gate("transportOut"));
        registerProtocol(Protocol::sr_network,gate("queueOut"),gate("queueIn"));
    }

    void SRForwarder::updatePacketTag(Packet* packet) {
        // ----------------- remove tag -----------------
        packet->removeTagIfPresent<PacketProtocolTag>();
        packet->removeTagIfPresent<DispatchProtocolReq>();
        // ----------------- remove tag -----------------
        // -------------------------------- add new tag -------------------------------
        packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::sr_network);
        // -------------------------------- add new tag -------------------------------
    }
}
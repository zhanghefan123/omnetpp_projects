/*
 * LipsinReceiver.cc
 *
 *  Created on: Sep 5, 2023
 *      Author: zhf
 */

#include <fstream>
#include "LipsinReceiver.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/projects/lipsin/lipsin_packets/LipsinHeader_m.h"
namespace inet {
    Define_Module(LipsinReceiver);

    /**
     * lipsin initialize
     * @param stage the stage of the initialization
     */
    void LipsinReceiver::initialize(int stage) {
        if (stage == INITSTAGE_LOCAL) {
            this->recorder = new ReceiveRecorder();
            this->setLinkInfoTable();
            this->registerLipsinReceiverProtocol();
        }
    }

    void LipsinReceiver::setLinkInfoTable(){
        this->linkInfoTable = dynamic_cast<LinkInfoTable*>(this->getParentModule()->getSubmodule("linkInfoTable"));
    }

    /**
     * register protocol
     */
    void LipsinReceiver::registerLipsinReceiverProtocol(){
        registerProtocol(Protocol::lipsin_app, gate("appOut"), gate("appIn"));
    }

    /**
     * handle message
     * @param message
     */
    void LipsinReceiver::handleMessage(cMessage *message){
        if(message->arrivedOn("appIn")){
            handleIncomingDataPacket(message);
        }
    }

    /**
     * we need to handle incoming data packet
     * @param message
     */
    void LipsinReceiver::handleIncomingDataPacket(cMessage *message) {
        if(message->isPacket()){
            auto* packet = check_and_cast<Packet*>(message);

            // update the recorder
            updateRecorder(packet);

            // delete the packet and related data structure
            LipsinTools::delete_lipsin_packet(packet);
        }
    }

    /**
     * update recorder
     * @param packet
     */
    void LipsinReceiver::updateRecorder(Packet *packet) {
        // get lipsinHeader
        auto lipsinHeader = packet->peekAtFront<LipsinHeader>();
        // get pathHeader
        auto pathHeader = lipsinHeader->getPathHeader();
        // get uuid
        std::string uuid = lipsinHeader->getUuid();
        // judge if exists
        if(this->recorder->alreadyReceivedPacketUuids.find(uuid) == this->recorder->alreadyReceivedPacketUuids.end()){
            this->recorder->alreadyReceivedPacketUuids.insert(uuid);
            if(this->recorder->packetReceivedCount == 0){
                this->recorder->startTime = simTime().dbl();
            }
            // ---------------------------delay related-----------------------------------------
            // record packet encapsulation delay
            double packetEncapsulationDelay = pathHeader->encapsulationNodeCount * 0.01; // ms
            // std::cout << packetEncapsulationDelay << "ms" << std::endl;
            // get packet total delay
            double packetTotalDelay = (simTime().dbl() - lipsinHeader->getPacketCreatedTime()) * 1000;
            // get packet transmission delay
            double packetTransmissionDelay = lipsinHeader->getTransmissionDelay();
            // get packet propagation delay
            double packetPropagationDelay = lipsinHeader->getPropagationDelay();
            // get packet queueing delay
            double packetQueueingDelay = packetTotalDelay - packetTransmissionDelay - packetPropagationDelay;
            // -------------------------- delay related-----------------------------------------

            // ---------------------------update delay related-----------------------------------------
            // update the receive num
            this->recorder->packetReceivedCount++;
            // update total delay
            this->recorder->sumDelay += packetTotalDelay;
            std::cout << packetTotalDelay << std::endl;
            // update transmission delay
            this->recorder->transmissionDelay += packetTransmissionDelay;
            // update propagation delay
            this->recorder->propagationDelay += packetPropagationDelay;
            // update queueing delay
            this->recorder->queueingDelay += packetQueueingDelay;
            // update average delay
            this->recorder->averageTotalDelay = (this->recorder->sumDelay / this->recorder->packetReceivedCount);
            // update average queueing delay
            this->recorder->averageQueueingDelay = (this->recorder->queueingDelay / this->recorder->packetReceivedCount);
            std::cout << "packet length:" << packet->getByteLength() << std::endl;
            // ---------------------------update delay related-----------------------------------------

            // update the encapsulationNodeCount
            this->recorder->encapsulationNodeCount += pathHeader->encapsulationNodeCount;
            // update the receive size
            this->recorder->totalReceivedSize += int(packet->getByteLength());
            // update the throughput
            this->recorder->throughput = this->recorder->totalReceivedSize * 8 /
                                         ((simTime().dbl() - this->recorder->startTime) * 1000 * 1000);
            if(this->recorder->forwardCount == 0){
                this->recorder->forwardCount = pathHeader->getSourceDecideLinkSet()->getLinkSetSize();
            }
        }
    }

    /**
     * @brief finish and record some statistics
     */
    void LipsinReceiver::finish(){
//        std::stringstream ss;
//        std::ofstream countFile;
//        std::string outputFileName;
//        ss.setf(std::ios::fixed);
//        ss.precision(3);
//        // --------------------------deley related output--------------------------------------------
//        ss << "total delay: " << this->recorder->sumDelay<< " ms" << std::endl;
//        ss << "total propagation delay: " << this->recorder->propagationDelay << " ms" << std::endl;
//        ss << "total transmission delay: " << this->recorder->transmissionDelay << " ms" << std::endl;
//        ss << "total queueing delay: " << this->recorder->queueingDelay << " ms" << std::endl;
//        ss << "average delay: " << this->recorder->averageTotalDelay << " ms" << std::endl;
//        ss << "average queueing delay: " << this->recorder->averageQueueingDelay << " ms" << std::endl;
//        // --------------------------deley related output--------------------------------------------
//
//        ss << "received packet count: " << this->recorder->packetReceivedCount << std::endl;
//        ss << "received packet size: " << this->recorder->totalReceivedSize << " Bytes" << std::endl;
//        ss << "throughput: " << this->recorder->throughput << " Mbps" << std::endl;
//        ss << "encapsulation node count: " << this->recorder->encapsulationNodeCount << std::endl;
//
//        outputFileName = this->getParentModule()->getFullName() + std::string("_receiver_statistic.txt");
//        countFile.open(outputFileName, std::ios::out | std::ios::trunc);
//        countFile.write(ss.str().c_str(), int(ss.str().length()));
    }

    ReceiveRecorder* LipsinReceiver::getReceiveRecorder() {
        return this->recorder;
    }

} /* namespace inet */

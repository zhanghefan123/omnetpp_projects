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
            this->registerLipsinReceiverProtocol();
        }
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
        // get uuid
        std::string uuid = lipsinHeader->getUuid();
        // judge if exists
        if(this->recorder->alreadyReceivedPacketUuids.find(uuid) == this->recorder->alreadyReceivedPacketUuids.end()){
            this->recorder->alreadyReceivedPacketUuids.insert(uuid);
            if(this->recorder->packetReceivedCount == 0){
                this->recorder->startTime = simTime().dbl();
            }
            // update total delay
            this->recorder->sumDelay += simTime().dbl() - packet->getCreationTime().dbl();
            // update average delay
            this->recorder->averageDelay = this->recorder->sumDelay / this->recorder->packetReceivedCount;
            // update the receive num
            this->recorder->packetReceivedCount++;
            // update the receive size
            this->recorder->totalReceivedSize += int(packet->getByteLength());
            // update the throughput
            this->recorder->throughput = this->recorder->totalReceivedSize * 8 /
                                         ((simTime().dbl() - this->recorder->startTime) * 1000 * 1000);
        } else {
            // do nothing
        }
    }

    /**
     * finish and record some statistics
     */
    void LipsinReceiver::finish(){
        std::stringstream ss;
        std::ofstream countFile;
        std::string outputFileName;
        ss << "received packet count: " << this->recorder->packetReceivedCount << std::endl;
        ss << "received packet size: " << this->recorder->totalReceivedSize << " Bytes" << std::endl;
        ss << "throughput: " << this->recorder->throughput << " Mbps" << std::endl;
        ss << "total delay: " << this->recorder->sumDelay * 1000<< " ms" << std::endl;
        ss << "average delay: " << this->recorder->averageDelay *1000<< " ms" << std::endl;
        outputFileName = this->getParentModule()->getFullName() + std::string("_receiver_statistic.txt");
        countFile.open(outputFileName, std::ios::out | std::ios::trunc);
        countFile.write(ss.str().c_str(), int(ss.str().length()));
    }

    ReceiveRecorder* LipsinReceiver::getReceiveRecorder() {
        return this->recorder;
    }

} /* namespace inet */

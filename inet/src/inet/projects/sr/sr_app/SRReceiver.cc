//
// Created by 张贺凡 on 2024/5/4.
//
#include <fstream>
#include "inet/projects/sr/sr_app/SRReceiver.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/projects/sr/sr_packet/SRHeader_m.h"

namespace inet{
    Define_Module(SRReceiver);

    void SRReceiver::initialize(int stage){
        if(stage == INITSTAGE_LOCAL){
            this->registerSRReceiverProtocol();
        }
    }

    void SRReceiver::handleMessage(cMessage* message){
        if(message->arrivedOn("appIn")){
            this->handleIncomingDataPacket(message);
        } else {
            delete message;
        }
    }

    void SRReceiver::handleIncomingDataPacket(omnetpp::cMessage *message) {
        auto* packet = check_and_cast<Packet*>(message);                                // convert the message to packet
        auto srHeader = packet->peekAtFront<SRHeader>();                         // get srheader
        double packetCreatedTime = srHeader -> getPacket_created_time();                           // get packet created time
        double currentTime = omnetpp::simTime().dbl();                                             // get packet current time
        double timeElapsed = currentTime - packetCreatedTime;                                      // time elapsed
        this->totalTimeElapsed += timeElapsed;
        this->receivedPacketCount += 1;
        delete packet;
    }

    void SRReceiver::registerSRReceiverProtocol() {
        registerProtocol(Protocol::sr_app, gate("appOut"), gate("appIn"));
    }

    void SRReceiver::finish(){
        std::ofstream resultFile;
        std::stringstream ss;
        ss << "received packet count: " << this->receivedPacketCount << std::endl;
        ss << "total end-to-end delay: " << this->totalTimeElapsed * 1000 << "ms" << std::endl;
        ss << "avg end-to-end delay: " << this->totalTimeElapsed / double(this->receivedPacketCount) * 1000 << "ms" << std::endl;
        std::string outputFileName = this->getParentModule()->getFullName() + std::string("_SENDER") + std::string("_RESULT.txt");
        resultFile.open(outputFileName, std::ios::out | std::ios::trunc);
        resultFile.write(ss.str().c_str(), int(ss.str().length()));
        resultFile.close();
    }
}
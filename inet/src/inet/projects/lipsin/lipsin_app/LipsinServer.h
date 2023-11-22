/*
 * LipsinServer.h
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINSERVER_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINSERVER_H_


#include "inet/common/InitStages.h"
#include "inet/common/packet/Packet.h"


using namespace omnetpp;
namespace inet {



class LipsinServer : public cSimpleModule{
private:
    int packetLength;
public:
    LipsinServer() = default;
    ~LipsinServer() override = default;
protected:
    void initialize(int stage) override;
    void handleMessage(omnetpp::cMessage *message) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
public:
    void addPayLoad(Packet* packet) const;
    Packet* generateNewPacket(std::string sourceSatellite, int bloomFilterSize, int numberOfHashFunctions);
    Packet* encapsulateLipsin(Packet* packet, std::string destinationSatellite, int bloomFilterSize, int numberOfHashFunctions);
    void handlePacketFromLowerLayer(cMessage* message);
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINSERVER_H_ */

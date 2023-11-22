/*
 * LipsinReceiver.h
 *
 *  Created on: Sep 5, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINRECEIVER_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINRECEIVER_H_

#include "inet/common/InitStages.h" // for NUM_INIT_STAGES
#include "inet/common/packet/Packet.h" // for Packet

using namespace omnetpp;

namespace inet {
class ReceiveRecorder{
public:
    double sumDelay = 0;
    double averageDelay = 0;
    int packetReceivedCount = 0;
    int totalReceivedSize = 0;
    double throughput = 0;
    double startTime = 0;
    std::set<std::string> alreadyReceivedPacketUuids;
};
class LipsinReceiver : public cSimpleModule { // NOLINT
private:
    int packetLength;
    ReceiveRecorder* recorder;
public:
    LipsinReceiver() = default;
    ~LipsinReceiver() override {delete this->recorder;}
protected:
    void initialize(int stage) override;
    void handleMessage(cMessage *message) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
    void finish() override;
public:
    void updateRecorder(Packet *packet);
    void handleIncomingDataPacket(cMessage* packet);
    void registerLipsinReceiverProtocol();
public:
    ReceiveRecorder* getReceiveRecorder();
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINRECEIVER_H_ */

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
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"
using namespace omnetpp;

namespace inet {
class ReceiveRecorder{
public:
    double queueingDelay = 0; // queueing delay
    double transmissionDelay = 0; // transmission delay
    double propagationDelay = 0; // propagation delay
    double sumDelay = 0;
    double averageTotalDelay = 0;
    double averageQueueingDelay = 0;
    int packetReceivedCount = 0;
    int totalReceivedSize = 0;
    double throughput = 0;
    double startTime = 0;
    int encapsulationNodeCount = 0;
    std::set<std::string> alreadyReceivedPacketUuids;
};
class LipsinReceiver : public cSimpleModule { // NOLINT
private:
    int packetLength;
    ReceiveRecorder* recorder;
    LinkInfoTable* linkInfoTable;
public:
    LipsinReceiver() = default;
    ~LipsinReceiver() override {delete this->recorder;}
    void setLinkInfoTable();
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

//
// Created by 张贺凡 on 2024/5/4.
//

#ifndef INET_PROJECTS_DELAYTOLERANTNETWORK_SRRECEIVER_H
#define INET_PROJECTS_DELAYTOLERANTNETWORK_SRRECEIVER_H
#include "inet/common/InitStages.h" // for NUM_INIT_STAGES
#include "inet/common/packet/Packet.h" // for Packet
using namespace omnetpp;
namespace inet{
    class SRReceiver: public cSimpleModule{
    // -------------- 统计相关的字段 --------------
    private:
        int receivedPacketCount = 0 ;
        double totalTimeElapsed = 0 ;
    // -------------- 统计相关的字段 --------------
    public:
        SRReceiver() = default;
        void registerSRReceiverProtocol();
    protected:
        void initialize(int stage) override;
        void handleMessage(cMessage* message) override;
        int numInitStages() const override { return NUM_INIT_STAGES; }
        void finish() override;
    private:
        void handleIncomingDataPacket(cMessage* message);
    };
}
#endif //INET_PROJECTS_DELAYTOLERANTNETWORK_SRRECEIVER_H

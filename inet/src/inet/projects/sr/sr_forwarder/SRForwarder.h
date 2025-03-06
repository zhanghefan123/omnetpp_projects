//
// Created by 张贺凡 on 2024/5/4.
//

#ifndef INET_PROJECTS_DELAYTOLERANTNETWORK_SRFORWARDERA_H
#define INET_PROJECTS_DELAYTOLERANTNETWORK_SRFORWARDERA_H
#include <stdio.h>
#include <omnetpp.h>
#include "inet/common/InitStages.h"
#include "inet/common/packet/Packet.h"
#include "inet/projects/sr/sr_config_loader/SRConfigLoader.h"
#include "inet/projects/lipsin/lipsin_table/LipsinLinkTable.h"
using namespace omnetpp;

namespace inet{

class SRForwarder: public cSimpleModule, public cListener {
private:
    LipsinLinkTable* plt = nullptr;
    int currentSatelliteId;
public:
    SRForwarder() = default;
protected:
    void initialize(int stage) override;
    void handleMessage(cMessage * message) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
public:
    void resolvePltTable();
    void resolveCurrentSatelliteId();
    void handlePacketFromHighLayer(cMessage* message);
    void handlePacketFromLowLayer(cMessage* message);
    void registerProtocolAndService();
    void updatePacketTag(Packet* packet);
};

}
#endif // INET_PROJECTS_DELAYTOLERANTNETWORK_SRFORWARDERA_H

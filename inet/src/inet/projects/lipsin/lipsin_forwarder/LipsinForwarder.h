/*
 * LipsinForwarder.h
 *
 *  Created on: Sep 2, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_FORWARDER_LIPSINFORWARDER_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_FORWARDER_LIPSINFORWARDER_H_
#include <omnetpp.h>
#include "inet/projects/lipsin/lipsin_table/LipsinLinkTable.h"
#include "inet/projects/lipsin/lipsin_packets/LipsinHeader_m.h"
#include "inet/projects/lipsin/lipsin_global_recorder/LipsinGlobalRecorder.h"
#include "inet/projects/lipsin/lipsin_table/LipsinRoutingTable.h"
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"
#include "inet/projects/lipsin/lipsin_neighbor/LipsinNeighbor.h"
using namespace omnetpp;

namespace inet {

enum LinkFailureMechanism{
    BACKUPLINK,
    REROUTING,
    DIRECT_FORWARDING
};

class LipsinForwarder:public omnetpp::cSimpleModule, public cListener{ // NOLINT
public:
    LipsinGlobalRecorder* recorder;
    cMessage* helloTimer = nullptr;
    double helloInterval;
public:
    LinkFailureMechanism linkFailureMechanism;
    int currentSatelliteId;
    int singleTimeEncapsulationCount;
    int lsaUp;
    std::map<std::string, double> receivedLsaMap;
    std::map<int, LipsinNeighbor*> neighborMap;
public:
    LipsinRoutingTable* lipsinRoutingTable;
    LipsinGlobalRecorder* globalRecorder;
    LinkInfoTable* linkInfoTable;
    LipsinLinkTable* plt;
    LipsinLinkTable* vlt;
    LipsinLinkTable* dlt;
public:
    ~LipsinForwarder() override;
    LipsinForwarder() = default;
    void analyzeLsaPacket(const Ptr<LipsinHeader>& lipsinHeader);
    void addWatches();
    void setLipsinNeighborsUp();
    void setLsaUp();
    void setLinkInfoTable();
    void setLipsinRoutingTable();
    void setLinkFailureMechanism();
    void setGlobalRecorder();
    void setThreeTables();
    void setCurrentSatelliteId();
    void setSingleTimeEncapsulationCount();
    int traverseAndForwardPackets(std::vector<LinkInfo*> entries,
                                  int incomingInterfaceId,
                                  Ptr<const LipsinHeader> lipsinHeaderOld,
                                  PathHeader* pathHeaderOld,
                                  Packet* packet,
                                  const std::set<int>& dontForwardInterfaceIds);
    void traverseDownLinkTableAndRerouting(Ptr<const LipsinHeader> lipsinHeader, BloomFilter* oldRealLidsBf);
    std::set<int> traverseDownLinkTableAndUpdateBf(BloomFilter* oldRealLidsBf, BloomFilter* oldVirtualLidsBf);
    bool checkIsDestination(Ptr<const LipsinHeader> lipsinHeader) const;
    std::vector<Packet*> generateLsaPackets(NetworkInterface* changedInterface);
protected:
    void finish() override;
    void initialize(int stage) override;
    void handleMessage(cMessage * message) override;
    void handleTimer(cMessage * timer);
    void handlePacketFromHighLayer(cMessage * message);
    void handlePacketFromLowLayer(cMessage * message);
    int numInitStages() const override { return NUM_INIT_STAGES; }
    void subscribeSignals();
    void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) override;
    void setLipsinRecorder();
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_FORWARDER_LIPSINFORWARDER_H_ */

//
// Created by 张贺凡 on 2024/5/4.
//

#ifndef INET_PROJECTS_DELAYTOLERANTNETWORK_SRSENDER_H
#define INET_PROJECTS_DELAYTOLERANTNETWORK_SRSENDER_H
#include "inet/common/InitStages.h" // for NUM_INIT_STAGES
#include "inet/common/packet/Packet.h" // for Packet
#include "inet/projects/lipsin/lipsin_table/LipsinRoutingTable.h"
#include "inet/projects/lipsin/lipsin_table/LipsinLinkTable.h"
using namespace omnetpp;
namespace inet{
    class SRSender: public cSimpleModule{
    private:
        // --------------  data  --------------
        int sendPacketCount;
        // --------------  data  --------------
        // -------------- params --------------
        double startTime;
        double stopTime;
        double sendInterval;
        int packetLength;
        int destinationSatelliteId;
        int currentSatelliteId;
        // -------------- params --------------
        // -------------- timer  --------------
        cMessage* sendTimer = nullptr;
        // -------------- timer  --------------
        // ------------- modules  -------------
        LipsinRoutingTable* lipsinRoutingTable = nullptr;
        LipsinLinkTable* plt = nullptr;
        // ------------- modules  -------------
    public:
        ~SRSender() override;
        SRSender() = default;                            // constructor
        void startSendMessage();                         // start send message function
        void handleSendTimer(cMessage* message);         // handle start timer
        Packet* generatePacket();                        // generate packet
        void registerSRSenderProtocol();                 // register SRSender protocol
        void createSRPacket(Packet* packet);             // create sr packet
        void addPayload(Packet* packet);                 // add payload
        void resolveTables();                            // resolve lipsin routing table
        void resolveCurrentSatelliteId();                // resolve current satellite ids
        NetworkInterface*  resolveOutputNetworkInterface(int linkId);  // resolve output interface
        int getSRV6PacketLengthInBytes(int lengthOfPath);
    protected:
        void initialize(int stage) override;
        void handleMessage(cMessage* message) override;
    };
}
#endif //INET_PROJECTS_DELAYTOLERANTNETWORK_SRSENDER_H

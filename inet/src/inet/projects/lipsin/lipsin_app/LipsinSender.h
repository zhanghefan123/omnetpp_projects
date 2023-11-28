/*
 * lipsinapp.h
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINAPP_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINAPP_H_

#include "inet/common/InitStages.h" // for NUM_INIT_STAGES
#include "inet/common/packet/Packet.h" // for Packet
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"

using namespace omnetpp;
namespace inet {
    class LipsinHeader;
    // transmission pattern
    enum class TransmissionPattern{
        UNICAST, // END-TO-END Transmission Pattern
        MULTICAST, // MULTICAST Transmission Pattern
        MULTI_UNICAST, // MULTI-UNICAST Transmission Pattern
    };

    enum class MulticastPattern{
        PRIMARY, // primary based multicast
        SPF, // shortest path based multicast
    };

    class SendRecorder{ // NOLINT
    public:
        double sumFalsePositiveRate = 0;
        double sumBitSetRate = 0;
        double sumDelay;
        double averageDelay;
        int packetSentCount = 0;
        int packetReceivedCount = 0;
        int totalReceivedSize = 0;
        double throughput = 0;
        double transmissionRatio = 0;
        std::vector<int> storedBloomFilterSeed;
    };

class LipsinSender:public omnetpp::cSimpleModule{
private:
    bool emptyStoredBloomFilterSize = false;

    LinkInfoTable* linkInfoTable;

    // transmission Pattern
    TransmissionPattern transmissionPattern;

    // satellite id and name
    int satelliteId;
    std::string satelliteName;
    int packetLength;

    // current seed
    int currentBloomFilterSeed;

    // recorder
    SendRecorder* recorder;

    // params
    MulticastPattern multicastPattern;

    // params
    double startTime;
    double stopTime;
    double sendInterval;
    cXMLElement* destinationSatellitesXml;
    std::vector<int> destinationSatelliteIds;

    int bloomFilterSize;
    int numberOfHashFunctions;
    int singleTimeEncapsulationCount;

    // timer
    cMessage* sendTimer;

    // availabel bloom filter seed
    std::vector<int> availabel_bloom_filter_seed;
public:
    std::map<std::string, std::vector<int>*> multicastGroups;

protected:
    void finish() override;
    void initialize(int stage) override;
    void handleMessage(cMessage * message) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
public:
    void addPayload(Packet* packet) const;
    LipsinSender() {this->recorder = new SendRecorder();}; // NOLINT
    ~LipsinSender() override;
    void encapsulateLipsin(Packet* packet, std::set<int> insertIds, std::vector<int> destinationIdList);
    void encapsulateLipsin(Packet* packet, const std::vector<int>& destIds, int packetType);
    void start();
    std::vector<Packet*> generateNewPackets();
    void updateRecorder(Packet* packet);
    void handleResponsePacket(cMessage* message);
    void handleTimer(cMessage* message);
    void loadDestinationSatellitesXml();
    void setCurrentSatelliteIdAndName();
    void addWatches();
    void registerLipsinSenderProtocols();
    void setMulticastPattern();

    void setTransmissionPattern();
    SendRecorder* getSendRecorder();
    TransmissionPattern getTransmissionPattern(){return this->transmissionPattern;}
    int getDestinationSize(){return int(this->destinationSatelliteIds.size());}
    std::string getTransmissionPatternStr();

    void setLinkInfoTable();
    void loadAvailableBloomFilterSeed();
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_APP_LIPSINAPP_H_ */

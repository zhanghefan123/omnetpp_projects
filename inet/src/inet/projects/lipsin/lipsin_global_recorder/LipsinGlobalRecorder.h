/*
 * LipsinGlobalRecorder.h
 *
 *  Created on: Sep 13, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_GLOBAL_RECORDER_LIPSINGLOBALRECORDER_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_GLOBAL_RECORDER_LIPSINGLOBALRECORDER_H_
#include <omnetpp.h>
#include "inet/common/InitStages.h" // for NUM_INIT_STAGES
using namespace omnetpp;
namespace inet {

class LipsinGlobalRecorder : public cSimpleModule{
public:
    std::string transmissionPattern;
    int redundantForwardCount = 0;
    int totalReceivedPackets = 0;
    int totalSendPackets = 0;
    int satelliteNum = 0;

    int totalLipsinReceiver = 0;
    int totalIpReceiver = 0;

    double totalLipsinThroughput = 0;
    double totalIpThroughput = 0;

    double avgLipsinThroughput = 0;
    double avgIpThroughput = 0;

    double totalLipsinAverageDelay = 0;
    double totalIpAverageDelay = 0;
protected:
    void finish() override;
    void initialize(int stage) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
public:
    void addWatches();
    void getGlobalInformation();
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_GLOBAL_RECORDER_LIPSINGLOBALRECORDER_H_ */
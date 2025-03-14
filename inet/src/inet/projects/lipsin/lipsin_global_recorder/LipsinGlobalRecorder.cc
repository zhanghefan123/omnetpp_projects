/*
 * LipsinGlobalRecorder.cpp
 *
 *  Created on: Sep 13, 2023
 *      Author: zhf
 */

#include "LipsinGlobalRecorder.h"
#include <sstream>
#include <fstream>
#include "inet/projects/lipsin/lipsin_app/LipsinReceiver.h"
#include "inet/projects/lipsin/lipsin_app/LipsinSender.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/projects/applications/zeusudpapp/UdpRequest.h"
#include "inet/projects/applications/zeusudpapp/UdpReceiver.h"

namespace inet {
    Define_Module(LipsinGlobalRecorder);

    void LipsinGlobalRecorder::addWatches() {
        WATCH(this->redundantForwardCount);
    }

    void LipsinGlobalRecorder::finish(){
        this->getGlobalInformation();
        std::stringstream ss;
        ss.setf(std::ios::fixed);
        ss.precision(3);
        std::ofstream globalRecorderFile;
        std::string outputFileName;
        cModule* channelController = this->getParentModule()->getSubmodule("channelController");
        cModule* satelliteModule = this->getParentModule()->getSubmodule("SAT0");
        if(channelController != nullptr){
            ss << "failure rate: " << channelController->par("faultRate").doubleValue() << std::endl;
        }
        bool isLipsin = false;
        if(satelliteModule->hasPar("lidIncrease")){
            isLipsin = true;
        }
        if(isLipsin){
            int lidIncrease = int(satelliteModule->par("lidIncrease").intValue());
            ss << "lipsin bloom filter size: " << this->settedBloomFilterSize << std::endl;
            ss << "transmission pattern: " << this->transmissionPattern << std::endl;
            ss << "lid Increase: " << lidIncrease << std::endl;
            ss << "redundant forward count: " << this->redundantForwardCount << std::endl;
            ss << "avg redundant forward count: " << double(this->redundantForwardCount) / double(this->totalSendPackets) << std::endl;
            ss << "avg redudant foward count caused latency" << (double(this->redundantForwardCount) / double(this->totalSendPackets)) * this->singlePacketSize * 8 / (double(10 * 1024 * 1024)) * 1000 << "ms" << std::endl;
            ss << "total send packet count: " << this->totalSendPackets << std::endl;
            ss << "total received packet count: " << this->totalReceivedPackets << std::endl;
            ss << "avg throughput: " << this->avgLipsinThroughput << "Mbps" << std::endl;
            ss << "avg total delay: " << (this->avgLipsinTotalDelaySum / this->totalLipsinReceiver) << "ms" << std::endl;
            ss << "avg queueing delay: " << (this->avgLipsinQueueingDelaySum / this->totalLipsinReceiver) << "ms" << std::endl;
            ss << "successful ratio: " << (double(this->totalReceivedPackets) / double(this->totalSendPackets)) * 100<< std::endl;
            ss << "avg bit set rate: " << this->sumBitSetRate / double(this->totalSendPackets) * 100 << "%" << std::endl;
            ss << "max forward count: " << this->maxForwardCount << std::endl;
            ss << "avg false positive rate: " << this->sumFalsePositiveRate / double(this->totalSendPackets) * 100 << "%" << std::endl;
            ss << "encapsulation node count: " << this->encapsulationNodeCount << std::endl; // 25-26 26-27 27-28 28-29 29-30
            // ((encapsulation count) * 0.00001 * 1000 + redundantforwardcount * (payload + bloomfiltersize) + (total received packets) * (single packet forward count) * (bloom filter size)) / receive packet count
            // ss << "time consumption: " << (this->encapsulationNodeCount * (0.01) + ((this->redundantForwardCount * (8000 + this->optimizedBloomFilterSize) + this->totalReceivedPackets * (this->forwardCount) * (this->optimizedBloomFilterSize)) / double(10*1000)) ) / this->totalReceivedPackets << std::endl; // 10 microseconds --> 10-2 miliseconds
            ss << "encapsulationNodeCount:" << this->encapsulationNodeCount << " "
            << "redundant foward count: "  << this->redundantForwardCount << " "
            << "optimized bloom filter size: " << this->optimizedBloomFilterSize << " "
            << " " << "forward count: "  << this->forwardCount << " "
            << " " << "totalReceivedPackets: " << this->totalReceivedPackets << std::endl;
            ss << std::endl;
        }else{
            ss << "total send packet count: " << this->totalSendPackets << std::endl;
            ss << "total received packet count: " << this->totalReceivedPackets << std::endl;
            ss << "avg throughput: " << this->avgIpThroughput << "Mbps" << std::endl;
            ss << "avg delay: " << (this->totalIpAverageDelay / this->totalIpReceiver) * 1000 << "ms" << std::endl;
            ss << "successful ratio: " << (double(this->totalReceivedPackets) / double(this->totalSendPackets)) * 100<< std::endl;
            ss << std::endl;
        }
        outputFileName = this->getParentModule()->getFullName() + std::string("_global_statistic.txt");
        globalRecorderFile.open(outputFileName, std::ios::out | std::ios::app);
        globalRecorderFile.write(ss.str().c_str(), int(ss.str().length()));
        globalRecorderFile.close();
    }

    void LipsinGlobalRecorder::initialize(int stage){
        if(stage == INITSTAGE_LOCAL){
            this->satelliteNum = int(this->par("satelliteNum").intValue());
            this->addWatches();
        }
    }

    /**
     * the method is used to get the statistics information of the whole constellation
     * for lipsin it includes the following information:
     * - 1. redundant forward count
     * - 2. total send packet count
     * - 3. total received packet count
     * - 4. avg throughput
     * - 5. successful ratio
     *
     * for ip it includes the following information:
     * - 1. total send packet count
     * - 2. total received packet count
     * - 3. avg throughput
     * - 4. successful ratio
     */
    void LipsinGlobalRecorder::getGlobalInformation() {
        // get the name of the first satellite
        std::string firstSatelliteName = "SAT" +  std::to_string(0);
        // get the first satellite module
        cModule* firstSatelliteModule = this->getParentModule()->getSubmodule(firstSatelliteName.c_str());
        // judge if the first satellite has lipsin
        // ------------------------------------------------------------------------
        bool hasLipsin = false;
        if(firstSatelliteModule->hasPar("hasLipsin")){
            hasLipsin = firstSatelliteModule->par("hasLipsin").boolValue();
        }
        // ------------------------------------------------------------------------
        // if it has lipsin
        // ----------------------------------------------------------------------------------------------------------
        if(hasLipsin){
            // traverse all the satellites in the constellation to get the total packet received number
            for(int satIndex = 0; satIndex < this->satelliteNum; satIndex++){
                // get the name of the satellite
                std::string satModStr = "SAT" + std::to_string(satIndex);
                // get the satellite module
                cModule* satelliteModule = this->getParentModule()->getSubmodule(satModStr.c_str());
                // judge if the satellite module has receiver
                auto* receiver = dynamic_cast<LipsinReceiver*>(satelliteModule->getSubmodule("lipsinReceiver"));
                if(receiver != nullptr){
                    // update the information
                    ReceiveRecorder* receiveRecorder = receiver->getReceiveRecorder();
                    this->totalReceivedPackets += receiveRecorder->packetReceivedCount;
                    this->totalLipsinThroughput += receiveRecorder->throughput;
                    this->avgLipsinTotalDelaySum += receiveRecorder->averageTotalDelay;
                    this->avgLipsinQueueingDelaySum += receiveRecorder->averageQueueingDelay;
                    this->totalLipsinReceiver += 1;
                    this->encapsulationNodeCount += receiveRecorder->encapsulationNodeCount;
                    if(this->forwardCount == 0){
                        this->forwardCount = receiveRecorder->forwardCount;
                    }
                }
                // judge if the satellite module has sender
                auto* sender = dynamic_cast<LipsinSender*>(satelliteModule->getSubmodule("lipsinSender"));
                if(sender != nullptr){
                    if(this->transmissionPattern.empty()){
                        this->transmissionPattern = sender->getTransmissionPatternStr();
                    }
                    SendRecorder* sendRecorder = sender->getSendRecorder();
                    if(sender->getTransmissionPattern() == TransmissionPattern::MULTICAST){
                        this->totalSendPackets += double(sendRecorder->packetSentCount) * sender->getDestinationSize() / sender->multicastGroups.size();
                    } else {
                        this->totalSendPackets += (sendRecorder->packetSentCount);
                    }
                    this->sumBitSetRate += sendRecorder->sumBitSetRate;
                    this->sumFalsePositiveRate += sendRecorder->sumFalsePositiveRate;
                }

            }
            this->avgLipsinThroughput = this->totalLipsinThroughput / double(this->totalLipsinReceiver);
        }
        // ----------------------------------------------------------------------------------------------------------
        // if don't has lipsin
        // ----------------------------------------------------------------------------------------------------------
        else {
            // traverse all the satellites in the constellation to get the total packet received number
            for(int satIndex = 0; satIndex < this->satelliteNum; satIndex++) {
                // get the name of the satellite
                std::string satModStr = "SAT" + std::to_string(satIndex);
                // get the satellite module
                cModule *satelliteModule = this->getParentModule()->getSubmodule(satModStr.c_str());
                // judge if the satellite module has udp receiver
                auto* udpReceiver = dynamic_cast<UdpReceiver*>(satelliteModule->getSubmodule("app", 0));
                if(udpReceiver != nullptr){
                    // update the information
                    this->totalReceivedPackets += udpReceiver->udpRecorder->packetReceivedCount;
                    this->totalIpThroughput += udpReceiver->udpRecorder->throughput;
                    this->totalIpAverageDelay += udpReceiver->udpRecorder->averageDelay;
                    this->totalIpReceiver += 1;
                }
                // judge if the satellite module has udp request
                auto* udpRequest = dynamic_cast<UdpRequest*>(satelliteModule->getSubmodule("app",0));
                if(udpRequest != nullptr){
                    this->totalSendPackets += udpRequest->Recorder.requestSendNum;
                }

            }
            this->avgIpThroughput = this->totalIpThroughput / this->totalIpReceiver;
        }
        //----------------------------------------------------------------------------------------------------------

    }

} /* namespace inet */

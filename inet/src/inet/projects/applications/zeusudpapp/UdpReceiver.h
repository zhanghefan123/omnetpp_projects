/*
 * UdpReceiver.h
 *
 *  Created on: Sep 18, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_APPLICATIONS_ZEUSUDPAPP_UDPRECEIVER_H_
#define INET_PROJECTS_APPLICATIONS_ZEUSUDPAPP_UDPRECEIVER_H_


#include <map>

#include "inet/common/INETDefs.h"
#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet {

class UdpRecorder{
public:
    double sumDelay = 0;
    double averageDelay = 0;
    int packetReceivedCount = 0;
    int totalReceivedSize = 0;
    double throughput = 0;
    double startTime = 0;
};

/**
 * Generate packet to clients.
 *
 * Cooperates with UdpRequst client.
 */
    class INET_API UdpReceiver : public ApplicationBase, public UdpSocket::ICallback // NOLINT
    {
    public:
        UdpSocket socket;
        UdpRecorder* udpRecorder;
        int localPort = -1;
        int timeToLive{};
        int dscp{};
        int tos{};
        std::string responsePacketName{};
        double stopOperationExtraTime{};
        double stopOperationTimeOut{};


        void recordInformation();
        virtual void processStreamRequest(Packet *msg);

        int numInitStages() const override { return NUM_INIT_STAGES; }
        void initialize(int stage) override;
        void finish() override;
        void handleMessageWhenUp(cMessage *msg) override;

        virtual void clearStreams();

        void handleStartOperation(LifecycleOperation *operation) override;
        void handleStopOperation(LifecycleOperation *operation) override;
        void handleCrashOperation(LifecycleOperation *operation) override;

        void socketDataArrived(UdpSocket *socket, Packet *packet) override;
        void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
        void socketClosed(UdpSocket *socket) override;

    public:
        UdpReceiver() = default;
        ~UdpReceiver() override;
    };

} // namespace inet

#endif /* INET_PROJECTS_APPLICATIONS_ZEUSUDPAPP_UDPRECEIVER_H_ */

/*
 * UdpResponse.h
 *
 *  Created on: May 20, 2020
 *      Author: hiro
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_UDPRESPONSE_H_
#define INET_APPLICATIONS_COMPUDPAPP_UDPRESPONSE_H_

#include <map>

#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"

namespace inet {

/**
 * Generate packet to clients.
 *
 * Cooperates with UdpRequst client.
 */
class INET_API UdpResponse : public ApplicationBase, public UdpSocket::ICallback
{
public:
    UdpSocket socket;
    int localPort = -1;
    int packetLength{};
    int timeToLive{};
    int dscp{};
    int tos{};
    std::string responsePacketName{};
    double stopOperationExtraTime{};
    double stopOperationTimeOut{};


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
    UdpResponse() = default;
    ~UdpResponse() override = default;
};

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_UDPRESPONSE_H_ */

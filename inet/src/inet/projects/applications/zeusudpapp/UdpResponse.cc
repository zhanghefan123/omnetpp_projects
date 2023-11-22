/*
 * UdpResponse.cc
 *
 */

#include "inet/projects/applications/zeusudpapp/UdpResponse.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/transportlayer/common/L4PortTag_m.h"
#include "inet/projects/applications/zeusudpapp/request_m.h"
#include "inet/projects/applications/zeusudpapp/UdpConst.h"

namespace inet {

Define_Module(UdpResponse);

void UdpResponse::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        this->localPort = par(PAR_LOCAL_PORT.c_str());
        this->packetLength = int(par(PAR_PACKET_LENGTH.c_str()).intValue());
        this->timeToLive = int(par(PAR_TIME_TO_LIVE.c_str()).intValue());
        this->dscp = int(par(PAR_DSCP.c_str()).intValue());
        this->tos = int(par(PAR_TOS.c_str()).intValue());
        this->responsePacketName = par(PAR_RESPONSE_PACKET_NAME.c_str()).stringValue();
        this->stopOperationExtraTime = par(PAR_STOP_OPERATION_EXTRA_TIME.c_str());
        this->stopOperationTimeOut = par(PAR_STOP_OPERATION_TIME_OUT.c_str());
    }
}

void UdpResponse::finish()
{
}

void UdpResponse::handleMessageWhenUp(cMessage *msg)
{
    if(!msg->isSelfMessage()) {
        // std::cout << "received a packet" << std::endl;
        // the msg will be processed by socketDataArrived()
        socket.processMessage(msg);
    }
}

void UdpResponse::socketDataArrived(UdpSocket *socket_tmp, Packet *packet)
{
    processStreamRequest(packet);
}

void UdpResponse::socketErrorArrived(UdpSocket *socket_tmp, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpResponse::socketClosed(UdpSocket *socket_tmp)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(this->stopOperationExtraTime);
}

void UdpResponse::processStreamRequest(Packet *msg)
{
    auto reqHead = msg->peekAtFront<Req>();
    auto *pkt = new Packet(this->responsePacketName.c_str());
    long packetLengthTmp = this->packetLength;
    pkt->setTimestamp(msg->getTimestamp());
    const auto& payload = makeShared<ByteCountChunk>(B(packetLengthTmp));
    const auto& dataHead = makeShared<Reply>();
    dataHead->setSeq(reqHead->getSeq());
    dataHead->setCreateTime(msg->getTimestamp().dbl());
    pkt->insertAtBack(dataHead);
    pkt->insertAtBack(payload);
    socket.sendTo(pkt, msg->getTag<L3AddressInd>()->getSrcAddress(), msg->getTag<L4PortInd>()->getSrcPort());
    msg->trim();
    delete msg;
}

void UdpResponse::clearStreams()
{
}

void UdpResponse::handleStartOperation(LifecycleOperation *operation)
{
    socket.setOutputGate(gate("socketOut"));
    socket.setCallback(this);
    socket.bind(localPort);

    int timeToLiveTmp = this->timeToLive;
    if (timeToLiveTmp != -1)
        socket.setTimeToLive(timeToLiveTmp);

    auto dscpTmp = short(this->dscp);
    if (dscpTmp != -1)
        socket.setDscp(dscpTmp);

    auto tosTmp = short(this->tos);
    if (tosTmp != -1)
        socket.setTos(tosTmp);
}

void UdpResponse::handleStopOperation(LifecycleOperation *operation)
{
    clearStreams();
    socket.setCallback(nullptr);
    socket.close();
    delayActiveOperationFinish(this->stopOperationTimeOut);
}

void UdpResponse::handleCrashOperation(LifecycleOperation *operation)
{
    clearStreams();
    if (operation->getRootModule() != getContainingNode(this))
        socket.destroy();
    socket.setCallback(nullptr);
}

} // namespace inet

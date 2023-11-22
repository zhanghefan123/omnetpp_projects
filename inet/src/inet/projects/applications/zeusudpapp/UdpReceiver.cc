/*
 * UdpReceiver.cc
 *
 */

#include "inet/projects/applications/zeusudpapp/UdpReceiver.h"
#include "inet/common/ModuleAccess.h"
#include "inet/projects/applications/zeusudpapp/request_m.h"
#include "inet/projects/applications/zeusudpapp/UdpConst.h"
#include <fstream>
namespace inet {

    Define_Module(UdpReceiver);

    /**
     * delete the udpRecorder
     */
    UdpReceiver::~UdpReceiver()
    {
        delete this->udpRecorder;
    }

    /**
     * initialize the udpReceiver
     * @param stage the current initialization stage
     */
    void UdpReceiver::initialize(int stage)
    {
        ApplicationBase::initialize(stage);

        if (stage == INITSTAGE_LOCAL) {
            this->localPort = par(PAR_LOCAL_PORT.c_str());
            this->timeToLive = int(par(PAR_TIME_TO_LIVE.c_str()).intValue());
            this->dscp = int(par(PAR_DSCP.c_str()).intValue());
            this->tos = int(par(PAR_TOS.c_str()).intValue());
            this->stopOperationExtraTime = par(PAR_STOP_OPERATION_EXTRA_TIME.c_str());
            this->stopOperationTimeOut = par(PAR_STOP_OPERATION_TIME_OUT.c_str());
            this->udpRecorder = new UdpRecorder;
        }
    }

    /**
     * udpReceiver need to record the information
     */
    void UdpReceiver::recordInformation() {
        // we need to write the information into the file
        std::ofstream outfile;
        auto fileName = std::string("Receiver:") +
                        this->getParentModule()->getFullName();
        outfile.open("./" + fileName, std::ios::out | std::ios::trunc);
        std::stringstream ss;
        ss << "received packet count: " << this->udpRecorder->packetReceivedCount << std::endl;
        ss << "received packet size: " << this->udpRecorder->totalReceivedSize << " Bytes" << std::endl;
        ss << "throughput: " << this->udpRecorder->throughput << " Mbps" << std::endl;
        ss << "total delay: " << this->udpRecorder->sumDelay * 1000<< " ms" << std::endl;
        ss << "average delay: " << this->udpRecorder->averageDelay * 1000<< " ms" << std::endl;
        outfile.write(ss.str().c_str(), int(ss.str().size()));
        outfile.close();
    }

    void UdpReceiver::finish()
    {
        this->recordInformation();
        ApplicationBase::finish();
    }

    void UdpReceiver::handleMessageWhenUp(cMessage *msg)
    {
        if(!msg->isSelfMessage()) {
            socket.processMessage(msg);
        }
    }

    void UdpReceiver::socketDataArrived(UdpSocket *socket_tmp, Packet *packet)
    {
        processStreamRequest(packet);
    }

    void UdpReceiver::socketErrorArrived(UdpSocket *socket_tmp, Indication *indication)
    {
        EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
        delete indication;
    }

    void UdpReceiver::socketClosed(UdpSocket *socket_tmp)
    {
        if (operationalState == State::STOPPING_OPERATION)
            startActiveOperationExtraTimeOrFinish(this->stopOperationExtraTime);
    }

    void UdpReceiver::processStreamRequest(Packet *msg)
    {
        auto packet = check_and_cast<Packet *>(msg);
        if(udpRecorder->packetReceivedCount == 0){
            udpRecorder->startTime = simTime().dbl();
        }
        udpRecorder->packetReceivedCount++;
        udpRecorder->totalReceivedSize += int(packet->getByteLength());
        udpRecorder->sumDelay += simTime().dbl() - packet->getCreationTime().dbl();
        udpRecorder->throughput = (udpRecorder->totalReceivedSize * 8.0) / (simTime().dbl() - this->udpRecorder->startTime) / 1000.0 / 1000.0;
        udpRecorder->averageDelay = udpRecorder->sumDelay / udpRecorder->packetReceivedCount;
        delete msg;
    }


    void UdpReceiver::clearStreams()
    {
    }

    void UdpReceiver::handleStartOperation(LifecycleOperation *operation)
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

    void UdpReceiver::handleStopOperation(LifecycleOperation *operation)
    {
        clearStreams();
        socket.setCallback(nullptr);
        socket.close();
        delayActiveOperationFinish(this->stopOperationTimeOut);
    }

    void UdpReceiver::handleCrashOperation(LifecycleOperation *operation)
    {
        clearStreams();
        if (operation->getRootModule() != getContainingNode(this))
            socket.destroy();
        socket.setCallback(nullptr);
    }

} // namespace inet

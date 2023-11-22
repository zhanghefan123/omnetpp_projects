/*
 * UdpRequest.cc
 */
#include <algorithm>
#include <fstream>
#include "inet/projects/applications/zeusudpapp/UdpRequest.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/projects/applications/zeusudpapp/request_m.h"
#include "inet/projects/applications/zeusudpapp/UdpConst.h"

namespace inet {
    using std::string;

    Define_Module(UdpRequest);

    double UdpRequest::getThroughput() const {
        if(simTime().dbl() - startTime <= 0){
            return 0;
        } else {
            return double(Recorder.throughput.get()) * 8 / ((simTime().dbl() - startTime) * 1000 * 1000);
        }
    }

    double UdpRequest::getSuccessfulRate() const {
        if(Recorder.requestSendNum == 0){
            return 0;
        } else {
            return 100 * double(Recorder.DataRecvNum) / Recorder.requestSendNum;
        }
    }

    void UdpRequest::SimRecorder::ConsumerPrint(std::ostream &os) {
        os << "index:   " << nodeName << endl;
        os << "sendNum: " << requestSendNum << endl;
        os << "recvNum: " << DataRecvNum << endl;
        if (requestSendNum != 0)
            os << "trans ratio: " << 100 * double(DataRecvNum) / requestSendNum << "%" << endl;  //success trans ratio.
        os << "send Interval: " << owner->sendInterval << "s" << endl;
        os << "Throughput: " << double(throughput.get()) * 8 / ((simTime().dbl() - owner->startTime) * 1000 * 1000)
           << " Mbps" << endl;
        os << "Average delay: ";
        double sum = 0;
        if (!delayArray.empty()) {
            std::for_each(delayArray.begin(), delayArray.end(), [&sum](double value) { sum += value; });
            os << sum * 1000 / double(delayArray.size()) << " ms" << endl;
        } else
            os << 0 << "ms" << endl;
        os << endl;
    }

    UdpRequest::~UdpRequest() {
        this->cancelAndDelete(sendTimer);
    }

    void UdpRequest::setTransmissionPattern() {
        std::string transmissionPatternStr = this->par(PAR_TRANSMISSION_PATTERN.c_str()).stdstringValue();
        if (transmissionPatternStr == "PUSH") {
            this->transmissionPattern = UdpTransmissionPattern::PUSH;
        } else if (transmissionPatternStr == "PULL") {
            this->transmissionPattern = UdpTransmissionPattern::PULL;
        } else {
            throw cRuntimeError("Unknown transmission pattern: %s", transmissionPatternStr.c_str()); // NOLINT
        }
    }

    void UdpRequest::initialize(int stage) {
        ApplicationBase::initialize(stage);
        if (stage == INITSTAGE_LOCAL) {
            this->startMsg = new cMessage(START_SENDING_MSG_NAME.c_str());
            this->sendTimer = new cMessage(SEND_TIMER_MSG_NAME.c_str());
            this->Recorder.nodeName = getParentModule()->getName();
            this->Recorder.owner = this;
            this->startTime = par(PAR_START_TIME.c_str()).doubleValue();
            this->stopTime = par(PAR_STOP_TIME.c_str()).doubleValue();
            this->sendInterval = par(PAR_SEND_INTERVAL.c_str()).doubleValue();
            this->path = par(PAR_OUTPUT_DIR.c_str()).stdstringValue();
            this->serverPort = int(par(PAR_SERVER_PORT.c_str()).intValue());
            this->localPort = int(par(PAR_LOCAL_PORT.c_str()).intValue());
            this->serverAddress = par(PAR_SERVER_ADDRESS.c_str()).stringValue();
            this->requestPacketName = par(PAR_REQUEST_PACKET_NAME.c_str()).stringValue();
            this->stopOperationExtraTime = par(PAR_STOP_OPERATION_EXTRA_TIME.c_str()).doubleValue();
            this->stopOperationTimeout = par(PAR_STOP_OPERATION_TIME_OUT.c_str()).doubleValue();
            this->setTransmissionPattern();
            this->packetLength = int(par(PAR_PACKET_LENGTH.c_str()).intValue());
        }
    }

    void UdpRequest::finish() {
        std::ofstream outfile;
        auto fileName = std::string("SendInterval:") +
                        std::to_string(this->sendInterval) +
                        " | " + std::string("Consumer.txt");
        outfile.open(path + fileName, std::ofstream::app);
        if(this->transmissionPattern == UdpTransmissionPattern::PULL){
            Recorder.ConsumerPrint(outfile);
            outfile.close();
            ApplicationBase::finish();
        } else {
            std::stringstream ss;
            ss << "send packet count: " << this->Recorder.requestSendNum << std::endl;
            outfile.write(ss.str().c_str(), int(ss.str().size()));
        }
    }

    void UdpRequest::handleMessageWhenUp(cMessage *msg) {
        if (msg->isSelfMessage()) {
            if (msg == startMsg) {
                requestStream();
                scheduleAt(simTime() + sendInterval, sendTimer);
                delete msg;
            } else if (msg == sendTimer) {
                sendReq();
                if(simTime().dbl() < this->stopTime){
                    // if not reach the stop time, we need to scheduleAtNextPacket
                    scheduleAt(simTime() + sendInterval, sendTimer);
                }
            }
        } else
            socket.processMessage(msg);
    }

    void UdpRequest::socketDataArrived(UdpSocket *socket_tmp, Packet *packet) {
        receiveStream(packet);
    }

    void UdpRequest::socketErrorArrived(UdpSocket *socket_tmp, Indication *indication) {
        EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
        delete indication;
    }

    void UdpRequest::socketClosed(UdpSocket *socket_tmp) {
        // ------------------------ original code --------------------------------------
        if (operationalState == State::STOPPING_OPERATION)
            startActiveOperationExtraTimeOrFinish(this->stopOperationExtraTime);
        // ------------------------ original code --------------------------------------
    }

    void UdpRequest::sendReq() {
        // std::cout << this->getFullPath() << std::endl;
        int serverPortTmp = this->serverPort;
        const char *serverAddresTmp = this->serverAddress;
        L3Address svrAddr = L3AddressResolver().resolve(serverAddresTmp);
        auto *pk = new Packet(this->requestPacketName.c_str());
        if(this->transmissionPattern == UdpTransmissionPattern::PUSH){
            const auto& payload = makeShared<ByteCountChunk>(B(this->packetLength));
            pk->insertAtBack(payload);
        }
        const auto &head = makeShared<Req>();
        head->setSeq(seqNum);
        pk->setTimestamp(simTime());
        pk->insertAtBack(head);
        socket.sendTo(pk, svrAddr, serverPortTmp);
        Recorder.requestSendNum++;
        delayMap[seqNum] = simTime().dbl();
        seqNum++;
    }

    void UdpRequest::requestStream() {
        int serverPortTmp = this->serverPort;
        const char *serverAddresTmp = this->serverAddress;
        L3Address svrAddr = L3AddressResolver().resolve(serverAddresTmp);
        if (svrAddr.isUnspecified()) {
            EV_ERROR << "Server address is unspecified, skip sending video stream request\n";
            return;
        }
        EV_INFO << "Requesting video stream from " << svrAddr << ":" << serverPortTmp << "\n";
        socket.setOutputGate(gate("socketOut"));
        socket.bind(localPort);
        socket.setCallback(this);
        sendReq();
    }

    void UdpRequest::receiveStream(Packet *pk) {
        const auto &datahead = pk->peekAtFront<Reply>();
        Recorder.DataRecvNum++;
        Recorder.delayArray.push_back(simTime().dbl() - delayMap[int(datahead->getSeq())]);
        Recorder.last = simTime();
        Recorder.throughput += B(pk->getByteLength());
        Recorder.tempThput += double(pk->getByteLength()) * 8;
        emit(packetReceivedSignal, pk);
        pk->trim();
        delete pk;
    }

    void UdpRequest::handleStartOperation(LifecycleOperation *operation) {
        simtime_t startTimeTmp = std::max(simtime_t(this->startTime), simTime());
        scheduleAt(startTimeTmp, startMsg);
    }

    void UdpRequest::handleStopOperation(LifecycleOperation *operation) {
        socket.close();
        delayActiveOperationFinish(this->stopOperationTimeout);
    }

    void UdpRequest::handleCrashOperation(LifecycleOperation *operation) {
        if (operation->getRootModule() != getContainingNode(this))
            socket.destroy();
    }

} // namespace inet

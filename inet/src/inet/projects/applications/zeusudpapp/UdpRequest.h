/*
 * UdpRequest.h
 */

#ifndef INET_APPLICATIONS_COMPUDPAPP_UDPREQUEST_H_
#define INET_APPLICATIONS_COMPUDPAPP_UDPREQUEST_H_

#include <unordered_map>
#include "inet/common/INETDefs.h"

#include "inet/applications/base/ApplicationBase.h"
#include "inet/common/packet/Packet.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "inet/mobility/base/MobilityBase.h"

namespace inet {

    enum UdpTransmissionPattern{
        PULL,
        PUSH
    };

/**
 * packet request client application.
 */
class INET_API UdpRequest : public ApplicationBase, public UdpSocket::ICallback
{
  public:

    double getThroughput() const;
    double getSuccessfulRate() const;
    void setTransmissionPattern();

  public:
    struct SimRecorder
    {
        UdpRequest *owner{};
        std::string nodeName;
        std::vector<double> delayArray;
        std::vector<double> puts;
        double tempThput{};

        B throughput = B(0);
        int requestSendNum = 0; // the number of request need to be sent

        int DataRecvNum =0;
        simtime_t delay = 0;
        simtime_t last = 0;

        void ConsumerPrint(std::ostream &os);
    };

  public:
    SimRecorder Recorder;
    int packetLength{};
    int serverPort{};
    int localPort{};
    const char* serverAddress{};
    std::string requestPacketName;
    UdpSocket socket;
    cMessage *startMsg = nullptr;
    cMessage *sendTimer = nullptr;
    double interval{};
    std::unordered_map<int, double> delayMap;
    double stopOperationExtraTime{};
    double stopOperationTimeout{};
    UdpTransmissionPattern transmissionPattern;

  protected:
    int numInitStages() const override { return NUM_INIT_STAGES; }
    void initialize(int stage) override;
    void finish() override;
    void handleMessageWhenUp(cMessage *msg) override;

    virtual void requestStream();
    virtual void receiveStream(Packet *msg);

    void sendReq();

    // ApplicationBase:
    void handleStartOperation(LifecycleOperation *operation) override;
    void handleStopOperation(LifecycleOperation *operation) override;
    void handleCrashOperation(LifecycleOperation *operation) override;

    void socketDataArrived(UdpSocket *socket, Packet *packet) override;
    void socketErrorArrived(UdpSocket *socket, Indication *indication) override;
    void socketClosed(UdpSocket *socket_tmp) override;

  public:
    double startTime{}; // the start time of the application
    double stopTime{}; // the stop time of the application
    double sendInterval{}; // the interval between two requests
    int seqNum = 0; // the sequence number of the request
    std::string path; // the path of the output file
    UdpRequest() = default;
    ~UdpRequest() override;
};

} // namespace inet

#endif /* INET_APPLICATIONS_COMPUDPAPP_UDPREQUEST_H_ */

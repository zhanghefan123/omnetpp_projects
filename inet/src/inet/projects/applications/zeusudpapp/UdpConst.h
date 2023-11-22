#ifndef INET_APPLICATIONS_ZEUSUDPAPP_UDPCONST_H_
#define INET_APPLICATIONS_ZEUSUDPAPP_UDPCONST_H_
#include <string>
namespace inet{
    // self msg names
    const std::string START_SENDING_MSG_NAME = "start_sending_msg";
    const std::string SEND_TIMER_MSG_NAME = "send_timer_msg";

    // ned parameters of udp request and udp response
    const std::string PAR_LOCAL_PORT = "localPort";
    const std::string PAR_SEND_INTERVAL = "sendInterval";
    const std::string PAR_SERVER_ADDRESS = "serverAddress";
    const std::string PAR_SERVER_PORT = "serverPort";
    const std::string PAR_START_TIME = "startTime";
    const std::string PAR_STOP_TIME = "stopTime";
    const std::string PAR_OUTPUT_DIR = "outputDir";
    const std::string PAR_REQUEST_PACKET_NAME = "requestPacketName";
    const std::string PAR_RESPONSE_PACKET_NAME = "responsePacketName";
    const std::string PAR_STOP_OPERATION_EXTRA_TIME = "stopOperationExtraTime";
    const std::string PAR_STOP_OPERATION_TIME_OUT = "stopOperationTimeout";
    const std::string PAR_TRANSMISSION_PATTERN = "transmissionPattern";


    const std::string PAR_PACKET_LENGTH = "packetLength";
    const std::string PAR_TIME_TO_LIVE = "timeToLive";
    const std::string PAR_DSCP = "dscp";
    const std::string PAR_TOS = "tos";
}
#endif
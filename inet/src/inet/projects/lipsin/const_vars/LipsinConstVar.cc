#include "LipsinConstVar.h"

namespace inet{
    bool LipsinConstVar::SHOULD_LOG = true;

    std::string LipsinConstVar::LIPSIN_MULTICAST_PACKET_NAME = "lipsin_multicast_packet";
    std::string LipsinConstVar::LIPSIN_MULTI_UNICAST_PACKET_NAME = "lipsin_multi_unicast_packet";
    std::string LipsinConstVar::LIPSIN_UNICAST_PACKET_NAME = "lipsin_unicast_packet";
    std::string LipsinConstVar::LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_NAME = "lipsin_lsa_packet";
    std::string LipsinConstVar::LIPSIN_HELLO_PACKET_NAME = "lipsin_hello_packet";

    std::string LipsinConstVar::LINK_FAILURE_MECHANISM_BACKUPLINK = "BACKUPLINK";
    std::string LipsinConstVar::LINK_FAILURE_MECHANISM_REROUTING = "REROUTING";
    std::string LipsinConstVar::LINK_FAILURE_MECHANISM_DIRECT_FORWARDING = "DIRECT_FORWARDING";

    int LipsinConstVar::LIPSIN_MULTICAST_PACKET_TYPE = 1;
    int LipsinConstVar::LIPSIN_MULTI_UNICAST_PACKET_TYPE = 2;
    int LipsinConstVar::LIPSIN_UNICAST_PACKET_TYPE = 3;
    int LipsinConstVar::LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_TYPE = 4;
    int LipsinConstVar::LIPSIN_HELLO_PACKET_TYPE = 5;

    std::string LipsinConstVar::DESTINATION_TAG_NAME = "Destination";
    std::string LipsinConstVar::MULTICAST_GROUP_TAG_NAME = "MulticastGroup";
}

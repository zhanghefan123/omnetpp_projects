/*
 * LipsinConstVar.h
 *
 *  Created on: Sep 6, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_CONST_VARS_LIPSINCONSTVAR_H_
#define INET_PROJECTS_LIPSIN_CONST_VARS_LIPSINCONSTVAR_H_
#include <string>
namespace inet{
    class LipsinConstVar{
    public:
        static bool SHOULD_LOG;  // whether we should log the information

        // ------------------LIPSIN PACKET NAME------------------
        static std::string LIPSIN_MULTICAST_PACKET_NAME;
        static std::string LIPSIN_MULTI_UNICAST_PACKET_NAME;
        static std::string LIPSIN_UNICAST_PACKET_NAME;
        static std::string LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_NAME;
        static std::string LIPSIN_HELLO_PACKET_NAME;
        // ------------------LIPSIN PACKET NAME------------------

        // ------------------LINK FAILURE MECHANISM------------------
        static std::string LINK_FAILURE_MECHANISM_BACKUPLINK;
        static std::string LINK_FAILURE_MECHANISM_REROUTING;
        static std::string LINK_FAILURE_MECHANISM_DIRECT_FORWARDING;
        // ------------------LINK FAILURE MECHANISM------------------

        // ------------------LIPSIN PACKET TYPE--------------------
        static int LIPSIN_MULTICAST_PACKET_TYPE;
        static int LIPSIN_MULTI_UNICAST_PACKET_TYPE;
        static int LIPSIN_UNICAST_PACKET_TYPE;
        static int LIPSIN_LINK_STATE_ANNOUNCEMENT_PACKET_TYPE;
        static int LIPSIN_HELLO_PACKET_TYPE;
        // ------------------LIPSIN PACKET TYPE--------------------


        // ------------------TAG NAME -----------------------------
        static std::string DESTINATION_TAG_NAME;
        static std::string MULTICAST_GROUP_TAG_NAME;
        // ------------------TAG NAME -----------------------------
    };
}
#endif /* INET_PROJECTS_LIPSIN_CONST_VARS_LIPSINCONSTVAR_H_ */

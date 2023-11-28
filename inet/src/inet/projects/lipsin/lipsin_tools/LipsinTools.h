/*
 * LipsinTools.h
 *
 *  Created on: Sep 4, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_TOOLS_LIPSINTOOLS_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_TOOLS_LIPSINTOOLS_H_
#include <string>
#include <random>
#include "inet/common/packet/Packet.h"
#include "inet/projects/lipsin/lipsin_table/LinkInfo.h"
using namespace omnetpp;
namespace inet {
class LipsinTools {
public:
    static std::default_random_engine engine; // NOLINT
    static std::uniform_int_distribution<int> distribution;
public:
    static std::string generate_uuid();
    static void module_log(omnetpp::cModule *module, const std::string& msg);
    static void delete_lipsin_packet(Packet* packet);
    static uint64_t generate_nonce();
    static int getSatelliteId(const std::string& satelliteName);

public:
    // get different types of attributes
    static bool getBoolAttrOrPar(const cXMLElement& ifConfig, const char *name) ;
    static int getIntAttr(const cXMLElement& ifConfig, const char *name) ;
    static const char * getStrAttr(const cXMLElement& ifConfig, const char *name);
    static IslType getIslType(const cXMLElement& ifconfig, const char* name);
    static std::vector<std::string> splitString(const std::string& str, char delimiter);
    static bool whetherToForward(double fpr);
};
} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_TOOLS_LIPSINTOOLS_H_ */

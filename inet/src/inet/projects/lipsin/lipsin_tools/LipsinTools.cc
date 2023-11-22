/*
 * LipsinTools.cc
 *
 *  Created on: Sep 4, 2023
 *      Author: zhf
 */

#include "LipsinTools.h"
#include <boost/uuid/random_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "inet/projects/lipsin/lipsin_packets/LipsinHeader_m.h"
#include "inet/projects/lipsin/const_vars/LipsinConstVar.h"
namespace inet {

    std::string LipsinTools::generate_uuid() {
        boost::uuids::random_generator gen;
        return boost::lexical_cast<std::string>(gen());
    }


    /**
     * module output log
     * @param module the output module
     * @param msg the output message
     */
    void LipsinTools::module_log(omnetpp::cModule *module, const std::string &msg) {
        std::string output;
        output += "[";
        output += module->getFullPath();
        output += "]-";
        output += msg;
        output += "-[";
        output += std::to_string(omnetpp::simTime().dbl());
        output += "]";
        if(LipsinConstVar::SHOULD_LOG){
            std::cout << output << std::endl;
        }
    }

    /**
     * delete lipsin packet
     * @param packet
     */
    void LipsinTools::delete_lipsin_packet(inet::Packet *packet) {
        // get lipsin header
        auto lipsin_header = packet->peekAtFront<LipsinHeader>();
        // get the real and virtual bloom filter and path header
        auto realLidsBf = lipsin_header->getRealLidsBf();
        auto virtualLidsBf = lipsin_header->getVirtualLidsBf();
        auto pathHeader = lipsin_header->getPathHeader();
        // delete the real and virtual bloom filter and path header
        delete realLidsBf;
        delete virtualLidsBf;
        delete pathHeader;
        // delete the packet
        delete packet;
    }

    /**
     * generate nonce
     * @return the nonce
     */
    uint64_t LipsinTools::generate_nonce() {
        return getEnvir()->getRNG(0)->intRand();
    }

    int LipsinTools::getSatelliteId(const std::string& satelliteName) {
        return std::stoi(satelliteName.substr(satelliteName.find("SAT")+3, 5));
    }

    /**
     * the bool value of the attribute
     * @param ifConfig the xml config
     * @param name the attribute name
     * @return the bool value of the attribute
     */
    bool LipsinTools::getBoolAttrOrPar(const cXMLElement &ifConfig, const char *name) {
        const char *attrStr = ifConfig.getAttribute(name);
        if (attrStr && *attrStr) {
            if (strcmp(attrStr, "true") == 0 || strcmp(attrStr, "1") == 0)
                return true;
            if (strcmp(attrStr, "false") == 0 || strcmp(attrStr, "0") == 0)
                return false;
            throw cRuntimeError("Invalid boolean attribute %s = '%s' at %s", name, attrStr, ifConfig.getSourceLocation()); // NOLINT
        }
        return false;
    }

    /**
     * get int attribute
     * @param ifConfig the xml tag
     * @param name the name of the attribute
     * @return the int value of the attribute
     */
    int LipsinTools::getIntAttr(const cXMLElement &ifConfig, const char *name) {
        const char *attrStr = ifConfig.getAttribute(name);
        if (attrStr && *attrStr){
            return atoi(attrStr); // NOLINT
        }
        else{
            return -1;
        }
    }

    /**
     * get the str attribute
     * @param ifConfig the xml tag
     * @param name the attribute name
     * @return the attribute value
     */
    const char * LipsinTools::getStrAttr(const cXMLElement &ifConfig, const char *name) {
        const char *attrStr = ifConfig.getAttribute(name);
        if (attrStr && *attrStr)
            return attrStr;
        return "nothing";
    }

    /**
     * get the orbit type
     * @param ifConfig the link's xml tag
     * @param name the name of the attribute
     * @return the orbit type
     */
    IslType LipsinTools::getIslType(const cXMLElement &ifConfig, const char *name){
        const char *attrStr = ifConfig.getAttribute(name);
        if(std::string(attrStr) == "inter-orbit"){
            return IslType::INTER_ORBIT;
        } else if(std::string(attrStr) == "intra-orbit"){
            return IslType::INTRA_ORBIT;
        } else {
            return IslType::UNKNOWN_TYPE;
        }
    }
} /* namespace inet */

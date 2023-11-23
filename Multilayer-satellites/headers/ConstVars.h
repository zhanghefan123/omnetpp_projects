//
// Created by zhf on 23-9-1.
//

#ifndef DELAYTOLERANTNETWORK_CONSTVARS_H
#define DELAYTOLERANTNETWORK_CONSTVARS_H
#include <string>
namespace inet{
    // -------------------- for satellite mobility --------------------
    const std::string PAR_DISPLAY_SATELLITE_APP = "displaySatelliteApp";
    const std::string PAR_DISPLAY_COVERAGE = "displayCoverage";
    // -------------------- for satellite mobility --------------------

    // -------------------- for link type --------------------
    const std::string LINKTYPE_SATTOSAT = "SatToSat";
    const std::string LINKTYPE_SATTOGROUND = "SatToGround";
    // -------------------- for link type --------------------

    // -------------------- for link attr --------------------
    const std::string ATTR_SRCMODULE = "src-module";
    const std::string ATTR_SRCGATE = "src-gate";
    const std::string ATTR_DESTMODULE = "dest-module";
    const std::string ATTR_DESTGATE = "dest-gate";
    const std::string ATTR_CHANNELTYPE = "channel-type";
    const std::string ATTR_LINKINFO = "link-info";
    // -------------------- for link attr --------------------

    // -------------------- SAT-TO-SAT Parameters -------------------------
    const std::string PAR_SAT_TO_SAT_COLOR = "satToSatColor";
    const std::string PAR_SAT_TO_SAT_ANOTHER_COLOR = "satToSatAnotherColor";
    const std::string PAR_SAT_TO_SAT_WIDTH = "satToSatWidth";
    // -------------------- SAT-TO-SAT Parameters -------------------------

    // -------------------- SAT-TO-GROUND Parameters ----------------------
    const std::string PAR_SAT_TO_GROUND_COLOR = "satToGroundColor";
    const std::string PAR_SAT_TO_GROUND_WIDTH = "satToGroundWidth";
    //  -------------------- SAT-TO-GROUND Parameters -------------------------

    // -------------------- for channel controller --------------------
    const std::string PAR_FAULT_INTERVAL = "faultInterval";
    const std::string PAR_FAULT_RATE = "faultRate";
    const std::string PAR_RNG_NUMBER = "rngNumber";
    const std::string PAR_RECOVER_INTERVAL = "recoverInterval";
    // -------------------- for channel controller --------------------

    // -------------------- for earth scene ---------------------------
    const std::string PAR_EARTH_SCENE = "scene";
    // -------------------- for earth scene ---------------------------

    // -------------------- for position update --------------------
    const std::string PAR_UPDATE_POSITION_INTERVAL = "updatePositionInterval";

    // -------------------- for position update --------------------

    // -------------------- msgs  --------------------
    const std::string MSG_UPDATE_POSITION = "calculatePosition";
    const std::string MSG_CALCULATE_LINK_FAILURE = "calculateLinkFailure";
    // -------------------- msgs  --------------------

    // -------------------- xml --------------------
    const std::string PAR_CHANNEL_XML_CONFIG = "config";
    // -------------------- xml --------------------

}
#endif //DELAYTOLERANTNETWORK_CONSTVARS_H

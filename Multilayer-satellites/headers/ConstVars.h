//
// Created by zhf on 23-9-1.
//

#ifndef DELAYTOLERANTNETWORK_CONSTVARS_H
#define DELAYTOLERANTNETWORK_CONSTVARS_H
#include <string>
namespace inet{
    // for satellite mobility
    const std::string PAR_DISPLAY_SATELLITE_APP = "displaySatelliteApp";
    const std::string PAR_DISPLAY_COVERAGE = "displayCoverage";

    // for channel controller
    const std::string PAR_RECOVER_INTERVAL = "recoverInterval";
    const std::string PAR_FAULT_INTERVAL = "faultInterval";
    const std::string PAR_FAULT_RATE = "faultRate";

    static const char *LINKTYPE_SATTOSAT = "SatToSat";
    static const char *LINKTYPE_SATTOHIGH = "SatToHigh";
    static const char *LINKTYPE_SATTOGROUND = "SatToGround";
    static const char *LINKTYPE_HIGHTOHIGH = "HighToHigh";
    static const char *LINKTYPE_HIGHTOGROUND = "HighToGround";
    static const char *LINKTYPE_GROUNDTOGROUND = "GroundToGround";

    static const char *ATTR_SRCMODULE = "src-module";
    static const char *ATTR_SRCGATE = "src-gate";
    static const char *ATTR_DESTMODULE = "dest-module";
    static const char *ATTR_DESTGATE = "dest-gate";
    static const char *ATTR_CHANNELTYPE = "channel-type";
    static const char *ATTR_LINKINFO = "link-info";
}
#endif //DELAYTOLERANTNETWORK_CONSTVARS_H

//
// Created by zhf on 23-9-1.
//

#ifndef DELAYTOLERANTNETWORK_CONST_VARS_H
#define DELAYTOLERANTNETWORK_CONST_VARS_H
#include <string>
namespace inet{
    // for satellite mobility
    const std::string PAR_DISPLAY_SATELLITE_APP = "displaySatelliteApp";
    const std::string PAR_DISPLAY_COVERAGE = "displayCoverage";

    // for channel controller
    const std::string PAR_RECOVER_INTERVAL = "recoverInterval";
    const std::string PAR_FAULT_INTERVAL = "faultInterval";
    const std::string PAR_FAULT_RATE = "faultRate";
}
#endif //DELAYTOLERANTNETWORK_CONST_VARS_H

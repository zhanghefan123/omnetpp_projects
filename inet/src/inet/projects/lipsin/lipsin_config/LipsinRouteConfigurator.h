/*
 * LipsinRouteConfigurator.h
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_CONFIG_LIPSINROUTECONFIGURATOR_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_CONFIG_LIPSINROUTECONFIGURATOR_H_

#include <omnetpp.h>
#include "inet/common/InitStages.h"
#include "inet/projects/lipsin/lipsin_table/LipsinRoutingTable.h"
using namespace omnetpp;


namespace inet {


class LipsinRouteConfigurator : public cSimpleModule { // NOLINT
private:
    int lidIncrease = 0; // zhf add code for experiment
    cModule* containingModule; // zhf add code for satellite
    cXMLElement* lipsinConfig;
protected:
    // override the methods in cSimpleModule
    void initialize(int stage) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
public:
    LipsinRouteConfigurator() = default;
    void loadConfigFromXml(cXMLElement* lipsinConfig);
    void addWatches();
private:
    void loadPhyInterfaceParameters(cXMLElement* link,  int tagSatelliteId);
    void loadVirInterfaceParameters(cXMLElement* link,  int tagSatelliteId);
public:
    int getLidIncrease() const {return this->lidIncrease;}
    void setLidIncrease(int lidIncreaseTmp){this->lidIncrease = lidIncreaseTmp;}
    cModule* getContainingModule(){return this->containingModule;}
    void setContainingModule(cModule* containingModuleTmp){this->containingModule = containingModuleTmp;}
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_CONFIG_LIPSINROUTECONFIGURATOR_H_ */

//
// Created by 张贺凡 on 2023/11/23.
//

#ifndef OMNETPP_PROJECTS_LINK_H
#define OMNETPP_PROJECTS_LINK_H
#include <iostream>
#include <omnetpp.h>
#include <osgEarthUtil/LineOfSight>
#include <osgEarthUtil/LinearLineOfSight>
using namespace omnetpp;
typedef std::pair<cGate*,cGate*>  GatePair;
typedef struct Link{
    int state; // the link state
    cModule* srcMod; // source module
    cModule* destMod; // destination module
    GatePair gatePair; // gate pair
    cChannelType* channelType; // channel type
    std::string linkInfo; // information of link
    osgEarth::Util::LinearLineOfSightNode *los; // line of sight
    cMessage* downMessage; // link down message
    cMessage* upMessage; // link up message
}Link_t;
#endif //OMNETPP_PROJECTS_LINK_H

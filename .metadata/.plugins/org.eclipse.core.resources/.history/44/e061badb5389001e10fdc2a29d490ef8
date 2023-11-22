//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __CHANNELCONTROLLER_H_
#define __CHANNELCONTROLLER_H_

#include <omnetpp.h>
#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include <map>

#include "OsgEarthScene.h"
#include "GroundNodeMobility.h"
#include "terNetMobility.h"
#include "SatMobility.h"
#include "HAPMobility.h"

#include <osg/Node>
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthUtil/LineOfSight>
#include <osgEarthUtil/LinearLineOfSight>
#include <osgEarthSymbology/Style>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>

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
/**
 * This module is responsible for tracking the distance of mobile nodes
 * and visualizing the connectivity graph using OSG nodes.
 */
class INET_API ChannelController : public cListener, public cSimpleModule
{
  public:
    static bool judgeLinkSrcOrDestHasApps(Link& link);
    double calculate_link_failure();
  private:
    // traverse all the links
    double all_links_count = 0;
    double failure_links_count = 0;
    int rngNumber;
    int timeoutEventCount = 0;
    std::map <cModule*,bool> satStateMap;
    std::map <cModule*,std::vector<int>> satLinkMap;
    std::map <cModule*,std::vector<int>> satToOthersLinkMap; // satName -> {satToOthersLinkIndex}
    std::vector<Link> linkList; // a vector of links
    std::map <cMessage*, int> downMessageToLinkMap;
    std::map <cMessage*, int> upMessageToLinkMap;
  protected:
    static osg::ref_ptr<osg::Drawable> createLineBetweenPoints(osg::Vec3 start, osg::Vec3 end, float width, osg::Vec4 color);


    osg::ref_ptr<osg::Geode> connections = nullptr;
    // visual parameters of the connections
    std::string satToSatColor;
    std::string satToSatAnotherColor;
    double satToSatWidth = 0;

    std::string satToGroundColor;
    double satToGroundWidth = 0;

    std::string satToHighColor;
    double satToHighWidth = 0;

    std::string groundToHighColor;
    double groundToHighWidth = 0;

    double faultRate = 0;
    int faultInterval = 20;
    int recoverInterval = 5;

    // the node containing the osgEarth data
    osg::Group *scene = nullptr;
    simtime_t timeout;  // timeout
    cMessage *timeOutEvent = nullptr;  // holds pointer to the timeout self-message
    cMessage *faultCheckEvent = nullptr;

  protected:

    void initialize(int stage) override;
    int numInitStages() const override { return 3; }
    void handleMessage(cMessage *msg) override;
    void refreshDisplay() const override;
    osgEarth::Util::LinearLineOfSightNode *addLineOfSight(osg::Node *a, osg::Node *b, int type);
    void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;
    void loadXMLConfig();
    void addSatToSatLink(const cXMLElement *node);
    static void createConnection(Link &link);
    void checkSatToOtherLink(cModule *srcSat);
    void addSatToOtherLink(const cXMLElement *node);
    void addOtherToOtherLink(const cXMLElement *node);
    static void disconnect(Link &link);
    cGate *findMandatorySingleGateTowards(cModule *srcModule, cModule *destModule);
    GatePair getConnection(const cXMLElement *node);
  public:
    ChannelController() = default;
    ~ChannelController() override;

};

#endif

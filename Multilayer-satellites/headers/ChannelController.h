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
#include <map>
#include <osg/Node>
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarthAnnotation/LocalGeometryNode>
#include <osgEarthUtil/LineOfSight>
#include <osgEarthUtil/LinearLineOfSight>
#include <osgEarthSymbology/Style>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/common/INETDefs.h"
#include "OsgEarthScene.h"
#include "GroundNodeMobility.h"
#include "SatMobility.h"
#include "Link.h"


/**
 * This module is responsible for tracking the distance of mobile nodes
 * and visualizing the connectivity graph using OSG nodes.
 */
class INET_API ChannelController : public cListener, public cSimpleModule
{
  private:
    // ------------- variables to calculate real time failure rate---------------
    double all_links_count = 0; // the number of all the links
    double failure_links_count = 0; // the number of all the failed links
    // ------------- variables to calculate real time failure rate---------------

    // ------------- link failure rate related ----------------------------------
    int rngNumber = 1;
    double faultInterval = 20;
    int recoverInterval = 5;
    double faultRate = 0;
    double calculateLinkFailureInterval = 0;
    std::map <cMessage*, int> downMessageToLinkMap;
    std::map <cMessage*, int> upMessageToLinkMap;
    // ------------- link failure rate related ----------------------------------

    // ------------SAT-TO-SAT Parameters--------------
    std::string satToSatColor;
    std::string satToSatAnotherColor;
    double satToSatWidth;
    // ------------SAT-TO-SAT Parameters--------------

    // ------------SAT-TO-GROUND Parameters ----------
    std::string satToGroundColor;
    double satToGroundWidth;
    // ------------SAT-TO-GROUND Parameters ----------

    // ------------POSITION_UPDATE Parameters --------
    double updatePositionInterval;  // timeout event interval
    // ------------POSITION_UPDATE Parameters --------

    // ------------REQUIRED DATA STRUCTURES ---------
    std::vector<Link> linkList; // 所有的 link
    std::map <cModule*,bool> notEnterPolarMap; // [卫星module] ---> [是否没有进入极区]
    std::map <cModule*,std::vector<int>> satLinkMap;  // [卫星module] ---> [卫星到卫星的link index]
    std::map <cModule*,std::vector<int>> satToGroundStationsLinkMap; // [卫星module] ---> [卫星到地面战的link]
    osg::ref_ptr<osg::Geode> connections = nullptr; // Geode 是一个几何节点，是一个叶节点，可以包含 osg::Drawable 对象
    osg::Group *scene = nullptr; // osg::Group 是所有可分支节点的基类
    // ------------REQUIRED DATA STRUCTURES ---------


    // ----------- ALL SELF MSGS --------------------
    cMessage * updatePositionEvent = nullptr;
    cMessage * calculateLinkFailureEvent = nullptr;
    // ----------- ALL SELF MSGS --------------------

    bool checkPolarEnter = false;

protected:
    void initialize(int stage) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
    void handleMessage(cMessage *msg) override;
    void refreshDisplay() const override;
    void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details) override;
    void loadXMLConfig();
    void addSatToSatLink(const cXMLElement *node);
    static void createConnection(Link &link);

    void addSatToOtherLink(const cXMLElement *node);
    static void disconnect(Link &link);
    osgEarth::Util::LinearLineOfSightNode *addLineOfSight(osg::Node *a, osg::Node *b, int type);

  public:
    bool getCheckPolarEnter() const{return this->checkPolarEnter;}
    GatePair getGatePair(const cXMLElement *node);
    static bool judgeLinkSrcOrDestHasApps(Link& link);
    double calculate_link_failure();
    ChannelController() = default;
    ~ChannelController() override;
    void initializeAllEvents();
    void handleUpdatePositionEvent(cMessage* msg);
    void handleLinkFailureCalculateEvent(cMessage* msg);
    void handleLinkDownEvent(cMessage* msg);
    void handleLinkUpEvent(cMessage* msg);
    void generateDownMessageForLink(Link& link);

public:
    // --------------------- GSL related ---------------------
    int satelliteNum;
    int groundStationNum;
    std::string gslChannelType;
    std::vector<Link> gslLinkList; // 所有的 link
    std::map<std::pair<std::string, std::string>, Link> gslConnectionMap; // [地面站名称] --- [卫星名称]
    std::map<std::string, bool> groundConnectedMap;
    cModule* findClosestSatellite(GroundNodeMobility* groundNodeMobility);
    cModule* findClosestGroundStation(SatMobility* satMobility);
    void checkSatToOtherLink(cModule *srcSat);
    void initializeGSL();
    // --------------------- GSL related ---------------------
};

#endif

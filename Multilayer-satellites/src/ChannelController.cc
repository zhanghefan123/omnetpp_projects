//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#if defined(WITH_OSG) && defined(WITH_OSGEARTH)
#include "ChannelController.h"
#include "inet/common/XMLUtils.h"
#include "SatMobility.h"
#include "HAPMobility.h"
#include "GroundNodeMobility.h"
#include "inet/common/Simsignals.h"
#include <osgEarthUtil/LinearLineOfSight>
#include <osgUtil/UpdateVisitor>
#include <osg/ValueObject>
#include <osg/LineWidth>
#include <osg/Depth>
#include "ConstVars.h"

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;

Define_Module(ChannelController);


template<typename T>
bool contains(const std::vector<T>& vector, T item) { return std::find(vector.begin(), vector.end(), item) != vector.end(); }

ChannelController::~ChannelController(){
    // traverse the linkList and delete the tmp.upMessage and tmp.downMessage
    for(auto &link:downMessageToLinkMap){
        if(link.first != nullptr){
            this->cancelEvent(link.first);
            delete link.first;
        }
    }
    for(auto &link:upMessageToLinkMap){
        if(link.first != nullptr){
            this->cancelEvent(link.first);
            delete link.first;
        }
    }
}


void ChannelController::initialize(int stage)
{
    /**
     * @brief ChannelController::initialize
     * @param stage: the initialization stage of the module
     */
    switch (stage) {
    case 0:{
        satToSatColor = par("satToSatColor").stringValue();
        satToSatAnotherColor = par("satToSatAnotherColor").stringValue();
        satToSatWidth = par("satToSatWidth").doubleValue();
        satToGroundColor = par("satToGroundColor").stringValue();
        satToGroundWidth = par("satToGroundWidth").doubleValue();
        satToHighColor = par("satToHighColor").stringValue();
        satToHighWidth = par("satToHighWidth").doubleValue();
        groundToHighColor = par("groundToHighColor").stringValue();
        groundToHighWidth = par("groundToHighWidth").doubleValue();
        faultRate = par(PAR_FAULT_RATE.c_str()).doubleValue();
        faultInterval = int(par(PAR_FAULT_INTERVAL.c_str()).intValue());
        recoverInterval = int(par(PAR_RECOVER_INTERVAL.c_str()).intValue());
        rngNumber = int(par("rngNumber").intValue());
        break;
    }
    case 1:
        scene = OsgEarthScene::getInstance()->getScene()->asGroup();
        connections = new osg::Geode();
        scene->addChild(connections);
        break;
    case 2:
        loadXMLConfig();
        subscribe(enterPolarAreaSignal,this);
        subscribe(leavePolarAreaSignal,this);
        subscribe(checkSatToGroundSignal,this);
        timeout = 0.01;
        timeOutEvent = new cMessage("timeoutEvent");
        scheduleAt(simTime() + timeout, timeOutEvent);
        break;
    default:
        break;
    }
}
//helper function
static bool parseIndexedName(const char *s, std::string& name, int& index)
{
    const char *b;
    if ((b = strchr(s, '[')) == nullptr || s[strlen(s) - 1] != ']') {
        name = s;
        index = -1;
        return false;
    }
    else {
        name.assign(s, b - s);
        index = atoi(b + 1);
        return true;
    }
}
static double calculateDistance(Coord s,Coord d){
    double x1,x2,y1,y2,z1,z2,xDis,yDis,zDis;
    x1 = s.getX();
    x2 = d.getX();
    y1 = s.getY();
    y2 = d.getY();
    z1 = s.getZ();
    z2 = d.getZ();
    xDis = std::abs(x1 - x2);
    yDis = std::abs(y1 - y2);
    zDis = std::abs(z1 - z2);
    return std::sqrt(xDis*xDis + yDis*yDis + zDis*zDis) * 2;
}
void ChannelController::checkSatToOtherLink(cModule *srcSat){
    std::string srcMobiName = std::string(srcSat->getFullPath()) + std::string(".mobility");
    SatMobility *srcMobi = check_and_cast<SatMobility*>(getModuleByPath(srcMobiName.c_str()));
    for(const auto &linkIndex:satToOthersLinkMap[srcSat]){
        bool connect = true;
        double dis,maxDis;
        std::string destMobiName = std::string(linkList[linkIndex].destMod->getFullName()) + std::string(".mobility");
        if(dynamic_cast<HAPMobility*>(getModuleByPath(destMobiName.c_str())) != nullptr){
            HAPMobility *destMobi = dynamic_cast<HAPMobility*>(getModuleByPath(destMobiName.c_str()));
            dis = calculateDistance(srcMobi->getCurrentPosition(),destMobi->getCurrentPosition()),maxDis = srcMobi->getHorizonDistance();
            if(dis > maxDis)    connect = false;
        }else if(dynamic_cast<GroundNodeMobility*>(getModuleByPath(destMobiName.c_str())) != nullptr){
            GroundNodeMobility *destMobi = dynamic_cast<GroundNodeMobility*>(getModuleByPath(destMobiName.c_str()));
            dis = calculateDistance(srcMobi->getCurrentPosition(),destMobi->getCurrentPosition()),maxDis = srcMobi->getHorizonDistance();
            if(dis > maxDis)  connect = false;
        }else{
            throw cRuntimeError("Undefined destMobility!");
        }
        if(linkList[linkIndex].state == 1 && !connect){
            linkList[linkIndex].state = 0;
            disconnect(linkList[linkIndex]);
            EV <<"Signal at T="<< simTime()<< " Disconnect the link between "<< linkList[linkIndex].srcMod->getFullPath() << " and "
                    << linkList[linkIndex].destMod->getFullPath() << " Dis = "<< dis <<",MaxDis = "<< maxDis <<endl;
        }else if(linkList[linkIndex].state == 0 && connect){
            linkList[linkIndex].state = 1;
            createConnection(linkList[linkIndex]);
            EV <<"Signal at T="<< simTime()<< " Connect the link between "<< linkList[linkIndex].srcMod->getFullPath() << " and "
                    << linkList[linkIndex].destMod->getFullPath() << " Dis = "<< dis <<",MaxDis = "<< maxDis <<endl;
        }
    }
}
void ChannelController::addOtherToOtherLink(const cXMLElement *node){
    Link tmp;
    std::string tag = node->getTagName();
    cModule *srcMod = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE));
    cModule *destMod = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE));

    if (srcMod->getParentModule() != destMod->getParentModule())
        throw cRuntimeError("'src-module' and 'dest-module' must have the same parent module");
    const char *channelTypeName = node->getAttribute(ATTR_CHANNELTYPE);
    cChannelType *channelType = channelTypeName ? cChannelType::get(channelTypeName) : nullptr;
    tmp.state = 1;
    tmp.srcMod = srcMod;
    tmp.destMod = destMod;
    tmp.channelType = channelType;
    tmp.gatePair = getConnection(node);
    if(tag == LINKTYPE_HIGHTOHIGH){
        std::string srcMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE)) + std::string(".mobility"),
                destMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE)) + std::string(".mobility");
        HAPMobility *srcMobi = dynamic_cast<HAPMobility*>(getModuleByPath(srcMobiName.c_str()));
        HAPMobility *destMobi = dynamic_cast<HAPMobility*>(getModuleByPath(destMobiName.c_str()));
        tmp.los = addLineOfSight(srcMobi->getLocatorNode(), destMobi->getLocatorNode(), 3);
        tmp.state = 1;
    }else if(tag == LINKTYPE_HIGHTOGROUND){
        std::string srcMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE)) + std::string(".mobility"),
                destMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE)) + std::string(".mobility");
        HAPMobility *srcMobi = dynamic_cast<HAPMobility*>(getModuleByPath(srcMobiName.c_str()));
        GroundNodeMobility *destMobi = dynamic_cast<GroundNodeMobility*>(getModuleByPath(destMobiName.c_str()));
        tmp.los = addLineOfSight(srcMobi->getLocatorNode(), destMobi->getLocatorNode(), 3);
        tmp.state = 1;
    }else if(tag == LINKTYPE_GROUNDTOGROUND){
        std::string srcMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE)) + std::string(".mobility"),
                destMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE)) + std::string(".mobility");
        GroundNodeMobility *srcMobi = dynamic_cast<GroundNodeMobility*>(getModuleByPath(srcMobiName.c_str()));
        GroundNodeMobility *destMobi = dynamic_cast<GroundNodeMobility*>(getModuleByPath(destMobiName.c_str()));
        tmp.los = nullptr;
        tmp.state = 1;
    }
    EV << "Successfully add the link " << node->getTagName()<< "between " << srcMod->getFullPath() << " and " << destMod->getFullPath() <<endl;
    linkList.push_back(tmp);
}

void ChannelController::addSatToOtherLink(const cXMLElement *node){
    Link tmp;
    std::string tag = node->getTagName();
    cModule *srcMod = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE));
    cModule *destMod = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE));

    if (srcMod->getParentModule() != destMod->getParentModule())
        throw cRuntimeError("'src-module' and 'dest-module' must have the same parent module");
    const char *channelTypeName = node->getAttribute(ATTR_CHANNELTYPE);
    cChannelType *channelType = channelTypeName ? cChannelType::get(channelTypeName) : nullptr;
    tmp.state = 1;
    tmp.srcMod = srcMod;
    tmp.destMod = destMod;
    tmp.channelType = channelType;
    tmp.gatePair = getConnection(node);
    if(tag == LINKTYPE_SATTOHIGH){
        std::string srcMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE)) + std::string(".mobility"),
                destMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE)) + std::string(".mobility");
        SatMobility *srcMobi = dynamic_cast<SatMobility*>(getModuleByPath(srcMobiName.c_str()));
        HAPMobility *destMobi = dynamic_cast<HAPMobility*>(getModuleByPath(destMobiName.c_str()));
        tmp.los = addLineOfSight(srcMobi->getLocatorNode(), destMobi->getLocatorNode(), 2);
        tmp.state = 1;
    }else if(tag == LINKTYPE_SATTOGROUND){
        std::string srcMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE)) + std::string(".mobility"),
                destMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE)) + std::string(".mobility");
        SatMobility *srcMobi = dynamic_cast<SatMobility*>(getModuleByPath(srcMobiName.c_str()));
        GroundNodeMobility *destMobi = dynamic_cast<GroundNodeMobility*>(getModuleByPath(destMobiName.c_str()));
        tmp.los = addLineOfSight(srcMobi->getLocatorNode(), destMobi->getLocatorNode(), 0);
        tmp.state = 1;
    }
    EV << "Successfully add the link " << node->getTagName()<< "between " << srcMod->getFullPath() << " and " << destMod->getFullPath() <<endl;
    linkList.push_back(tmp);
    if(satToOthersLinkMap.find(srcMod) == satToOthersLinkMap.end()){
        satToOthersLinkMap[srcMod] = {(int)linkList.size()-1};
    }else{
        satToOthersLinkMap[srcMod].push_back((int)linkList.size()-1);
    }
}

void ChannelController::disconnect(Link &link){
    link.gatePair.first->disconnect();
    link.gatePair.second->disconnect();
}

void ChannelController::createConnection(Link &link)
{
    double latitude = 0;
    if(link.gatePair.first->isConnected() || link.gatePair.second->isConnected()) {
        std::cout<<"Exist connection between "<< link.srcMod->getFullPath() << " and "<< link.destMod->getFullPath() << endl;
        return;
    }
    // connect from source to dest
    // ----------------------------------------------------------------------------------------------------------------------------------------------
    cGate *srcGate = link.srcMod->gateHalf(link.gatePair.first->getBaseName(), cGate::OUTPUT, link.gatePair.first->getIndex());
    cGate *destGate = link.destMod->gateHalf(link.gatePair.second->getBaseName(), cGate::INPUT, link.gatePair.second->getIndex());
    cChannel *channel = link.channelType->create("channel");
    srcGate->connectTo(destGate, channel);
    // ----------------------------------------------------------------------------------------------------------------------------------------------

    // connect from dest to source
    // ----------------------------------------------------------------------------------------------------------------------------------------------
    destGate = link.srcMod->gateHalf(link.gatePair.first->getBaseName(), cGate::INPUT, link.gatePair.first->getIndex());
    srcGate = link.destMod->gateHalf(link.gatePair.second->getBaseName(), cGate::OUTPUT, link.gatePair.second->getIndex());
    channel = link.channelType->create("channel");
    srcGate->connectTo(destGate, channel);
    // ----------------------------------------------------------------------------------------------------------------------------------------------
}

void ChannelController::addSatToSatLink(const cXMLElement *node){
    cModule *srcMod = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE));
    cModule *destMod = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE));
    if (srcMod->getParentModule() != destMod->getParentModule())
        throw cRuntimeError("'src-module' and 'dest-module' must have the same parent module");
    const char *channelTypeName = node->getAttribute(ATTR_CHANNELTYPE);
    cChannelType *channelType = channelTypeName ? cChannelType::get(channelTypeName) : nullptr;

    // create tmp link
    // ------------------------------------------------------------------
    Link tmp;
    tmp.state = 1;
    tmp.srcMod = srcMod;
    tmp.destMod = destMod;
    tmp.channelType = channelType;
    tmp.gatePair = getConnection(node);
    tmp.linkInfo = std::string(node->getAttribute(ATTR_LINKINFO));
    // ------------------------------------------------------------------

    // if the link is an inter-orbit link
    // ------------------------------------------------------------------
    if(tmp.linkInfo == "inter-orbit"){
        // get src_module name in the xml file
        std::string srcMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE)) + std::string(".mobility");
        // get dest_module name in the xml file
        std::string destMobiName = std::string(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE)) + std::string(".mobility");
        // get src_module mobility
        auto *srcMobi = dynamic_cast<SatMobility*>(getModuleByPath(srcMobiName.c_str())),*destMobi = dynamic_cast<SatMobility*>(getModuleByPath(destMobiName.c_str()));
        // add line of sight between src_module and dest_module
        tmp.los = addLineOfSight(srcMobi->getLocatorNode(), destMobi->getLocatorNode(), 1);
        // downMessage and upMessage are used to simulate the link fault and recovery
        std::string downMessageInfo = std::string("down" + std::to_string(int(linkList.size())));
        tmp.downMessage = new cMessage(downMessageInfo.c_str());
        this->downMessageToLinkMap[tmp.downMessage] = (int)linkList.size();
        std::string upMessageInfo = std::string("up" + std::to_string(int(linkList.size())));
        tmp.upMessage = new cMessage(upMessageInfo.c_str());
        this->upMessageToLinkMap[tmp.upMessage] = (int)linkList.size();
        if(this->faultRate > 0){
            // schedule the first fault message
            this->scheduleAt(1 + exponential(this->faultInterval),tmp.downMessage);
        }
    }else{
        tmp.los = nullptr;
        tmp.downMessage = nullptr;
        tmp.upMessage = nullptr;
    }
    // ------------------------------------------------------------------
    linkList.push_back(tmp);
    if(satStateMap.find(srcMod) == satStateMap.end())
        satStateMap[srcMod] = true;
    if(satStateMap.find(destMod) == satStateMap.end())
        satStateMap[destMod] = true;
    if(satLinkMap.find(srcMod) == satLinkMap.end()){
        satLinkMap[srcMod] = {(int)linkList.size()-1};
    }else{
        satLinkMap[srcMod].push_back((int)linkList.size()-1);
    }
    if(satLinkMap.find(destMod) == satLinkMap.end()){
        satLinkMap[destMod] = {(int)linkList.size()-1};
    }else{
        satLinkMap[destMod].push_back((int)linkList.size()-1);
    }
}
void ChannelController::loadXMLConfig(){
    cXMLElement *script = par("config");
    for (cXMLElement *node = script->getFirstChild(); node; node = node->getNextSibling()) {
        std::string tag = node->getTagName();
        if(tag == LINKTYPE_SATTOSAT)
            addSatToSatLink(node);
        else if(tag == LINKTYPE_SATTOGROUND || tag == LINKTYPE_SATTOHIGH)
            addSatToOtherLink(node);
        else addOtherToOtherLink(node);
    }

}

osgEarth::Util::LinearLineOfSightNode *ChannelController::addLineOfSight(osg::Node *a, osg::Node *b, int type)
{
    auto mapNode = osgEarth::MapNode::findMapNode(scene);
    auto *los = new osgEarth::Util::LinearLineOfSightNode(mapNode);

    // not drawing the line of sight nodes' lines
    los->setGoodColor(osg::Vec4f(0, 0, 0, 0));
    los->setBadColor(osg::Vec4f(0, 0, 0, 0));

    auto stateSet = los->getOrCreateStateSet();
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    auto depth = new osg::Depth;
    depth->setWriteMask(false);
    stateSet->setAttributeAndModes(depth, osg::StateAttribute::ON);

    los->setUserValue("type", type);

    los->setUpdateCallback(new osgEarth::Util::LineOfSightTether(a, b));
    los->setTerrainOnly(true); // so the dish model itself won't occlude

    scene->addChild(los);

    return los;
}

void ChannelController::refreshDisplay() const
{
    // los update callbacks are called during update traversal, so do it now
    osgUtil::UpdateVisitor updateVisitor;
    scene->traverse(updateVisitor);

    // update line-of-sight lines (remove all, then add back current ones)
    connections->removeDrawables(0, connections->getNumDrawables());

    int numSatToSat = 0;
    int numSatToGround = 0;
    int numSatToHigh = 0;
    int numGroundToHigh = 0;

    for (const auto &link : linkList) {
        if(link.state == 0 || link.los == nullptr) continue;
            auto start = link.los->getStartWorld();
            auto end = link.los->getEndWorld();

            int type;
            link.los->getUserValue("type", type);
            switch (type) {
                case 0:{
                    ++numSatToGround;
                    if (!satToGroundColor.empty())
                        connections->addDrawable(createLineBetweenPoints(start, end, satToGroundWidth, osgEarth::Color(satToGroundColor)));
                    break;
                }
                case 1:{
                    cModule* sourceModule = link.srcMod;
                    auto* srcSatMobility = dynamic_cast<SatMobility*>(sourceModule->getSubmodule("mobility"));
                    cModule* destModule = link.destMod;
                    auto* destSatMobility = dynamic_cast<SatMobility*>(destModule->getSubmodule("mobility"));

                    std::pair<double, double> sourceLatAndLong = srcSatMobility->getLatitudeAndLongitude();
                    double srcLatitude = sourceLatAndLong.first;
                    double srcLongitude = sourceLatAndLong.second;

                    std::pair<double, double> destLatAndLong = destSatMobility->getLatitudeAndLongitude();
                    double destLatitude = destLatAndLong.first;
                    double destLongitude = destLatAndLong.second;

                    int situation = 0;
                    if(srcLatitude > destLatitude)
                    {
                        situation = 1;
                    }

                    ++numSatToSat;
                    if (!satToSatColor.empty())
                    {
                        if(situation == 1){
                            connections->addDrawable(createLineBetweenPoints(start, end, satToSatWidth, osgEarth::Color(satToSatColor)));
                        } else {
                            connections->addDrawable(createLineBetweenPoints(start, end, satToSatWidth, osgEarth::Color(satToSatAnotherColor)));
                        }
                    }
                    break;
                }
                case 2:{
                    ++numSatToHigh;
                    if (!satToHighColor.empty())
                        connections->addDrawable(createLineBetweenPoints(start, end, satToHighWidth, osgEarth::Color(satToHighColor)));
                    break;
                }
                case 3:{
                    ++numGroundToHigh;
                    if (!groundToHighColor.empty())
                        connections->addDrawable(createLineBetweenPoints(start, end, groundToHighWidth, osgEarth::Color(groundToHighColor)));
                    break;
                }
            }
    }

//    EV << "Active connections: " << numSatToSat << " sat-to-sat and " << numSatToGround << " sat-to-ground "<< numSatToHigh <<" sat-to-high\n";
}

osg::ref_ptr<osg::Drawable> ChannelController::createLineBetweenPoints(osg::Vec3 start, osg::Vec3 end, float width, osg::Vec4 color)
{
    osg::ref_ptr<osg::Geometry> orbitGeom = new osg::Geometry;
    osg::ref_ptr<osg::DrawArrays> drawArrayLines = new  osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP);
    osg::ref_ptr<osg::Vec3Array> vertexData = new osg::Vec3Array;

    orbitGeom->addPrimitiveSet(drawArrayLines);
    auto stateSet = orbitGeom->getOrCreateStateSet();
    stateSet->setAttributeAndModes(new osg::LineWidth(width), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
    stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    auto depth = new osg::Depth;
    depth->setWriteMask(false);
    stateSet->setAttributeAndModes(depth, osg::StateAttribute::ON);

    vertexData->push_back(start);
    vertexData->push_back(end);

    orbitGeom->setVertexArray(vertexData);
    drawArrayLines->setFirst(0);
    drawArrayLines->setCount(vertexData->size());

    osg::ref_ptr<osg::Vec4Array> colorData = new osg::Vec4Array;
    colorData->push_back(osgEarth::Color(color));
    orbitGeom->setColorArray(colorData, osg::Array::BIND_OVERALL);
    return orbitGeom;
}

bool ChannelController::judgeLinkSrcOrDestHasApps(Link &link) {
    cModule* srcModule = link.gatePair.first->getOwnerModule();
    cModule* destModule = link.gatePair.second->getOwnerModule();
    bool srcHasIpApp = (srcModule->par("numApps").intValue() > 0);
    bool destHasIpApp = (destModule->par("numApps").intValue() > 0);
    if(srcHasIpApp || destHasIpApp){
        std::cout << "dont down" << std::endl;
        return true;
    }
    bool hasLipsin = false;
    if(srcModule->hasPar("hasLipsin")){
        hasLipsin = srcModule->par("hasLipsin").boolValue();
    }
    if(hasLipsin){
        // if has lipsinSender or receiver
        bool srcHasLipsinApp = srcModule->par("hasLipsinSender") || srcModule->par("hasLipsinReceiver") || srcModule->par("hasLipsinServer").boolValue();
        bool destHasLipsinApp =  destModule->par("hasLipsinSender") || destModule->par("hasLipsinReceiver") || destModule->par("hasLipsinServer").boolValue();
        if(srcHasLipsinApp || destHasLipsinApp){
            return true;
        }
    }
    return false;
}

double ChannelController::calculate_link_failure() {
    for(const auto& link : this->linkList){
        if(link.state == 0 && link.linkInfo == "inter-orbit"){
            failure_links_count += 1;
        }
        if(link.linkInfo == "inter-orbit"){
            all_links_count += 1;
        }
    }
    double link_failure_rate = failure_links_count / all_links_count;
    return link_failure_rate;
}

void ChannelController::handleMessage(cMessage *msg)
{
    if(msg == timeOutEvent){
        for(const auto &satList:satLinkMap){
            std::string satStr = satList.first->getFullPath();
            satStr += ".mobility";
            auto *sMobi =  check_and_cast<SatMobility *>(satList.first->getModuleByPath(satStr.c_str()));
            sMobi->updatePosition();
        }
        scheduleAt(simTime()+timeout, timeOutEvent);
        if(timeoutEventCount % 500 == 0){
            std::cout << "link failure rate: " << this->calculate_link_failure() << std::endl;
        }
        timeoutEventCount += 1;
    }
    // if the message is the down link message
    else if(this->downMessageToLinkMap.find(msg) != downMessageToLinkMap.end()){
        // get the link index
        int link_index = downMessageToLinkMap[msg];
        // get the corresponding link
        auto& link = linkList[link_index];
        // if we need to shutdown the link
        double now_probability = uniform(0, 1.0, rngNumber);
        // get the src module
        std::string srcModuleFullPath = link.gatePair.first->getOwnerModule()->getFullPath();

        if(now_probability < (faultRate)){
            if(link.gatePair.first->isConnected() && link.gatePair.second->isConnected()){
                    if(!this->judgeLinkSrcOrDestHasApps(link)){
                        this->disconnect(link);
                        link.state = 0;
                        scheduleAt(simTime() + 5, link.upMessage);
                    } else {
                        this->scheduleAt(simTime() + exponential(faultInterval), link.downMessage);
                    }
            } else {
                this->scheduleAt(simTime() + exponential(faultInterval), link.downMessage);
            }
        } else {
            scheduleAt(simTime()+ exponential(faultInterval), link.downMessage);
        }
    }
    // if the message is the recover link message
    else if(this->upMessageToLinkMap.find(msg) != this->upMessageToLinkMap.end()){
        // get the link index
        int link_index = upMessageToLinkMap[msg];
        // get the corresponding link
        auto& link = linkList[link_index];
        // we need to recovery the link
        if(link.state == 0 && !link.gatePair.first->isConnected() && !link.gatePair.second->isConnected()){
            createConnection(link);
            link.state = 1;
        }
        this->scheduleAt(simTime() + exponential(faultInterval), link.downMessage);
    }
}

void ChannelController::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details){
    // TODO
    // judge the signal type, polar_constellation type?
    if(signalID == leavePolarAreaSignal){
        //when a satellite leave the polar area, it will be ready to establish inter-orbit links, but whether establishing or not depends on the state of another node.
        auto *src = check_and_cast<cModule * >(obj);
        satStateMap[src] = true;
        for(const auto &linkIndex : satLinkMap[src]){
            if(satStateMap[linkList[linkIndex].srcMod] && satStateMap[linkList[linkIndex].destMod] && linkList[linkIndex].linkInfo == "inter-orbit"){
                linkList[linkIndex].state = 1;
                createConnection(linkList[linkIndex]);
            }
        }
    }else if(signalID == enterPolarAreaSignal){
        //when the satellite enters the polar area, it will shut down the inter-orbit links immediately
        cModule *src = check_and_cast<cModule * >(obj);
        double latitude = 0;
        satStateMap[src] = false;
        for(const auto &linkIndex : satLinkMap[src]){
            if(linkList[linkIndex].linkInfo != "inter-orbit") continue;
            linkList[linkIndex].state = 0;
            disconnect(linkList[linkIndex]);
        }
        refreshDisplay();
    }else if(signalID == checkSatToGroundSignal){
        cModule *src = check_and_cast<cModule *>(obj);
        checkSatToOtherLink(src);
    }

}

cGate *ChannelController::findMandatorySingleGateTowards(cModule *srcModule, cModule *destModule)
{
    cGate *resultGate = nullptr;
    for (cModule::GateIterator it(srcModule); !it.end(); ++it) {
        cGate *gate = *it;
        if (gate->getType() == cGate::OUTPUT && gate->getNextGate() != nullptr && gate->getNextGate()->getOwnerModule() == destModule) {
            if (resultGate)
                throw cRuntimeError("Ambiguous gate: there is more than one connection between the source and destination modules"); // NOLINT
            resultGate = gate;
        }
    }
    if (!resultGate)
        throw cRuntimeError("No such gate: there is no connection between the source and destination modules"); // NOLINT
    return resultGate;
}

GatePair ChannelController::getConnection(const cXMLElement *node)
{
    if (node->getAttribute(ATTR_SRCGATE)) {
        cModule *srcModule = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE));
        const char *srcGateSpec = xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCGATE);
        std::string name;
        int index;
        parseIndexedName(srcGateSpec, name, index);
        if (srcModule->gateType(name.c_str()) == cGate::OUTPUT) {
            return GatePair(srcModule->gate(name.c_str(), index), nullptr); // throws if not found // NOLINT
        }
        else if (srcModule->gateType(name.c_str()) == cGate::INOUT) {
            cGate *outputHalf = srcModule->gateHalf(name.c_str(), cGate::OUTPUT, index);
            cGate *inputHalf = srcModule->gateHalf(name.c_str(), cGate::INPUT, index);
            if (outputHalf->getNextGate() == nullptr || inputHalf->getPreviousGate() == nullptr)
                throw cRuntimeError("The specified gate (or the input or output half of it) is not connected"); // NOLINT
            if (outputHalf->getNextGate()->getOwnerModule() != inputHalf->getPreviousGate()->getOwnerModule()) // NOLINT
                throw cRuntimeError("The specified gate (or the input or output half of it) is connected to a node on another level");
            return GatePair(outputHalf, inputHalf->getPreviousGate()); // NOLINT
        }
        else {
            throw cRuntimeError("'src-gate' must be an inout or output gate"); // NOLINT
        }
    }
    else if (node->getAttribute(ATTR_DESTMODULE)) {
        cModule *srcModule = getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_SRCMODULE));
        cModule *destModule =getModuleByPath(xmlutils::getMandatoryFilledAttribute(*node, ATTR_DESTMODULE));
        if (srcModule->getParentModule() != destModule->getParentModule())
            throw cRuntimeError("Source and destination modules must be under the same parent"); // NOLINT
        cGate *srcGate = findMandatorySingleGateTowards(srcModule, destModule);
        bool bidir = strlen(srcGate->getNameSuffix()) > 0; //TODO use =srcGate->isGateHalf();
        if (!bidir) {
            return GatePair(srcGate, nullptr); // NOLINT
        }
        else {
            cGate *otherHalf = srcModule->gateHalf(srcGate->getBaseName(), cGate::INPUT, srcGate->isVector() ? srcGate->getIndex() : -1); //TODO use =srcGate->getOtherHalf();
            cGate *otherSrcGate = otherHalf->getPreviousGate();
            if (otherSrcGate == nullptr)
                throw cRuntimeError("Broken bidirectional connection: the corresponding input gate is not connected"); // NOLINT
            if (otherSrcGate->getOwnerModule() != destModule)
                throw cRuntimeError("Broken bidirectional connection: the input and output gates are connected to two different modules"); // NOLINT
            return GatePair(srcGate, otherSrcGate); // NOLINT
        }
    }
    else {
        throw cRuntimeError("Missing attribute: Either 'src-gate' or 'dest-module' must be present"); // NOLINT
    }
}


#endif

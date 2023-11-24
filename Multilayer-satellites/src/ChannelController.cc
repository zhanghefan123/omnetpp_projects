//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#if defined(WITH_OSG) && defined(WITH_OSGEARTH)
#include <osg/Geometry>
#include <unistd.h>
#include <osgEarthUtil/LinearLineOfSight>
#include <osgUtil/UpdateVisitor>
#include <osg/LineWidth>
#include <osg/Depth>
#include "ChannelController.h"
#include "inet/common/XMLUtils.h"
#include "SatMobility.h"
#include "GroundNodeMobility.h"
#include "inet/common/Simsignals.h"
#include "ConstVars.h"
#include "MultilayerTools.h"

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;

Define_Module(ChannelController);


ChannelController::~ChannelController(){
    /**
     * @brief 进行所有事件的清空
     */
    if(updatePositionEvent != nullptr){
        this->cancelEvent(updatePositionEvent);
        delete this->updatePositionEvent;
    }

    if(calculateLinkFailureEvent != nullptr){
        this->cancelEvent(calculateLinkFailureEvent);
        delete this->calculateLinkFailureEvent;
    }

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
            satToSatColor = par(PAR_SAT_TO_SAT_COLOR.c_str()).stringValue();
            satToSatAnotherColor = par(PAR_SAT_TO_SAT_ANOTHER_COLOR.c_str()).stringValue();
            satToSatWidth = par(PAR_SAT_TO_SAT_WIDTH.c_str()).doubleValue();

            satToGroundColor = par(PAR_SAT_TO_GROUND_COLOR.c_str()).stringValue();
            satToGroundWidth = par(PAR_SAT_TO_GROUND_WIDTH.c_str()).doubleValue();

            faultRate = par(PAR_FAULT_RATE.c_str()).doubleValue();
            faultInterval = double(par(PAR_FAULT_INTERVAL.c_str()).doubleValue());
            rngNumber = int(par(PAR_RNG_NUMBER.c_str()).intValue());
            recoverInterval = int(par(PAR_RECOVER_INTERVAL.c_str()).intValue());

            break;
        }
        case 1:{
            scene = OsgEarthScene::getInstance()->getScene()->asGroup();
            connections = new osg::Geode();
            scene->addChild(connections);
            break;
        }
        case 2:{
            loadXMLConfig();
            subscribe(enterPolarAreaSignal,this);
            subscribe(leavePolarAreaSignal,this);
            subscribe(checkSatToGroundSignal,this);
            initializeAllEvents();
            break;
        }
        default:
            break;
    }
}

void ChannelController::checkSatToOtherLink(cModule *srcSat){
    std::string srcMobiName = std::string(srcSat->getFullPath()) + std::string(".mobility");
    auto *srcMobi = check_and_cast<SatMobility*>(getModuleByPath(srcMobiName.c_str()));
    for(const auto &linkIndex:satToGroundStationsLinkMap[srcSat]){
        bool connect = true;
        double dis,maxDis;
        std::string destMobiName = std::string(linkList[linkIndex].destMod->getFullName()) + std::string(".mobility");
        if(dynamic_cast<GroundNodeMobility*>(getModuleByPath(destMobiName.c_str())) != nullptr){
            auto *destMobi = dynamic_cast<GroundNodeMobility*>(getModuleByPath(destMobiName.c_str()));
            dis = MultilayerTools::calculateDistance(srcMobi->getCurrentPosition(),destMobi->getCurrentPosition());
            maxDis = srcMobi->getHorizonDistance();
            if(dis > maxDis)  connect = false;
        }else{
            throw cRuntimeError("Undefined destMobility!"); // NOLINT
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

void ChannelController::addSatToOtherLink(const cXMLElement *node){
    /**
     * @brief addSatToOtherLink 添加从卫星到地面站的链路
     * @param node xml 标签，代表一条链路
     */
    // --------------------------------------- create link --------------------------------------------------------------
    Link satToGroundLink; // create a gsl link
    std::string tag = node->getTagName(); // get tagname
    std::string srcModuleName = node->getAttribute(ATTR_SRCMODULE.c_str()); // get src module name
    std::string destModuleName = node->getAttribute(ATTR_DESTMODULE.c_str()); // get dest module name
    cModule* srcModule = getModuleByPath(srcModuleName.c_str()); // get src module
    cModule* destModule = getModuleByPath(destModuleName.c_str()); // get dest module
    if (srcModule->getParentModule() != destModule->getParentModule())
        throw cRuntimeError("'src-module' and 'dest-module' must have the same parent the osg earth"); // NOLINT
    const char *channelTypeName = node->getAttribute(ATTR_CHANNELTYPE.c_str());
    cChannelType *channelType = channelTypeName ? cChannelType::get(channelTypeName) : nullptr;
    // --------------------------------------- create link --------------------------------------------------------------
    if(tag == LINKTYPE_SATTOGROUND){
        auto *srcMobi = dynamic_cast<SatMobility*>(srcModule->getSubmodule("mobility"));
        auto *destMobi = dynamic_cast<GroundNodeMobility*>(destModule->getSubmodule("mobility"));
        satToGroundLink.srcMod = srcModule; // set the srcModule of the link
        satToGroundLink.destMod = destModule; // set the destModule of the link
        satToGroundLink.los = addLineOfSight(srcMobi->getLocatorNode(), destMobi->getLocatorNode(), 0);
        satToGroundLink.state = 1; // the initialize status of a link is up
        satToGroundLink.channelType = channelType; // set the channel type
        satToGroundLink.gatePair = getGatePair(node); // get the gate pair of the link
    } else {
        throw cRuntimeError("other not supported now"); // NOLINT
    }
    linkList.push_back(satToGroundLink);
    if(satToGroundStationsLinkMap.find(srcModule) == satToGroundStationsLinkMap.end()){
        satToGroundStationsLinkMap[srcModule] = {(int)linkList.size() - 1};
    }else{
        satToGroundStationsLinkMap[srcModule].push_back((int)linkList.size() - 1);
    }
}

void ChannelController::addSatToSatLink(const cXMLElement *node){
    /**
     * @brief addSatToSatLink 添加从卫星到卫星的链路
     * @param node xml 标签，代表一条链路
     */
    // -------------------------create link ------------------------------------
    Link satToSatLink;
    std::string srcModuleName = node->getAttribute(ATTR_SRCMODULE.c_str());
    std::string destModuleName = node->getAttribute(ATTR_DESTMODULE.c_str());
    cModule *srcModule = getModuleByPath(srcModuleName.c_str());
    cModule *destModule = getModuleByPath(destModuleName.c_str());
    if (srcModule->getParentModule() != destModule->getParentModule())
        throw cRuntimeError("'src-module' and 'dest-module' must have the same parent module the osgearth"); // NOLINT
    const char *channelTypeName = node->getAttribute(ATTR_CHANNELTYPE.c_str());
    cChannelType *channelType = channelTypeName ? cChannelType::get(channelTypeName) : nullptr;
    // -------------------------create link ------------------------------------

    // -------------------------same procedure for inter and intra orbit --------------------
    satToSatLink.state = 1;
    satToSatLink.srcMod = srcModule;
    satToSatLink.destMod = destModule;
    satToSatLink.channelType = channelType;
    satToSatLink.gatePair = getGatePair(node);
    satToSatLink.linkInfo = std::string(node->getAttribute(ATTR_LINKINFO.c_str()));
    // -------------------------same procedure for inter and intra orbit --------------------

    // if the link is an inter-orbit link
    // ------------------------------------------------------------------
    if(satToSatLink.linkInfo == "inter-orbit"){
        // get src_module mobility
        auto *srcMobi = dynamic_cast<SatMobility*>(srcModule->getSubmodule("mobility"));
        auto *destMobi = dynamic_cast<SatMobility*>(destModule->getSubmodule("mobility"));
        // add line of sight between src_module and dest_module
        satToSatLink.los = addLineOfSight(srcMobi->getLocatorNode(), destMobi->getLocatorNode(), 1);
        // 如果链路故障率大于0
        if(this->faultRate > 0){
            // downMessage and upMessage are used to simulate the link fault and recovery
            generateDownMessageForLink(satToSatLink);
        }
    }else{
        satToSatLink.los = nullptr;
        satToSatLink.downMessage = nullptr;
        satToSatLink.upMessage = nullptr;
    }
    // ------------------------------------------------------------------
    linkList.push_back(satToSatLink);


    // 全部置为没有进入极区的情况
    if(notEnterPolarMap.find(srcModule) == notEnterPolarMap.end())
        notEnterPolarMap[srcModule] = true;
    if(notEnterPolarMap.find(destModule) == notEnterPolarMap.end())
        notEnterPolarMap[destModule] = true;

    // 添加到 satLinkMap 中
    if(satLinkMap.find(srcModule) == satLinkMap.end()){
        satLinkMap[srcModule] = {(int)linkList.size()-1};
    }else{
        satLinkMap[srcModule].push_back((int)linkList.size()-1);
    }
    if(satLinkMap.find(destModule) == satLinkMap.end()){
        satLinkMap[destModule] = {(int)linkList.size()-1};
    }else{
        satLinkMap[destModule].push_back((int)linkList.size()-1);
    }
}

void ChannelController::loadXMLConfig(){
    /**
     * @brief loadXMLConfig 加载 xml 配置文件
     */
    // get xml doc
    cXMLElement *script = par(PAR_CHANNEL_XML_CONFIG.c_str());
    // 进行子标签的遍历
    for (cXMLElement *node = script->getFirstChild(); node!=nullptr; node = node->getNextSibling()) {
        std::string tag = node->getTagName(); // 获取标签名
        if(tag == LINKTYPE_SATTOSAT) // 如果是卫星到卫星的链路
            addSatToSatLink(node); // 添加卫星到卫星的链路
        else if(tag == LINKTYPE_SATTOGROUND) // 如果是卫星到地面站的链路
            addSatToOtherLink(node); // 添加卫星到地面站的链路
        else {
            throw cRuntimeError("other not supported now"); // NOLINT
        }
    }

}

osgEarth::Util::LinearLineOfSightNode *ChannelController::addLineOfSight(osg::Node *a, osg::Node *b, int type)
{
    /**
     * @brief addLineOfSight 添加一条绘制的链路
     */
    auto mapNode = osgEarth::MapNode::findMapNode(scene);
    auto *los = new osgEarth::Util::LinearLineOfSightNode(mapNode);

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
    /**
     * @brief refreshDisplay 进行星间链路和星地链路的绘制
     */
    osgUtil::UpdateVisitor updateVisitor;
    scene->traverse(updateVisitor);
    connections->removeDrawables(0, connections->getNumDrawables());
    int numSatToSat = 0;
    int numSatToGround = 0;
    for (const auto &link : linkList) {
        // 如果没有连接，那么就不进行绘制
        if(link.state == 0 || link.los == nullptr){
            continue;
        }

        // 获取链路的起始点和终止点
        auto start = link.los->getStartWorld();
        auto end = link.los->getEndWorld();

        // 获取链路的类型
        int type;
        link.los->getUserValue("type", type);

        switch (type) {
            case 0:{ // 代表是星地链路
                // 添加星地链路
                ++numSatToGround;
                if (!satToGroundColor.empty())
                    connections->addDrawable(MultilayerTools::createLineBetweenPoints(start, end, satToGroundWidth, osgEarth::Color(satToGroundColor)));
                break;
            }
            case 1:{  // 代表是星间链路
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
                if((srcLatitude > destLatitude))
                {
                    situation = 1;
                }

                ++numSatToSat;
                if (!satToSatColor.empty())
                {
                    if(situation == 1){
                        connections->addDrawable(MultilayerTools::createLineBetweenPoints(start, end, satToSatWidth, osgEarth::Color(satToSatColor)));
                    } else {
                        connections->addDrawable(MultilayerTools::createLineBetweenPoints(start, end, satToSatWidth, osgEarth::Color(satToSatAnotherColor)));
                    }
                }
                break;
            }
            default:{
                break;
            }
        }
    }
}

bool ChannelController::judgeLinkSrcOrDestHasApps(Link &link) {
    /**
     * @brief 判断链路的源模块或者目的模块是否有应用,如果有的话，那么就不进行链路的断开
     */
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
    /**
     * @brief 计算链路的故障率
     */
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
    /**
     * @brief 处理各种各样的自消息
     */
    std::string msgname = msg->getName();
    if(msg == updatePositionEvent){
        handleUpdatePositionEvent(msg);
    } else if(msg == calculateLinkFailureEvent){
        handleLinkFailureCalculateEvent(msg);
    } else if(msgname.find("down") != std::string::npos) {
        handleLinkDownEvent(msg);
    } else if(msgname.find("up") != std::string::npos){
        handleLinkUpEvent(msg);
    }
}

void ChannelController::handleLinkUpEvent(omnetpp::cMessage *msg) {
    int link_index = upMessageToLinkMap[msg]; // 获取消息对应的链路索引
    auto& link = linkList[link_index]; // 获取相应的链路
    bool firstGateIsConnected = link.gatePair.first->isConnected(); // 判断第一个端口是否连接
    bool secondGateIsConnected = link.gatePair.second->isConnected(); // 判断第二个端口是否连接
    if(link.state == 0 && !firstGateIsConnected && !secondGateIsConnected){ // 如果链路处于断开状态，并且两个端口都没有连接
        createConnection(link); // 进行连接的创建
        link.state = 1; // 将链路的状态置为连接状态
    }
    this->scheduleAt(simTime() + exponential(faultInterval), link.downMessage); // 重新计划下一次的链路断开事件
}

void ChannelController::handleLinkDownEvent(omnetpp::cMessage *msg) {
    int link_index = downMessageToLinkMap[msg]; // 获取消息对应的链路索引
    auto& link = linkList[link_index]; // 获取相应的链路
    double now_probability = uniform(0, 1.0, rngNumber); // 生成一个当前的0~1之间的随机数
    std::string srcModuleFullPath = link.gatePair.first->getOwnerModule()->getFullPath(); // 获取源模块的全路径
    if(faultRate > now_probability){ // 故障率大于当前的随机数,那么就准备进行链路的断开
        // 首先我们判断链路是否处于连接的状态
        bool firstGateIsConnected = link.gatePair.first->isConnected();
        bool secondGateIsConnected = link.gatePair.second->isConnected();
        if(firstGateIsConnected && secondGateIsConnected){
            if(!this->judgeLinkSrcOrDestHasApps(link)){ // 进行链路的断开
                ChannelController::disconnect(link);
                link.state = 0;
                scheduleAt(simTime() + recoverInterval, link.upMessage);
            } else { // 选择另一条链路
                this->scheduleAt(simTime() + exponential(faultInterval), link.downMessage);
            }
        } else {// 如果链路本身就不处于连接的状态，那么我们隔一段时间再来进行一次检查
            this->scheduleAt(simTime() + exponential(faultInterval), link.downMessage);
        }
    } else {
        // 我们隔一段时间再来进行一次检查
        scheduleAt(simTime()+ exponential(faultInterval), link.downMessage);
    }
}

void ChannelController::generateDownMessageForLink(Link& satToSatLink){
    // downMessage and upMessage are used to simulate the link fault and recovery
    std::string downMessageInfo = std::string("down") + std::to_string(int(linkList.size()));
    std::string upMessageInfo = std::string("up") + std::to_string(int(linkList.size()));
    satToSatLink.downMessage = new cMessage(downMessageInfo.c_str());
    satToSatLink.upMessage = new cMessage(upMessageInfo.c_str());
    this->downMessageToLinkMap[satToSatLink.downMessage] = (int)linkList.size();
    this->upMessageToLinkMap[satToSatLink.upMessage] = (int)linkList.size();
    // schedule the first fault test message
    this->scheduleAt(1 + exponential(this->faultInterval),satToSatLink.downMessage);
}

void ChannelController::initializeAllEvents(){
    calculateLinkFailureInterval = this->par(PAR_FAULT_INTERVAL.c_str()).doubleValue();
    calculateLinkFailureEvent = new cMessage(MSG_CALCULATE_LINK_FAILURE.c_str());
    scheduleAt(simTime() + calculateLinkFailureInterval, calculateLinkFailureEvent);

    updatePositionInterval = this->par(PAR_UPDATE_POSITION_INTERVAL.c_str()).doubleValue();
    updatePositionEvent = new cMessage(MSG_UPDATE_POSITION.c_str());
    scheduleAt(simTime() + updatePositionInterval, updatePositionEvent);
}

void ChannelController::handleLinkFailureCalculateEvent(omnetpp::cMessage *msg) {
    double calculated_link_failure_rate = this->calculate_link_failure();
    std::cout << "link failure rate: " << calculated_link_failure_rate << std::endl;
}

void ChannelController::handleUpdatePositionEvent(omnetpp::cMessage *msg) {
    /**
     * @brief 处理位置更新的事件
     * @param msg 代表的是一个超时事件
     */
    // 进行 [卫星 ---> 卫星的星间链路] 的遍历
    for(const auto &item:satLinkMap){
        // 获取第一个元素模块
        cModule* satellite = item.first;
        // 获取这个卫星模块的移动模块
        auto *sMobi =  check_and_cast<SatMobility *>(satellite->getSubmodule("mobility"));
        // 进行位置的更新
        sMobi->refreshDisplay();
    }
    // 计划着下一次的超时事件
    scheduleAt(simTime()+updatePositionInterval, updatePositionEvent);
}

void ChannelController::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details){
    /**
     * @source 信号的发送方
     * @signalID 信号的ID
     * @obj 信号带的数据
     * @details 信号的详细信息
     */
    // 判断信号的类型
    if(signalID == leavePolarAreaSignal){
        // 当一个卫星要离开极地区域的时候，它将准备好进行跨轨道星间链路的建立
        auto *src = check_and_cast<cModule * >(obj)->getParentModule();
        // 进行这个状态表的更新
        notEnterPolarMap[src] = true;
        // 遍历这个卫星的所有的link
        for(const auto &linkIndex : satLinkMap[src]){
            // 只有是跨轨道星间链路，并且两个卫星都出了极区域才能够更新 link 的 state
            bool srcNotEnterPolar = notEnterPolarMap[linkList[linkIndex].srcMod];
            bool destNotEnterPolar = notEnterPolarMap[linkList[linkIndex].destMod];
            bool isInterOrbitLink = linkList[linkIndex].linkInfo == "inter-orbit";
            if(srcNotEnterPolar && destNotEnterPolar && isInterOrbitLink){
                // 进行 link 状态的更新
                linkList[linkIndex].state = 1;
                // 进行连接的创建
                createConnection(linkList[linkIndex]);
            }
        }
        refreshDisplay();
    }else if(signalID == enterPolarAreaSignal){
        // 当一个卫星要进入极区的时候，他将准备好进行跨轨道星间链路的断开
        auto *src = check_and_cast<cModule * >(obj)->getParentModule();
        // 首先将这颗卫星的状态进行更新 - 说明这颗卫星进入了极区
        notEnterPolarMap[src] = false;
        // 进行所有的链路的遍历
        for(const auto &linkIndex : satLinkMap[src]){
            // 判断是否是跨轨道星间链路
            bool isInterOrbitLink = linkList[linkIndex].linkInfo == "inter-orbit";
            if(!isInterOrbitLink){
                continue;
            }
            // 设置链路的状态为0
            linkList[linkIndex].state = 0;
            // 进行链路的关闭
            disconnect(linkList[linkIndex]);
        }
        refreshDisplay();
    }else if(signalID == checkSatToGroundSignal){
        // 如果是check星地链路
        auto *src = check_and_cast<cModule *>(obj)->getParentModule();
        checkSatToOtherLink(src);
        refreshDisplay();
    }
}

void ChannelController::disconnect(Link &link){
    /**
     * @param link 代表的是一个 link
     */
    link.gatePair.first->disconnect();
    link.gatePair.second->disconnect();
}

void ChannelController::createConnection(Link &link)
{
    /**
     * @param link 代表的是一个 link
     */
    bool theConnectivityOfFirstGate = false;
    bool theConnectivityOfSecondGate = false;
    theConnectivityOfFirstGate = link.gatePair.first->isConnected();
    theConnectivityOfSecondGate = link.gatePair.second->isConnected();
    std::string firstGateBaseName = link.gatePair.first->getBaseName();
    std::string secondGateBaseName = link.gatePair.second->getBaseName();
    int firstGateIndex = link.gatePair.first->getIndex();
    int secondGateIndex = link.gatePair.second->getIndex();
    if(theConnectivityOfFirstGate || theConnectivityOfSecondGate) {
        std::stringstream ss;
        ss << "Exisiting Connection between" << link.srcMod->getFullPath() << " and "<< link.destMod->getFullPath() << endl;
        throw cRuntimeError("%s", ss.str().c_str()); // NOLINT
    }
    // connect from source to dest
    // ----------------------------------------------------------------------------------------------------------------------------------------------
    cGate *srcGateHalf = link.srcMod->gateHalf(firstGateBaseName.c_str(), cGate::OUTPUT, firstGateIndex);
    cGate *destGateHalf = link.destMod->gateHalf(secondGateBaseName.c_str(), cGate::INPUT, secondGateIndex);
    cChannel *firstToSecondchannel = link.channelType->create("channel");
    srcGateHalf->connectTo(destGateHalf, firstToSecondchannel);
    // ----------------------------------------------------------------------------------------------------------------------------------------------

    // connect from dest to source
    // ----------------------------------------------------------------------------------------------------------------------------------------------
    cChannel *secondToFirstChannel = link.channelType->create("channel");
    srcGateHalf = link.destMod->gateHalf(secondGateBaseName.c_str(), cGate::OUTPUT, secondGateIndex);
    destGateHalf = link.srcMod->gateHalf(firstGateBaseName.c_str(), cGate::INPUT, firstGateIndex);
    srcGateHalf->connectTo(destGateHalf, secondToFirstChannel);
    // ----------------------------------------------------------------------------------------------------------------------------------------------
}

GatePair ChannelController::getGatePair(const cXMLElement *node)
{
    /**
     * @param node 代表的是 channel.xml 之中的一个 link
     */
    // 获取链路标签的 src 属性 - 如果不为空
    const char* sourceGatePath = node->getAttribute(ATTR_SRCGATE.c_str()); // ethg[0]
    const char* sourceModulePath = node->getAttribute(ATTR_SRCMODULE.c_str()); // src module
    if (strcmp(sourceGatePath, "") != 0) {

        // ------ 那么我们通过 getModuleByPath 进行 gate 的获取 -----
        cModule *srcModule = getModuleByPath(sourceModulePath);
        // ------ 那么我们通过 getModuleByPath 进行 gate 的获取 -----

        // -------------------------------进行门的名和索引的获取---------------------------------------
        std::pair<std::string, int> temp_pair = MultilayerTools::getNameAndIndex(sourceGatePath);
        std::string name = temp_pair.first;
        int index = temp_pair.second;
        // -------------------------------进行门的名和索引的获取---------------------------------------

        // -------------------------------检查src gate的类型---------------------------------------
        cGate::Type sourceGateType = srcModule->gateType(name.c_str());
        // 仅仅可能是输入输出门
        if (sourceGateType == cGate::INOUT) {
            // get the name of output half of the gate
            cGate *outputHalf = srcModule->gateHalf(name.c_str(), cGate::OUTPUT, index);
            // get the name of input half of the gate
            cGate *inputHalf = srcModule->gateHalf(name.c_str(), cGate::INPUT, index);
            // output half will connect to the other side of the link
            if (outputHalf->getNextGate() == nullptr || inputHalf->getPreviousGate() == nullptr){
                throw cRuntimeError("The specified gate (or the input or output half of it) is not connected"); // NOLINT
            }
            // 假设卫星1和卫星2连接，输出门的下一个门是卫星2的输入门，输入门的前一个门是卫星2的输出门
            if (outputHalf->getNextGate()->getOwnerModule() != inputHalf->getPreviousGate()->getOwnerModule()){ // NOLINT
                throw cRuntimeError("The specified gate (or the input or output half of it) is connected to a node on another level"); // NOLINT
            }
            return GatePair(outputHalf, inputHalf->getPreviousGate()); // NOLINT
        }
        else {
            throw cRuntimeError("'src-gate' must be an input and output gate"); // NOLINT
        }
        // -------------------------------检查src gate的类型---------------------------------------
    } else {
        throw cRuntimeError("Missing attribute: Either 'src-gate' or 'dest-module' must be present"); // NOLINT
    }
}


#endif

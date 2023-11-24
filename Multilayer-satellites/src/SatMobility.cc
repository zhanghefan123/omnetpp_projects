//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifdef WITH_OSG
#ifdef WITH_OSGEARTH

#include <sstream>
#include <iostream>
#include <osg/Node>
#include <osg/Texture>
#include <osg/LineWidth>
#include <osg/PolygonMode>
#include <osg/Depth>
#include <osg/PositionAttitudeTransform>
#include <osgEarth/Capabilities>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>
#include "omnetpp/osgutil.h"
#include "inet/common/INETMath.h"
#include "inet/common/geometry/common/Quaternion.h"
#include "inet/common/Simsignals.h"
#include "inet/projects/applications/zeusudpapp/UdpRequest.h"
#include "SatMobility.h"
#include "OsgEarthScene.h"
#include "ChannelController.h"
#include "ConstVars.h"

using namespace omnetpp;
using namespace inet;
using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;

Define_Module(SatMobility);

void SatMobility::setModelTree() {
    scene = OsgEarthScene::getInstance()->getScene(); // scene is initialized in stage 0 so we have to do our init in stage 1
    mapNode = osgEarth::MapNode::findMapNode(scene); // get map node from scene
    geoTransform = new osgEarth::GeoTransform(); // a GeoTransform allows positioning a model using world coordinates
    auto modelNode = osgDB::readNodeFile(modelURL); // load the model
    modelNode->getOrCreateStateSet()->setAttributeAndModes(
            new osg::Program(), osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    modelNode->getOrCreateStateSet()->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    auto pat = new osg::PositionAttitudeTransform(); // scale and rotate the model if necessary
    pat->setScale(osg::Vec3d(modelScale, modelScale, modelScale)); // set the scale of the model
    auto objectNode = new cObjectOsgNode(this);
    pat->addChild(objectNode); // 添加 objectNode
    objectNode->addChild(modelNode); // 添加 modelNode
    auto geode = new osg::Geode();
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    setLabelCharacters();
    geode->addDrawable(label);
    objectNode->addChild(geode);
    geoTransform->addChild(pat);
    // add the locator node to the scene
    scene->asGroup()->addChild(geoTransform);
}

void SatMobility::setCoverage() {
    /**
     * @brief 展示卫星的覆盖范围
     */
    if(this->display_coverage){
        if (!coneColor.empty()) {
            double orbitRadius = earthRadius + altitude; // in kilometers
            // the angle between the center of the earth and the horizon as seen from the satellite, in radians
            double alpha = std::asin(earthRadius / orbitRadius);
            // the distance of the horizon from the satellite, in meters
            horizonDistance = std::sqrt(orbitRadius * orbitRadius - earthRadius * earthRadius) * 1000;
            // double horizonDistance = std::sqrt(orbitRadius * orbitRadius - earthRadius * earthRadius) * 500;
            double coneHeight = std::sin(alpha)*horizonDistance;
            double coneRadius = std::cos(alpha)*horizonDistance;
            // the offset is to position the tip to the satellite
            auto *cone = new osg::Cone(osg::Vec3(0, 0, -coneRadius*0.75), coneHeight, coneRadius);
            osg::ref_ptr<osg::Geode> coneGeode = new osg::Geode;
            auto coneDrawable = new osg::ShapeDrawable(cone);
            coneDrawable->setColor(osgEarth::Color(coneColor));

            coneGeode->addDrawable(coneDrawable);
            coneGeode->getOrCreateStateSet()->setAttribute(new osg::PolygonMode(
                    osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));
            coneGeode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
            auto depth = new osg::Depth;
            depth->setWriteMask(false);
            coneGeode->getOrCreateStateSet()->setAttributeAndModes(depth, osg::StateAttribute::ON);
            geoTransform->addChild(coneGeode);
        }
    }
}

void SatMobility::setOrbit(){
    /**
     * @brief 展示卫星的轨道
     */
    // making the orbit circle
    if (!orbitColor.empty()) {
        osg::ref_ptr<osg::Geometry> orbitGeom = new osg::Geometry;
        osg::ref_ptr<osg::DrawArrays> drawArrayLines = new  osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP);
        osg::ref_ptr<osg::Vec3Array> vertexData = new osg::Vec3Array;

        orbitGeom->addPrimitiveSet(drawArrayLines);
        auto stateSet = orbitGeom->getOrCreateStateSet();
        stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
        stateSet->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
        stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
        stateSet->setAttributeAndModes(new osg::LineWidth(1.5), osg::StateAttribute::ON);
        stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        auto depth = new osg::Depth;
        depth->setWriteMask(false);
        stateSet->setAttributeAndModes(depth, osg::StateAttribute::ON);

        for (int i = 0; i <= 100; ++i)
            vertexData->push_back(getPositionAtPhase(i / 100.0 * M_PI*2));

        orbitGeom->setVertexArray(vertexData);
        drawArrayLines->setFirst(0);
        drawArrayLines->setCount(vertexData->size());

        osg::ref_ptr<osg::Vec4Array> colorData = new osg::Vec4Array;
        colorData->push_back(osgEarth::Color(orbitColor));
        orbitGeom->setColorArray(colorData, osg::Array::BIND_OVERALL);

        osg::ref_ptr<osg::Geode> orbitGeode = new osg::Geode;
        orbitGeode->addDrawable(orbitGeom.get());
        scene->asGroup()->addChild(orbitGeode);
    }
}

void SatMobility::setLabelCharacters() {
    /**
     * @brief 进行字体参数的设置
     */
    double spacing = 4; // 字体间距
    this->label = nullptr;
    auto font = osgText::Font::getDefaultFont();
    cModule *networkNode = getContainingNode(this);
    label = new osgText::Text();
    label->setCharacterSize(2);
    label->setBoundingBoxColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
    label->setBoundingBoxMargin(spacing);
    label->setColor(osgEarth::Color(labelColor));//
    label->setAlignment(osgText::Text::CENTER_CENTER);
    label->setText(networkNode->getFullName());
    label->setDrawMode(osgText::Text::TEXT);
    label->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    for (const auto& texture : font->getGlyphTextureList()) {
        texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
        texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    }
}

void SatMobility::setOrbitNormal() {
    std::string orbitNormalString = par(PAR_ORBIT_NORMAL.c_str());
    if (orbitNormalString.empty()){
        // it is not a correct spherical distribution, nor deterministic, but will do here
        normal.set(dblrand() * 2 - 1, dblrand() * 2 - 1, dblrand() * 2 - 1);
    }
    else {
        std::stringstream ss(orbitNormalString);

        /* std::istream::ignore Extract and discard characters. */
        double x, y, z;
        ss >> x;
        ss.ignore();
        ss >> y;
        ss.ignore();
        ss >> z;

        if (!ss)
            throw cRuntimeError("Couldn't parse orbit normal vector \"%s\", the correct format is for example \"2.5,3,0\", or leave it empty for random", orbitNormalString.c_str()); // NOLINT

        normal.set(x, y, z);
    }
    normal.normalize();
    auto c1 = normal ^ osg::Vec3d(0, 1, 0);
    auto c2 = normal ^ osg::Vec3d(1, 0, 0);
    osg::Vec3d &cross = c1.length2() < 0.0001 ? c2 : c1;
    cross.normalize();
    orbitX = cross;
    orbitY = normal ^ cross;
}

/*
 * Initializes satellite parameters: altitude, modelURL, modelScale.. and call OSG library files for 3D display
 */
void SatMobility::initialize(int stage)
{
    switch (stage) {
        case 0: {
            modelURL = par(PAR_MODEL_URL.c_str()).stringValue();
            modelScale = par(PAR_MODEL_SCALE.c_str());
            labelColor = par(PAR_LABEL_COLOR.c_str()).stringValue();
            altitude = par(PAR_ALTITUDE.c_str());
            phase = startingPhase = par(PAR_STARTING_PHASE.c_str()).doubleValue() * M_PI / 180.0;
            display_satellite_app = par(PAR_DISPLAY_SATELLITE_APP.c_str()).boolValue();
            display_coverage = par(PAR_DISPLAY_COVERAGE.c_str()).boolValue();
            setOrbitNormal();
            orbitColor = par(PAR_ORBIT_COLOR.c_str()).stringValue();
            coneColor = par(PAR_CONE_COLOR.c_str()).stringValue();
            controller = getModuleFromPar<cModule>(par("ChannelControllerModule"),this);
            /**
             * Set the 3D scene to be displayed. Note that osg::Node implements
             * reference counting, and setScene() increments the reference count.
             */
            getOsgCanvas()->setScene(osgDB::readNodeFile(modelURL));
            break;
        }
        case 1:{

            setModelTree();

            setOrbit();

            setCoverage();

            break;
        }
        default:
            break;
    }
}

void SatMobility::updatePosition()
{
    simtime_t t = simTime();
    if (t != lastPositionUpdateTime) {
        phase = startingPhase + t.dbl() * getOmega();
        pos = getPositionAtPhase(phase);
        osg::Vec3d v;
        mapNode->getMapSRS()->transformFromWorld(pos, v);
        geoTransform->setPosition(osgEarth::GeoPoint(mapNode->getMapSRS(), v));
        lastPosition = getPosition();
        lastPositionUpdateTime = t;
        emitMobilityStateChangedSignal();
        checkPolarAreaEntering();
        checkSatToGroundLink();
        // here we are going to get the app module
        if(this->display_satellite_app){
            cModule* udpApp = nullptr;
            udpApp = this->getParentModule()->getSubmodule("app",0);
            if(udpApp != nullptr){
                auto* udpRequestModule = dynamic_cast<UdpRequest*>(udpApp);
                if(udpRequestModule != nullptr){
                    std::string final_str = getContainingNode(this)->getFullName();
                    final_str += "\n";
                    final_str += std::to_string(udpRequestModule->getThroughput());
                    final_str += " Mbps";
                    final_str += "\n";
                    final_str += std::to_string(udpRequestModule->getSuccessfulRate());
                    final_str += "%";
                    this->label->setText(final_str);
                }
            }
        }
    }
}

void SatMobility::recorder(std::string filename)
{
    std::ofstream outfile;
    outfile.open(filename, std::ofstream::app);

    simtime_t time = simTime();                                      //get current time

    cModule *host = getContainingNode(this);                         //get nodes name

    double latitudes = getTransformPosition(lastPosition.x, lastPosition.y, lastPosition.z); //getCurrentPosition(latitude)
}

void SatMobility::checkSatToGroundLink()
{
    controller->emit(checkSatToGroundSignal,this);
}

void SatMobility::checkPolarAreaEntering()
{
    bool record = false;
    bool direct;
    simtime_t time = simTime();
    double latitude = getTransformPosition(lastPosition.x, lastPosition.y, lastPosition.z);
    if(latitude >= 66.32 && !isInPolarArea){
        isInPolarArea = true;
        controller->emit(enterPolarAreaSignal,this);
        std::cout<< simTime() << " s, " << getContainingNode(this)->getFullName() << " Enter Polar, latitude; " << latitude << endl;
    }else if(latitude >= 0 && latitude < 66.32 && isInPolarArea){
        isInPolarArea = false;
        controller->emit(leavePolarAreaSignal,this);
    }else if(latitude < 0 && latitude > -66.32 && isInPolarArea){
        isInPolarArea = false;
        controller->emit(leavePolarAreaSignal,this);
    }else if(latitude <= -66.32 && !isInPolarArea){
        isInPolarArea = true;
        controller->emit(enterPolarAreaSignal,this);
    }
}

/*   * get a geocentric coordinate system position    */
Coord SatMobility::getPosition()
{
    Coord position;

    position.x = pos.x();
    position.y = pos.y();
    position.z = pos.z();

    return position;
}

std::pair<double, double> SatMobility::getLatitudeAndLongitude(){
    double a, b, c, d, p, q, N;
    double Longitude;
    double Latitude;
    double Altitude;
    double x = lastPosition.x;
    double y = lastPosition.y;
    double z = lastPosition.z;

    a = 6371137.0;
    b = 6371752.31424518;

    c = std::sqrt(((a * a) - (b * b)) / (a * a));
    d = std::sqrt(((a * a) - (b * b)) / (b * b));
    p = std::sqrt((x * x) + (y * y));
    q = std::atan2((z * a), (p * b));

    Longitude = std::atan2(y, x);
//     Latitude = std::atan2((z + (d * d) * b * std::pow(std::sin(q), 3)), (p - (c * c) * a * std::pow(std::cos(q), 3)));
    Latitude = std::atan2(z, p);

    N = a / std::sqrt(1 - ((c * c) * std::pow(std::sin(Latitude), 2)));
    Altitude = (p / std::cos(Latitude)) - N;

    Longitude = Longitude * 180.0 / osg::PI;
    Latitude = Latitude * 180.0 / osg::PI;

    std::pair<double, double> pair = std::make_pair(Latitude,Longitude);
    return pair;
}


double SatMobility::getTransformPosition(double x, double y, double z)
{
     double a, b, c, d, p, q, N;
     double Longitude;
     double Latitude;
     double Altitude;

     a = 6371137.0;
     b = 6371752.31424518;

     c = std::sqrt(((a * a) - (b * b)) / (a * a));
     d = std::sqrt(((a * a) - (b * b)) / (b * b));
     p = std::sqrt((x * x) + (y * y));
     q = std::atan2((z * a), (p * b));

     Longitude = std::atan2(y, x);
//     Latitude = std::atan2((z + (d * d) * b * std::pow(std::sin(q), 3)), (p - (c * c) * a * std::pow(std::cos(q), 3)));
     Latitude = std::atan2(z, p);

     N = a / std::sqrt(1 - ((c * c) * std::pow(std::sin(Latitude), 2)));
     Altitude = (p / std::cos(Latitude)) - N;

     Longitude = Longitude * 180.0 / osg::PI;
     Latitude = Latitude * 180.0 / osg::PI;

     return Latitude;
 }

osg::Vec3 SatMobility::getPositionAtPhase(double alpha) const
{
    return (orbitX * std::cos(alpha) + orbitY * std::sin(alpha)) * (earthRadius + altitude) * 1000;
}

void SatMobility::refreshDisplay() const
{

    const_cast<SatMobility *>(this)->updatePosition();
    // update the position on the 2D canvas
    getDisplayString().setTagArg("p", 0, 300 + pos.x() / 100000);
    getDisplayString().setTagArg("p", 1, 300 - pos.y() / 100000);
}

Coord& SatMobility::getCurrentPosition()
{
    return lastPosition;
}

void SatMobility::handleMessage(cMessage *msg)
{
    throw cRuntimeError("Not supposed to be called");
}
#endif // WITH_OSGEARTH
#endif // WITH_OSG

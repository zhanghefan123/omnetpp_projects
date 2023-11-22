//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#if defined(WITH_OSG) && defined(WITH_OSGEARTH)

#include "HAPMobility.h"
#include "OsgEarthScene.h"
#include "ChannelController.h"
#include "omnetpp/osgutil.h"

#include <sstream>
#include <iomanip>
#include <iostream>

#include "omnetpp/osgutil.h"

#include <osg/Node>
#include <osg/Texture>
#include <osg/LineWidth>
#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/Depth>
#include <stdlib.h>
#include <osg/PositionAttitudeTransform>
#include <osgEarth/Capabilities>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>

#include "inet/common/INETMath.h"
#include "inet/common/geometry/common/Quaternion.h"

using namespace omnetpp;
using namespace inet;

Define_Module(HAPMobility)

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;

/*
 * Initializes nodes parameters: altitude, modelURL, modelScale.. and call OSG library files for 3D display
 */
void HAPMobility::initialize(int stage)
{
    switch (stage) {
    case 0: {
        modelURL = par("modelURL").stringValue();
        modelScale = par("modelScale");
        labelColor = par("labelColor").stringValue();
        longitude = par("longitude");
        latitude = par("latitude");
        altitude = par("altitude");
        altitude *= 1000;

        waitTimeParameter = &par("waitTime");
        hasWaitTime = waitTimeParameter->isExpression() || waitTimeParameter->doubleValue() != 0;
        speedParameter = &par("speed");
        stationary = !speedParameter->isExpression() && speedParameter->doubleValue() == 0;

        moveTimer = new cMessage("move");
        updateInterval = par("updateInterval");
        faceForward = par("faceForward");
        /**
         * Set the 3D scene to be displayed. Note that osg::Node implements
         * reference counting, and setScene() increments the reference count.
         */
        getOsgCanvas()->setScene(osgDB::readNodeFile(modelURL));

        break;
    }
    case 1:

        auto scene = OsgEarthScene::getInstance()->getScene(); // scene is initialized in stage 0 so we have to do our init in stage 1
        mapNode = osgEarth::MapNode::findMapNode(scene);

        // build up the node representing this module
        // a GeoTransform allows positioning a model using world coordinates
        geoTransform = new osgEarth::GeoTransform();

        auto modelNode = osgDB::readNodeFile(modelURL);

        modelNode->getOrCreateStateSet()->setAttributeAndModes(
          new osg::Program(), osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
        modelNode->getOrCreateStateSet()->setMode(
                  GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);

        // scale and rotate the model if necessary
        auto pat = new osg::PositionAttitudeTransform();
        pat->setScale(osg::Vec3d(modelScale, modelScale, modelScale));

        auto objectNode = new cObjectOsgNode(this);
        pat->addChild(objectNode);
        objectNode->addChild(modelNode);
        double spacing = 4;
        osgText::Text *label = nullptr;
        auto font = osgText::Font::getDefaultFont();
        label = new osgText::Text();
        label->setCharacterSize(2);
        label->setBoundingBoxColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
        label->setBoundingBoxMargin(spacing);
        label->setColor(osgEarth::Color(labelColor));
        label->setAlignment(osgText::Text::CENTER_CENTER);
        label->setText(par("label").stringValue());
        label->setDrawMode(osgText::Text::TEXT);
        label->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
        for (auto texture : font->getGlyphTextureList()) {
            texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
            texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
        }
        auto geode = new osg::Geode();
        geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
        geode->addDrawable(label);
        objectNode->addChild(geode);
        geoTransform->addChild(pat);
        scene->asGroup()->addChild(geoTransform);

        nextChange = simTime();
        osg::Vec3d geoPosition(longitude, latitude, altitude);
        currentGeoPosition = geoPosition;
        lastPosition = transformToXYZ (geoPosition);
        setTargetPosition();
        timeOut = 0.01;
        timeOutEvent = new cMessage("timeOutEvent");
        scheduleAt(simTime() + timeOut, timeOutEvent);
        break;
    }
//    lastUpdate = simTime();

}

void HAPMobility::scheduleUpdate()
{
    cancelEvent(moveTimer);
    if(!stationary && updateInterval != 0){
        // periodic update is needed
        simtime_t nextUpdate = simTime() + updateInterval;
        if (nextChange != -1 && nextChange < nextUpdate)
            // next change happens earlier than next update
            scheduleAt(nextChange, moveTimer);
        else
            // next update happens earlier than next change or there is no change at all
            scheduleAt(nextUpdate, moveTimer);
    }
    else if (nextChange != -1)
        // no periodic update is needed
        scheduleAt(nextChange, moveTimer);
}

Coord HAPMobility::getRandomPos()
{
    Coord p;
//    auto aboveSurfaceAltitude = altitude;//(earthRadius + altitude) * 1000;
    auto geoP = transformToXYZ(currentGeoPosition); // transform geographic location to xyz
    p.x = uniform(geoP.x, geoP.x + 60000); //x value
    p.y = uniform(geoP.y, geoP.y + 60000); //y value
    p.z = uniform(geoP.z, geoP.z + 2000); //altitude value
    return p;
}

void HAPMobility::setTargetPosition()
{
    if (nextMoveIsWait) {
        simtime_t waitTime = waitTimeParameter->doubleValue();
        nextChange = simTime() + waitTime;
        nextMoveIsWait = false;
    }
    else {
        targetPosition = getRandomPos();
        double speed = speedParameter->doubleValue();
        double distance = lastPosition.distance(targetPosition);
        simtime_t travelTime = distance / speed;
        nextChange = simTime() + travelTime;
        nextMoveIsWait = hasWaitTime;
    }
}

void HAPMobility::move()
{
    simtime_t now = simTime();
    if (now == nextChange) {
        setTargetPosition();
        lastPosition = targetPosition;
        std::cout << "reached current target position = " << lastPosition.x << endl;
        EV_INFO << "new target position = " << targetPosition << ", next change = " << nextChange << endl;
        lastVelocity = (targetPosition - lastPosition) / (nextChange - simTime()).dbl();
    }
    else if (now > lastUpdate) {
        ASSERT(nextChange == -1 || now < nextChange);
        setTargetPosition();
        lastPosition = targetPosition;
        lastVelocity = (targetPosition - lastPosition) / (nextChange - simTime()).dbl();
//        lastPosition += lastVelocity * (now - lastUpdate).dbl();
    }
}

void HAPMobility::orient()
{
    if (faceForward) {
        // determine orientation based on direction
        if (lastVelocity != Coord::ZERO) {
            Coord direction = lastVelocity;
            direction.normalize();
            auto alpha = rad(atan2(direction.y, direction.x));
            auto beta = rad(-asin(direction.z));
            auto gamma = rad(0.0);
            lastOrientation = Quaternion(EulerAngles(alpha, beta, gamma));
        }
    }
}

double HAPMobility::getMaxSpeed()
{
    return speedParameter->isExpression() ? NaN : speedParameter->doubleValue();
}

void HAPMobility::updatePosition()
{
    simtime_t t = simTime();
    if (t != lastPositionUpdateTime) {
        position = getPosition();
        osg::Vec3d geoPos = transformXYZToGeographicPosition(position.x, position.y, position.z);
        longitude = geoPos.x();
        latitude = geoPos.y();
        geoTransform->setPosition(osgEarth::GeoPoint(mapNode->getMapSRS(), geoPos));
        lastPositionUpdateTime = t;
    }
}

Coord HAPMobility::getPosition()
{
    std::cout<<lastPosition.x<<" "<<lastPosition.y<<" "<<lastPosition.z<<endl;
    return lastPosition;

}

void HAPMobility::refreshDisplay() const
{
    const_cast<HAPMobility *>(this)->updatePosition();

//    geoTransform->setPosition(osgEarth::GeoPoint(mapNode->getMapSRS(), longitude, latitude, altitude));
}

void HAPMobility::handleMessage(cMessage *msg)
{
    if(msg == timeOutEvent){
        moveAndUpdate();
        scheduleUpdate();
    }
}

void HAPMobility::moveAndUpdate()
{
    refreshDisplay();
    simtime_t now = simTime();
    if (nextChange == now || lastUpdate != now) {
        move();
        orient();
        lastUpdate = simTime();
        emitMobilityStateChangedSignal();
    }
}

/**
*  transform to geocentric coordinate system position.
*/
Coord HAPMobility::transformToXYZ (osg::Vec3d geoPosition)
{
    osg::Vec3d output;
    mapNode->getMapSRS()->transformToWorld(geoPosition, output);
    return Coord(output.x(),output.y(),output.z());
}

osg::Vec3d HAPMobility:: transformXYZToGeographicPosition(double x, double y, double z)
{
    osg::Vec3d v,nowxyz(x,y,z);
    mapNode->getMapSRS()->transformFromWorld(nowxyz, v);
    return v;
 }

const Coord& HAPMobility::getCurrentPosition()
{
    moveAndUpdate();
    return lastPosition;
}

const Coord& HAPMobility::getCurrentVelocity()
{
    moveAndUpdate();
    return lastVelocity;
}

const Quaternion& HAPMobility::getCurrentAngularPosition()
{
    moveAndUpdate();
    return lastOrientation;
}

const Quaternion& HAPMobility::getCurrentAngularVelocity()
{
    moveAndUpdate();
    return lastAngularVelocity;
}
#endif // WITH_OSG

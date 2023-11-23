//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#if defined(WITH_OSG) && defined(WITH_OSGEARTH)

#include "GroundNodeMobility.h"
#include "OsgEarthScene.h"
#include "omnetpp/osgutil.h"

#include <osg/Node>
#include <osg/Texture>
#include <osg/LineWidth>
#include <osg/PolygonMode>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/PositionAttitudeTransform>
#include <osgEarth/Capabilities>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthSymbology/Geometry>
#include <osgEarthFeatures/Feature>

/*
 * header file for coordinate transfer.
 */
#include "inet/common/INETMath.h"
#include "inet/common/geometry/common/GeographicCoordinateSystem.h"
#include "inet/common/geometry/common/Quaternion.h"

using namespace omnetpp;
using namespace inet;

Define_Module(GroundNodeMobility)

using namespace osgEarth;
using namespace osgEarth::Annotation;
using namespace osgEarth::Features;

void GroundNodeMobility::initialize(int stage)
{
    switch (stage) {
        case 0: {
            timeStep = par("timeStep");
            modelURL = par("modelURL").stringValue();
            modelScale = par("modelScale");
            labelColor = par("labelColor").stringValue();
            longitude = par("longitude");
            latitude = par("latitude");
            altitude = par("altitude");
            altitude *= 1000;
            getOsgCanvas()->setScene(osgDB::readNodeFile(modelURL));
            break;
        }
        case 1:
        {
            auto scene = OsgEarthScene::getInstance()->getScene(); // scene is initialized in stage 0 so we have to do our init in stage 1
            auto rotator = OsgEarthScene::getInstance()->getRotator();
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
            rotator->asGroup()->addChild(geoTransform);
            osg::Vec3d input(longitude,latitude,altitude),output;
            mapNode->getMapSRS()->transformToWorld(input, output);
            lastPosition.x = output.x();
            lastPosition.y = output.y();
            lastPosition.z = output.z();
            geoTransform->setPosition(osgEarth::GeoPoint(mapNode->getMapSRS(), longitude,latitude,altitude));
            EV << "GroundStation : (x,y,z) = " << lastPosition.x << "," << lastPosition.y << "," << lastPosition.z << endl;
            // position the nodes, so we will see them at correct position right after initialization
            break;
        }
        default:
        {
            break;
        }
    }
}

/*
 * A geographic coordinate system model maps scene coordinates to geocentric coordinate system
 */

void GroundNodeMobility::refreshVisuals()
{
}

Coord& GroundNodeMobility::getCurrentPosition()
{
    osg::Vec3d point(geoTransform->getBound().center());
    point = point * osg::computeLocalToWorld(mapNode->getParentalNodePaths()[0]);
    lastPosition = Coord(point.x(),point.y(),point.z());
    return lastPosition;
}
#endif // WITH_OSG


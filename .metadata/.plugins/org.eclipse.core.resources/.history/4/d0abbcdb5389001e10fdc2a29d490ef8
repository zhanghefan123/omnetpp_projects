//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __TERNETMOBILITY_H__
#define __TERNETMOBILITY_H__

#include <omnetpp.h>
#include "OsgEarthScene.h"

#include <osgEarth/MapNode>
#include <osgEarth/GeoTransform>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/FeatureNode>
#include "inet/common/INETDefs.h"

#include "inet/common/geometry/common/Coord.h"
#include "inet/common/geometry/common/Quaternion.h"
#include "inet/mobility/base/MobilityBase.h"

#include "inet/common/geometry/common/CanvasProjection.h"
#include "inet/common/geometry/common/EulerAngles.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/StringFormat.h"

using namespace omnetpp;
using namespace inet;

/**
 * A mobile node (with a 3D model) moving around . A range indicator, and the
 * model's track can be shown along with its label.
 */
class terNetMobility : public MobilityBase
{
  protected:
    // configuration
    double timeStep;
    unsigned int trailLength;
    std::string labelColor;
    std::string rangeColor;
    std::string trailColor;
    std::string modelURL;
    double modelScale;

    Coord position;

    // the node containing the osgEarth data
    osg::observer_ptr<osgEarth::MapNode> mapNode = nullptr;
    // osgEarth node for 3D visualization
    osgEarth::GeoTransform *geoTransform = nullptr;

    double longitude = -70, latitude = 40, altitude = 400;
//    double Lon=longitude;
//    double Lat=latitude;
//    double Alt=altitude;

  public:

    osg::Vec3d getGeoPosition() { return osg::Vec3d(longitude, latitude, altitude); }

    /*A geographic coordinate system model maps scene coordinates to geocentric coordinate system.*/
    virtual Coord getTransformPosition();

    osg::Node *getLocatorNode() { return geoTransform; };

    /** @brief Initializes the position from the display string or from module parameters. */
//    static int BLH2xyz(double Lon, double Lat, double Alt, double x, double y, double z);

    virtual Quaternion& getCurrentAngularPosition() override { return lastOrientation; }
    virtual Quaternion& getCurrentAngularVelocity() override { return Quaternion::IDENTITY; }
    virtual Quaternion& getCurrentAngularAcceleration() override { return Quaternion::IDENTITY; }

    virtual const Coord& getCurrentPosition() override;
    virtual const Coord& getCurrentVelocity() override { return Coord::ZERO; }
    virtual const Coord& getCurrentAcceleration() override { return Coord::ZERO; }

    virtual double getMaxSpeed() const override { return 0; }

    virtual const Coord& getConstraintAreaMax() const override { return lastPosition; }
    virtual const Coord& getConstraintAreaMin() const override { return lastPosition; }

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return 2; }
//    virtual void handleMessage(cMessage *msg) override;
    virtual void handleSelfMessage(cMessage *message) override { throw cRuntimeError("Invalid operation"); }

    virtual void refreshVisuals();
};

#endif

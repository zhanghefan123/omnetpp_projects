//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __SATMOBILITY_H__
#define __SATMOBILITY_H__

#include <omnetpp.h>
#include "OsgEarthScene.h"


#include <osgEarth/MapNode>
#include <osgEarth/GeoTransform>
#include <osgEarthAnnotation/CircleNode>
#include <osgEarthAnnotation/FeatureNode>
#include "inet/common/INETDefs.h"

#include "inet/common/geometry/common/GeographicCoordinateSystem.h"

#include "inet/common/geometry/common/Coord.h"
#include "inet/common/geometry/common/Quaternion.h"
#include "inet/mobility/base/MobilityBase.h"

using namespace omnetpp;
using namespace inet;

/**
 * Satellite model. See NED file for details.
 */
class ChannelController;
class SatMobility : public MobilityBase
{
  public:
    // zhf add code
    osgText::Text *label;
    bool display_satellite_app = false;
    bool display_coverage = false;


  protected:
    // configuration
    double startingPhase;
    std::string labelColor;
    std::string modelURL;
    double modelScale;

    // the node containing the osgEarth data
    osg::observer_ptr<osgEarth::MapNode> mapNode = nullptr;

    // osgEarth node for 3D visualization
    osgEarth::GeoTransform *geoTransform = nullptr;

    cModule * controller = nullptr;
    const double mu = 398600.4418; // "geocentric gravitational constant" - source: wikipedia, units: km^3 / s^2
    const double earthRadius = 6371; // in km

    double altitude = 10000; // in km, above the surface
    double phase = 0; // on the orbit, in radians, unbounded
    osg::Vec3d normal = osg::Vec3d(0, 0, 1); // doesn't have to be unit length, just can't be 0
    osg::Vec3d orbitX, orbitY; // the base of the orbit plane, orthogonal, and both are unit length, computed from the normal
    osg::Vec3d pos;
    double Omega;
    double theta, fai;
    double horizonDistance;

    /** @brief The next simulation time when the mobility module needs to update its internal state.
     *
     * The -1 value turns off sending a self message for the next mobility state change.
     */
    simtime_t lastPositionUpdateTime = -1;
    bool isInPolarArea = false;
    simtime_t timeout;  // timeout
    cMessage *timeOutEvent;  // holds pointer to the timeout self-message

  public:
    virtual ~SatMobility();

    Coord position;

    double getHorizonDistance() const{ return horizonDistance; };
    /** @brief  get the node geotransform information. */
    osg::Node *getLocatorNode() { return geoTransform; };

    /** A  geocentric coordinate system model maps scene coordinates to geographic coordinate system */
    double getTransformPosition(double x, double y, double z);

    std::pair<double, double> getLatitudeAndLongitude();

    /** @brief  update the satellite position. */
    void updatePosition();

    /** @brief handleSelfMessage setting. */
    void handleSelfMessage(cMessage *message) override { throw cRuntimeError("Invalid operation"); }

    /** @brief Get angular velocity in rad/sec??. */
    Quaternion& getCurrentAngularVelocity() override { return Quaternion::IDENTITY; }

    /** @brief get some parameters which in EulerAngles form. */
    Quaternion& getCurrentAngularPosition() override { return lastOrientation; };
    Quaternion& getCurrentAngularAcceleration() override { return Quaternion::IDENTITY; }


    /** @brief Achieve the satellite current position that can be used in constanttimePropagation. */
//    virtual Coord getCurrentPosition() override { return lastPosition; }
    virtual Coord& getCurrentPosition() override;

    /** @brief Useless functions in satellite networks. */
    const Coord& getCurrentVelocity() override { return Coord::ZERO; }
    const Coord& getCurrentAcceleration() override { return Coord::ZERO; }
    double getMaxSpeed() const override { return 0; }

  protected:

    /** @brief angular velocity in rad/sec. */
    double getOmega()
    {
        Omega=std::sqrt(mu / std::pow(altitude + earthRadius, 3));
        return Omega;
    }

    // in world coordinates, units is meters, phase is the angle on the orbit in radians

    /** @brief Don't know its meaning!! */
    osg::Vec3 getPositionAtPhase(double alpha) const;

    /** @brief Initialize the satellite parameters, has two stages.*/
    void initialize(int stage) override;
    int numInitStages() const override { return 2; }

    /*A new function can be used to get the nodes' position.*/
    virtual Coord getPosition();

    void recorder(std::string filename);

    void checkPolarAreaEntering();
    void checkSatToGroundLink();

    /** @brief handleMessage.*/
    void handleMessage(cMessage *msg) override;

    /** @brief Moves the visual representation module's icon to the new position on the screen.*/
    void refreshDisplay() const override;
};

#endif

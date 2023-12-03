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
#include "inet/projects/generic_tools/global_module/GlobalModule.h"

using namespace omnetpp;
using namespace inet;

/**
 * Satellite model. See NED file for details.
 */
class ChannelController;
class SatMobility : public MobilityBase
{
  private:
    // configure parameters
    std::string modelURL;
    double modelScale;
    std::string labelColor;
    double altitude = 10000; // in km, above the surface
    double phase; // on the orbit, in radians, unbounded
    double startingPhase;
    std::string orbitColor;
    std::string coneColor;
    osg::Node* scene;
    double horizonDistance;
    bool currentInPolarArea = false;
    osgText::Text *label;
    bool display_satellite_app = false;
    bool display_coverage = false;
    GlobalModule* globalModule = nullptr;
    ChannelController* controller = nullptr;
    bool shouldCheckPolarAreaEnter = false;
    bool checkSatToOtherLinkFlag = true;
public:
    void checkSatToOtherLink();
    void checkPolarAreaEntering();
    void setGlobalModule();
    void setChannelController();
    void setModelTree();
    void setOrbitNormal();
    void setLabelCharacters();
    void setOrbit();
    void setCoverage();
    void setAppLabel();
    Coord& getCurrentPosition() override;
    Coord calculatePosition();
    void initializePars();
    void initializeScene();

  protected:
    // the node containing the osgEarth data
    osg::observer_ptr<osgEarth::MapNode> mapNode = nullptr;

    // osgEarth node for 3D visualization
    osgEarth::GeoTransform *geoTransform = nullptr;
    const double mu = 398600.4418; // "geocentric gravitational constant" - source: wikipedia, units: km^3 / s^2
    const double earthRadius = 6371; // in km

    osg::Vec3d normal = osg::Vec3d(0, 0, 1); // doesn't have to be unit length, just can't be 0
    osg::Vec3d orbitX, orbitY; // the base of the orbit plane, orthogonal, and both are unit length, computed from the normal
    osg::Vec3d pos;
    double Omega;

    /** @brief The next simulation time when the mobility module needs to update its internal state.
     *
     * The -1 value turns off sending a self message for the next mobility state change.
     */
    simtime_t lastPositionUpdateTime = -1;

  public:
    ~SatMobility() override = default;
    void refreshDisplay() const override;
    double getHorizonDistance() const{ return horizonDistance; };
    /** @brief  get the node geotransform information. */
    osg::Node *getLocatorNode() { return geoTransform; };

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

    /** @brief handleMessage.*/
    void handleMessage(cMessage *msg) override;
};

#endif

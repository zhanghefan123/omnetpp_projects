//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef __HAPMOBILITY_H__
#define __HAPMOBILITY_H__

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
 * High platform nodes' mobility model.
 */
class HAPMobility : public MobilityBase
{
  protected:
    // configuration
    std::string modelURL;
    double modelScale;
    std::string labelColor;
    double startingPhase;

    //node's location parameter
    double longitude = -70;
    double latitude = 40;
    double altitude = 1000; // in km, above the surface

    //node's mobility  parameter
    bool nextMoveIsWait;
    cPar *speedParameter = nullptr;
    cPar *waitTimeParameter = nullptr;
    bool hasWaitTime;

    /** @brief A mobility model may decide to become stationary at any time.
     * The true value disables sending self messages. */
    bool stationary = false;

    /** @brief The next simulation time when the mobility module needs to update its internal state.
     * The -1 value turns off sending a self message for the next mobility state change. */
    simtime_t nextChange;

    Coord position;
    osg::Vec3d currentGeoPosition;

    /** @brief End position of current linear movement. */
    Coord targetPosition;
    osg::Vec3d targetGeoPosition;
    /** @brief The last velocity that was reported at lastUpdate. */
    Coord lastVelocity = Coord::ZERO;

    /** @brief The simulation time when the mobility state was last updated. */
    simtime_t lastUpdate = 0;

    /** @brief The message used for mobility state changes. */
    cMessage *moveTimer = nullptr;

    /** @brief The simulation time interval used to regularly signal mobility state changes.
     *
     * The 0 value turns off the signal. */
    simtime_t updateInterval = 0;

    bool faceForward = false;

    /** @brief The last angular velocity that was reported at lastUpdate. */
    Quaternion lastAngularVelocity;

    // the node containing the osgEarth data
    osg::observer_ptr<osgEarth::MapNode> mapNode = nullptr;

    // osgEarth node for 3D visualization
    osgEarth::GeoTransform *geoTransform = nullptr;

    simtime_t lastPositionUpdateTime = -1;
    simtime_t timeOut;
    cMessage *timeOutEvent;

  public:
    /** @brief  get the node geotransform information. */
    osg::Node *getLocatorNode() { return geoTransform; };

    /** @brief  update the node position. */
    void updatePosition();

    /** @brief handleSelfMessage setting. */
    virtual void handleSelfMessage(cMessage *message) override { throw cRuntimeError("Invalid operation"); }

    virtual const Coord& getCurrentPosition() override;
    virtual const Coord& getCurrentVelocity() override;
    virtual const Coord& getCurrentAcceleration() override { throw cRuntimeError("Invalid operation"); }

    virtual const Quaternion& getCurrentAngularPosition() override;
    virtual const Quaternion& getCurrentAngularVelocity() override;
    virtual const Quaternion& getCurrentAngularAcceleration() override { throw cRuntimeError("Invalid operation"); }

    //node's mobility function.
    void setTargetPosition();
    void moveAndUpdate();
    void move();
    void orient();
    double getMaxSpeed();

    /** @brief get a random position */
    Coord getRandomPos();

    Coord transformToXYZ (osg::Vec3d geoPosition);

    /** A  geocentric coordinate system model maps scene coordinates to geographic coordinate system */
    osg::Vec3d  transformXYZToGeographicPosition(double x, double y, double z);

    /** @brief Initialize the satellite parameters, has two stages.*/
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return 2; }

    /*A new function can be used to get the nodes' position.*/
    virtual Coord getPosition();

    /** @brief Schedules the move timer that will update the mobility state. */
    void scheduleUpdate();

    //recorder the nodes' position to txt file.
    void recorder(std::string filename);

    /** @brief handleMessage.*/
    virtual void handleMessage(cMessage *msg) override;

    /** @brief Moves the visual representation module's icon to the new position on the screen.*/
    virtual void refreshDisplay() const override;
};

#endif

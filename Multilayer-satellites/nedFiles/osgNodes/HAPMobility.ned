//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// Represents a satellite ground station at the given longitude/latitude.
//

package nedFiles.osgNodes;

import inet.mobility.base.MobilityBase;

module HAPMobility extends MobilityBase
{
    parameters:
        @signal[mobilityStateChanged](type=HAPMobility);
        // 3D model parameters
        string modelURL;                               // the URL/filename of the 3D model to be used for the node
        double modelScale = default(1);
        // decorations and annotations
        string labelColor = default("#000000ff");      // the color of the model label in hex RRGGBBAA format or "" to turn off labels
 
        double longitude;
        double latitude;
        double altitude @unit("km"); // above sea level
        string label;   
 
        volatile double speed @unit(mps) = default(mps); // use uniform(minSpeed, maxSpeed) or another distribution
        volatile double waitTime @unit(s) = default(0s); // wait time between reaching a target and choosing a new one
        double updateInterval @unit(s) = default(1s); // the simulation time interval used to regularly signal mobility state changes and update the display
        bool faceForward = default(true);
        @class(HAPMobility);
}

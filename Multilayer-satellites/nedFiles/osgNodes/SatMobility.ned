//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// Represents a satellite. Loads the 3D model from the given file, and 
// moves it along the specified orbit.
//
package nedFiles.osgNodes;

import inet.mobility.base.MobilityBase;

module SatMobility extends MobilityBase
{
    parameters:
        @signal[mobilityStateChanged](type=SatMobility);
        // 3D model parameters
        string modelURL;                               // the URL/filename of the 3D model to be used for the node
        string ChannelControllerModule;
        double modelScale = default(50000);
        bool displaySatelliteApp = default(false);
        bool displayCoverage = default(false);
        // decorations and annotations
        string labelColor = default("#000000ff");      // the color of the model label in hex RRGGBBAA format or "" to turn off labels
        string orbitColor = default("#80C8C8C8");      // the color of the orbit circle in hex RRGGBBAA, or "" to hide the orbit
        string coneColor = default("#FFFFFF16");       // the color of the range cone in hex RRGGBBAA, or "" to hide the cone
        
        double altitude @unit("km") = default(5000km); // above sea level
        string orbitNormal = default("");              // can't be zero length, for example: "2.5,3,0", or leave it empty for a random orbit plane
        double startingPhase @unit("deg") = default(0deg);     
                
        double updateInterval @unit(s) = default(10s); // the simulation time interval used to regularly signal mobility state changes and update the display
        bool faceForward = default(true);
        bool checkSatToOtherLinkFlag = default(true);
        @class(SatMobility);      
}

//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

//
// This module is responsible for tracking the distances of mobile nodes,
// and visualizing the connectivity graph via osgEarth.
//
package nedFiles.osgNodes;

simple ChannelController
{
    @signal[enterPolarAreaSignal](type=ChannelController);
    @signal[leavePolarAreaSignal](type=ChannelController);
    @signal[checkSatToGroundSignal](type=ChannelController);
    @display("i=block/network2");
    string satToSatColor = default("#00FF00BF");
    string satToSatAnotherColor = default("#FF4020DF");
    double satToSatWidth = default(2);
    
    string satToGroundColor = default("#FFBF00BF");
    double satToGroundWidth = default(2);
    
    string satToterNetColor = default("#FEBF00BF");
    double satToterNetWidth = default(2);
    

    string satToHighColor = default("#FCBF00BF");
    double satToHighWidth = default(2);
    
    string groundToHighColor = default("#FCBF00CF");
    double groundToHighWidth = default(2);
    
    double faultRate = default(0);
    int faultInterval = default(20);
    int recoverInterval = default(5);

    int rngNumber = default(1);
    
    xml config = default(xml("<config></config>"));

    double calculatePositionInterval = default(0.01);
    double calculateLinkFailureInterval = default(10);
}

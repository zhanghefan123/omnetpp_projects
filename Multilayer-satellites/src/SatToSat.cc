//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
#include "inet/common/geometry/common/Coord.h"
#include "SatToSat.h"
#include <cmath>
Register_Class(SatToSat);

void SatToSat::initialize()
{
        cDatarateChannel::initialize(); // NOLINT
        displayAsTooltip = par("displayAsTooltip");
        fmt = par("thruputDisplayFormat");
        host = getContainingNode(getSourceGate()->getOwnerModule()); //get the containing node LEO XX and let it subscribe the signal
        initialized = true;
}
void SatToSat::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj, cObject *details){
    Enter_Method("SatToSatThruputMeteringChannel::receiveSignal");
}

double SatToSat::getDistance(){
    if(!initialized){
        initialized = true;
        host = getContainingNode(getSourceGate()->getOwnerModule()); //get the containing node LEO XX and let it subscribe the signal
        std::cout<<getFullPath()<<" initialize in the function of getDistance()"<<std::endl;
    }
    cGate *source,*dest;
    source = getSourceGate();
    dest = source->getNextGate() == nullptr ? source->getPreviousGate() : source->getNextGate();
    cModule *sourceNode,*destNode;
    sourceNode = source->getOwnerModule();
    destNode = dest->getOwnerModule();
    std::string sourceStr = sourceNode->getFullPath();
    std::string destStr = destNode->getFullPath();
    sourceStr += ".mobility";
    destStr += ".mobility";
    cModule *sourceModule = sourceNode->getModuleByPath(sourceStr.c_str());
    cModule *destModule = destNode->getModuleByPath(destStr.c_str());
    SatMobility *sMobi =  check_and_cast<SatMobility *>(sourceModule);
    SatMobility *dMobi = check_and_cast<SatMobility *>(destModule);
    sMobi->updatePosition();
    dMobi->updatePosition();
    Coord sLoc = sMobi->getCurrentPosition() , dLoc = dMobi->getCurrentPosition();
    double x1,x2,y1,y2,z1,z2,xDis,yDis,zDis,distance;
    x1 = sLoc.getX();
    x2 = dLoc.getX();
    y1 = sLoc.getY();
    y2 = dLoc.getY();
    z1 = sLoc.getZ();
    z2 = dLoc.getZ();
    xDis = std::abs(x1 - x2);
    yDis = std::abs(y1 - y2);
    zDis = std::abs(z1 - z2);
    distance = std::sqrt(xDis*xDis + yDis*yDis + zDis*zDis);
    this->setDelay(distance / 300000000);
    return distance;
}
cChannel::Result SatToSat::processMessage(cMessage *msg, const SendOptions& options, simtime_t t)
{
    getDistance();
    auto result = ThruputMeteringChannel::processMessage(msg, options, t);
    return result;
}


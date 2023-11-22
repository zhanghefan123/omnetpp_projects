//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#include "inet/queueing/filter/OrdinalBasedDropper.h"

#include "inet/common/ModuleAccess.h"

namespace inet {
namespace queueing {

Define_Module(OrdinalBasedDropper);

void OrdinalBasedDropper::initialize(int stage)
{
    PacketFilterBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        numPackets = 0;
        numDropped = 0;
        generateFurtherDrops = false;

        WATCH(numPackets);
        WATCH(numDropped);
        WATCH(generateFurtherDrops);

        const char *vector = par("dropsVector");
        parseVector(vector);

        if (dropsVector.size() == 0)
            EV_WARN << "Empty dropsVector" << EV_ENDL;
        else {
            EV_DEBUG << EV_FIELD(dropsVector, vector) << EV_ENDL;
            generateFurtherDrops = true;
        }
    }
}

bool OrdinalBasedDropper::matchesPacket(const Packet *packet) const
{
    return !generateFurtherDrops || numPackets != dropsVector[0];
}

void OrdinalBasedDropper::processPacket(Packet *packet)
{
    numPackets++;
}

void OrdinalBasedDropper::dropPacket(Packet *packet)
{
    EV_DEBUG << "Dropping packet" << EV_FIELD(ordinalNumber, numPackets) << EV_FIELD(packet) << EV_ENDL;
    numPackets++;
    numDropped++;
    dropsVector.erase(dropsVector.begin());
    if (dropsVector.size() == 0) {
        EV_DEBUG << "End of dropsVector reached" << EV_ENDL;
        generateFurtherDrops = false;
    }
}

void OrdinalBasedDropper::parseVector(const char *vector)
{
    const char *v = vector;
    while (*v) {
        // parse packet numbers
        while (isspace(*v))
            v++;
        if (!*v || *v == ';')
            break;
        if (!isdigit(*v))
            throw cRuntimeError("Syntax error in dropsVector: packet number expected");
        if (dropsVector.size() > 0 && dropsVector.back() >= (unsigned int)atoi(v))
            throw cRuntimeError("Syntax error in dropsVector: packet numbers in ascending order expected");

        dropsVector.push_back(atoi(v));
        while (isdigit(*v))
            v++;

        // skip delimiter
        while (isspace(*v))
            v++;
        if (!*v)
            break;
        if (*v != ';')
            throw cRuntimeError("Syntax error in dropsVector: separator ';' missing");
        v++;
        while (isspace(*v))
            v++;
    }
}

} // namespace queueing
} // namespace inet


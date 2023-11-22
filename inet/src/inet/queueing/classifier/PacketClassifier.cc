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

#include "inet/queueing/classifier/PacketClassifier.h"

namespace inet {
namespace queueing {

Define_Module(PacketClassifier);

void PacketClassifier::initialize(int stage)
{
    PacketClassifierBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
        packetClassifierFunction = createClassifierFunction(par("classifierClass"));
}

IPacketClassifierFunction *PacketClassifier::createClassifierFunction(const char *classifierClass) const
{
    return check_and_cast<IPacketClassifierFunction *>(createOne(classifierClass));
}

int PacketClassifier::classifyPacket(Packet *packet)
{
    int index = packetClassifierFunction->classifyPacket(packet);
    return index == -1 ? index : getOutputGateIndex(index);
}

} // namespace queueing
} // namespace inet


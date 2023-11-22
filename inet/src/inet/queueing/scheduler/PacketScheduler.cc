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

#include "inet/queueing/scheduler/PacketScheduler.h"

namespace inet {
namespace queueing {

Define_Module(PacketScheduler);

void PacketScheduler::initialize(int stage)
{
    PacketSchedulerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
        packetSchedulerFunction = createSchedulerFunction(par("schedulerClass"));
}

IPacketSchedulerFunction *PacketScheduler::createSchedulerFunction(const char *schedulerClass) const
{
    return check_and_cast<IPacketSchedulerFunction *>(createOne(schedulerClass));
}

int PacketScheduler::schedulePacket()
{
    int index = packetSchedulerFunction->schedulePacket(providers);
    return index == -1 ? index : getInputGateIndex(index);
}

} // namespace queueing
} // namespace inet


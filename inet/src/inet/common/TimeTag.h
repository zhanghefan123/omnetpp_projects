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

#ifndef __INET_TIMETAG_H
#define __INET_TIMETAG_H

#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"

namespace inet {

template<typename T>
void increaseTimeTag(const Ptr<Chunk>& chunk, simtime_t duration)
{
    chunk->mapAllTagsForUpdate<T>(b(0), chunk->getChunkLength(), [&] (b offset, b length, T *timeTag) {
        for (int i = 0; i < (int)timeTag->getTotalTimesArraySize(); i++)
            timeTag->setTotalTimes(i, timeTag->getTotalTimes(i) + duration);
    });
}

template<typename T>
void increaseTimeTag(Packet *packet, simtime_t duration)
{
    packet->mapAllRegionTagsForUpdate<T>(b(0), packet->getTotalLength(), [&] (b offset, b length, const Ptr<T>& timeTag) {
        for (int i = 0; i < (int)timeTag->getTotalTimesArraySize(); i++)
            timeTag->setTotalTimes(i, timeTag->getTotalTimes(i) + duration);
    });
}

} // namespace inet

#endif


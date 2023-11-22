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

#ifndef __INET_IPACKETMARKER_H
#define __INET_IPACKETMARKER_H

#include "inet/queueing/contract/IPacketFlow.h"

namespace inet {
namespace queueing {

/**
 * This class defines the interface for packet markers.
 */
class INET_API IPacketMarker : public virtual IPacketFlow
{
  public:
    /**
     * Marks the packet by attaching information to it.
     */
    virtual void markPacket(Packet *packet) = 0;
};

} // namespace queueing
} // namespace inet

#endif


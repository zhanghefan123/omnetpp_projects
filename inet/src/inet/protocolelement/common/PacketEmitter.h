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

#ifndef __INET_PACKETEMITTER_H
#define __INET_PACKETEMITTER_H

#include "inet/common/DirectionTag_m.h"
#include "inet/common/Protocol.h"
#include "inet/common/packet/PacketFilter.h"
#include "inet/queueing/base/PacketFlowBase.h"

namespace inet {

using namespace inet::queueing;

class INET_API PacketEmitter : public PacketFlowBase
{
  protected:
    simsignal_t signal;
    PacketFilter packetFilter;
    Direction direction = DIRECTION_UNDEFINED;

    Packet *processedPacket = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void processPacket(Packet *packet) override;
    virtual void emitPacket(Packet *packet);

  public:
    virtual ~PacketEmitter() { delete processedPacket; }

    virtual void pushPacket(Packet *packet, cGate *gate) override;
    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override;
};

} // namespace inet

#endif


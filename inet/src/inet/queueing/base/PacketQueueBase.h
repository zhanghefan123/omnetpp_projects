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

#ifndef __INET_PACKETQUEUEBASE_H
#define __INET_PACKETQUEUEBASE_H

#include "inet/queueing/base/PacketProcessorBase.h"
#include "inet/queueing/contract/IPacketQueue.h"

namespace inet {
namespace queueing {

class INET_API PacketQueueBase : public PacketProcessorBase, public virtual IPacketQueue
{
  protected:
    const char *displayStringTextFormat = nullptr;
    int numPushedPackets = -1;
    int numPulledPackets = -1;
    int numRemovedPackets = -1;
    int numDroppedPackets = -1;
    int numCreatedPackets = -1;

    cGate *inputGate = nullptr;
    cGate *outputGate = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void emit(simsignal_t signal, cObject *object, cObject *details = nullptr) override;

    virtual void updateDisplayString();

  public:
    virtual bool canPullSomePacket(cGate *gate) const override { return getNumPackets() > 0; }
    virtual bool canPushSomePacket(cGate *gate) const override { return true; }

    virtual void enqueuePacket(Packet *packet) override;
    virtual Packet *dequeuePacket() override;

    virtual void pushPacketStart(Packet *packet, cGate *gate, bps datarate) override { throw cRuntimeError("Invalid operation"); }
    virtual void pushPacketEnd(Packet *packet, cGate *gate) override { throw cRuntimeError("Invalid operation"); }
    virtual void pushPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength = b(0)) override { throw cRuntimeError("Invalid operation"); }

    virtual Packet *pullPacketStart(cGate *gate, bps datarate) override { throw cRuntimeError("Invalid operation"); }
    virtual Packet *pullPacketEnd(cGate *gate) override { throw cRuntimeError("Invalid operation"); }
    virtual Packet *pullPacketProgress(cGate *gate, bps datarate, b position, b extraProcessableLength) override { throw cRuntimeError("Invalid operation"); }
};

} // namespace queueing
} // namespace inet

#endif


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

#ifndef __INET_PREEMPTABLESTREAMER_H
#define __INET_PREEMPTABLESTREAMER_H

#include "inet/common/clock/ClockUserModuleMixin.h"
#include "inet/queueing/base/PacketProcessorBase.h"
#include "inet/queueing/contract/IPacketFlow.h"

namespace inet {

using namespace inet::queueing;

class INET_API PreemptableStreamer : public ClockUserModuleMixin<PacketProcessorBase>, public virtual IPacketFlow
{
  protected:
    bps datarate = bps(NaN);
    b minPacketLength = b(-1);
    b roundingLength = b(-1);

    cGate *inputGate = nullptr;
    IActivePacketSource *producer = nullptr;
    IPassivePacketSource *provider = nullptr;

    cGate *outputGate = nullptr;
    IPassivePacketSink *consumer = nullptr;
    IActivePacketSink *collector = nullptr;

    simtime_t streamStart;
    bps streamDatarate = bps(NaN);
    Packet *streamedPacket = nullptr;
    Packet *remainingPacket = nullptr;

    ClockEvent *endStreamingTimer = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual bool isStreaming() const { return streamedPacket != nullptr; }
    virtual void endStreaming();

  public:
    virtual ~PreemptableStreamer();

    virtual IPassivePacketSink *getConsumer(cGate *gate) override { return this; }
    virtual IPassivePacketSource *getProvider(cGate *gate) override { return this; }

    virtual bool supportsPacketPushing(cGate *gate) const override { return true; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return true; }
    virtual bool supportsPacketPassing(cGate *gate) const override { return gate == inputGate; }
    virtual bool supportsPacketStreaming(cGate *gate) const override { return gate == outputGate; }

    virtual bool canPushSomePacket(cGate *gate) const override;
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override;
    virtual void pushPacket(Packet *packet, cGate *gate) override;

    virtual void pushPacketStart(Packet *packet, cGate *gate, bps datarate) override { throw cRuntimeError("Invalid operation"); }
    virtual void pushPacketEnd(Packet *packet, cGate *gate) override { throw cRuntimeError("Invalid operation"); }
    virtual void pushPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength = b(0)) override { throw cRuntimeError("Invalid operation"); }

    virtual void handleCanPushPacketChanged(cGate *gate) override;
    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override;

    virtual bool canPullSomePacket(cGate *gate) const override;
    virtual Packet *canPullPacket(cGate *gate) const override;
    virtual Packet *pullPacket(cGate *gate) override { throw cRuntimeError("Invalid operation"); }

    virtual Packet *pullPacketStart(cGate *gate, bps datarate) override;
    virtual Packet *pullPacketEnd(cGate *gate) override;
    virtual Packet *pullPacketProgress(cGate *gate, bps datarate, b position, b extraProcessableLength) override;

    virtual void handleCanPullPacketChanged(cGate *gate) override;
    virtual void handlePullPacketProcessed(Packet *packet, cGate *gate, bool successful) override;
};

} // namespace inet

#endif


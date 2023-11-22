//
// Copyright (C) 2012 OpenSim Ltd.
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

#ifndef __INET_DSCPMARKER_H
#define __INET_DSCPMARKER_H

#include "inet/common/packet/Packet.h"
#include "inet/queueing/base/PacketProcessorBase.h"
#include "inet/queueing/contract/IActivePacketSource.h"
#include "inet/queueing/contract/IPassivePacketSink.h"

namespace inet {

/**
 * DSCP Marker.
 */
class INET_API DscpMarker : public queueing::PacketProcessorBase, public queueing::IPassivePacketSink, public queueing::IActivePacketSource
{
  protected:
    cGate *outputGate = nullptr;
    IPassivePacketSink *consumer = nullptr;

    std::vector<int> dscps;

    int numRcvd = 0;
    int numMarked = 0;

    static simsignal_t packetMarkedSignal;

  public:
    DscpMarker() {}

    virtual bool supportsPacketPushing(cGate *gate) const override { return true; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return false; }

    virtual queueing::IPassivePacketSink *getConsumer(cGate *gate) override { return this; }

    virtual bool canPushSomePacket(cGate *gate) const override { return true; }
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override { return true; }

    virtual void pushPacketStart(Packet *packet, cGate *gate, bps datarate) override { throw cRuntimeError("Invalid operation"); }
    virtual void pushPacketEnd(Packet *packet, cGate *gate) override { throw cRuntimeError("Invalid operation"); }
    virtual void pushPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength = b(0)) override { throw cRuntimeError("Invalid operation"); }

    virtual void handleCanPushPacketChanged(cGate *gate) override {}

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;
    virtual void refreshDisplay() const override;

    virtual bool markPacket(Packet *msg, int dscp);

  public:
    virtual void pushPacket(Packet *packet, cGate *gate) override;

    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override {}
};

} // namespace inet

#endif


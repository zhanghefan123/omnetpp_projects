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

#ifndef __INET_PACKETMULTIPLEXER_H
#define __INET_PACKETMULTIPLEXER_H

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/queueing/base/PacketProcessorBase.h"
#include "inet/queueing/contract/IActivePacketSource.h"
#include "inet/queueing/contract/IPassivePacketSink.h"

namespace inet {
namespace queueing {

class INET_API PacketMultiplexer : public PacketProcessorBase, public virtual IPassivePacketSink, public virtual IActivePacketSource, public DefaultProtocolRegistrationListener
{
  protected:
    std::vector<cGate *> inputGates;
    std::vector<IActivePacketSource *> producers;

    cGate *outputGate = nullptr;
    IPassivePacketSink *consumer = nullptr;

    int inProgressStreamId = -1;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual bool isStreamingPacket() const { return inProgressStreamId != -1; }
    virtual void startPacketStreaming(Packet *packet);
    virtual void endPacketStreaming(Packet *packet);
    virtual void checkPacketStreaming(Packet *packet);

  public:
    virtual IPassivePacketSink *getConsumer(cGate *gate) override { return consumer; }

    virtual bool supportsPacketPulling(cGate *gate) const override { return false; }
    virtual bool supportsPacketPushing(cGate *gate) const override { return true; }
    virtual bool supportsPacketStreaming(cGate *gate) const override { return true; }

    virtual bool canPushSomePacket(cGate *gate) const override { return consumer->canPushSomePacket(outputGate); }
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override { return consumer->canPushPacket(packet, gate); }

    virtual void pushPacket(Packet *packet, cGate *gate) override;

    virtual void pushPacketStart(Packet *packet, cGate *gate, bps datarate) override;
    virtual void pushPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength = b(0)) override;
    virtual void pushPacketEnd(Packet *packet, cGate *gate) override;

    virtual void handleCanPushPacketChanged(cGate *gate) override;
    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override;

    virtual void handleRegisterService(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;
    virtual void handleRegisterProtocol(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;
};

} // namespace queueing
} // namespace inet

#endif


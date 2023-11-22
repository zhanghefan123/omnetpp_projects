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

#ifndef __INET_PACKETPROCESSORBASE_H
#define __INET_PACKETPROCESSORBASE_H

#include "inet/common/Simsignals.h"
#include "inet/common/StringFormat.h"
#include "inet/common/packet/Packet.h"
#include "inet/queueing/contract/IPacketProcessor.h"
#include "inet/queueing/contract/IPassivePacketSink.h"

namespace inet {
namespace queueing {

class INET_API PacketProcessorBase : public cSimpleModule, public virtual IPacketProcessor, public StringFormat::IDirectiveResolver
{
  protected:
    const char *displayStringTextFormat = nullptr;
    int numProcessedPackets = -1;
    b processedTotalLength = b(-1);

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handlePacketProcessed(Packet *packet);

    virtual void checkPacketOperationSupport(cGate *gate) const;

    virtual void pushOrSendPacket(Packet *packet, cGate *gate, IPassivePacketSink *consumer);
    virtual void pushOrSendPacketStart(Packet *packet, cGate *gate, IPassivePacketSink *consumer, bps datarate, int transmissionId);
    virtual void pushOrSendPacketEnd(Packet *packet, cGate *gate, IPassivePacketSink *consumer, int transmissionId);
    virtual void pushOrSendPacketProgress(Packet *packet, cGate *gate, IPassivePacketSink *consumer, bps datarate, b position, b extraProcessableLength, int transmissionId);

    virtual void dropPacket(Packet *packet, PacketDropReason reason, int limit = -1);

    virtual void updateDisplayString() const;

    virtual void animateSend(Packet *packet, cGate *gate, const SendOptions& sendOptions) const;
    virtual void animateSendPacket(Packet *packet, cGate *gate) const;
    virtual void animateSendPacketStart(Packet *packet, cGate *gate, bps datarate, long transmissionId) const;
    virtual void animateSendPacketStart(Packet *packet, cGate *gate, bps datarate, const SendOptions& sendOptions) const;
    virtual void animateSendPacketEnd(Packet *packet, cGate *gate, long transmissionId) const;
    virtual void animateSendPacketEnd(Packet *packet, cGate *gate, const SendOptions& sendOptions) const;
    virtual void animateSendPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength, long transmissionId) const;
    virtual void animateSendPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength, const SendOptions& sendOptions) const;

  public:
    virtual bool supportsPacketSending(cGate *gate) const override { return true; }
    virtual bool supportsPacketPassing(cGate *gate) const override { return true; }
    virtual bool supportsPacketStreaming(cGate *gate) const override { return false; }

    virtual const char *resolveDirective(char directive) const override;
};

} // namespace queueing
} // namespace inet

#endif


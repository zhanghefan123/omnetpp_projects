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

#ifndef __INET_ETHERNETCUTTHROUGHSINK_H
#define __INET_ETHERNETCUTTHROUGHSINK_H

#include "inet/protocolelement/common/PacketStreamer.h"

namespace inet {

using namespace inet::queueing;

class INET_API EthernetCutthroughSink : public PacketStreamer
{
  protected:
    cGate *cutthroughInputGate = nullptr;
    IActivePacketSource *cutthroughProducer = nullptr;

    bool cutthrough = false;

  protected:
    virtual void initialize(int stage) override;

  public:
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override;

    virtual void pushPacketStart(Packet *packet, cGate *gate, bps datarate) override;
    virtual void pushPacketEnd(Packet *packet, cGate *gate) override;

    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override;
};

} // namespace inet

#endif


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

#ifndef __INET_RESENDING_H
#define __INET_RESENDING_H

#include "inet/queueing/base/PacketPusherBase.h"

namespace inet {

using namespace inet::queueing;

class INET_API Resending : public PacketPusherBase
{
  protected:
    int numRetries = 0;
    queueing::IActivePacketSource *producer = nullptr;

    Packet *packet = nullptr;
    int retry = 0;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

  public:
    virtual ~Resending() { delete packet; }
    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override;

    virtual bool canPushSomePacket(cGate *gate) const override { return packet == nullptr; }
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override { return packet == nullptr; }
    virtual void pushPacket(Packet *packet, cGate *gate) override;
};

} // namespace inet

#endif


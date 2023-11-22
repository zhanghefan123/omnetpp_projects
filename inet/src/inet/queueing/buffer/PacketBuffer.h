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

#ifndef __INET_PACKETBUFFER_H
#define __INET_PACKETBUFFER_H

#include "inet/queueing/base/PacketBufferBase.h"
#include "inet/queueing/contract/IPacketBuffer.h"
#include "inet/queueing/contract/IPacketCollection.h"
#include "inet/queueing/contract/IPacketDropperFunction.h"

namespace inet {
namespace queueing {

class INET_API PacketBuffer : public PacketBufferBase, public virtual IPacketBuffer
{
  protected:
    int packetCapacity = -1;
    b dataCapacity = b(-1);

    std::vector<Packet *> packets;

    IPacketDropperFunction *packetDropperFunction = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual IPacketDropperFunction *createDropperFunction(const char *dropperClass) const;
    virtual bool isOverloaded() const;

  public:
    virtual int getMaxNumPackets() const override { return packetCapacity; }
    virtual int getNumPackets() const override { return packets.size(); }

    virtual b getMaxTotalLength() const override { return dataCapacity; }
    virtual b getTotalLength() const override;

    virtual Packet *getPacket(int index) const override;
    virtual bool isEmpty() const override { return packets.size() == 0; }

    virtual void addPacket(Packet *packet) override;
    virtual void removePacket(Packet *packet) override;

    virtual bool supportsPacketPushing(cGate *gate) const override { return false; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return false; }
};

} // namespace queueing
} // namespace inet

#endif


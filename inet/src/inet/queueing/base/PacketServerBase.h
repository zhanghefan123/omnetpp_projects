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

#ifndef __INET_PACKETSERVERBASE_H
#define __INET_PACKETSERVERBASE_H

#include "inet/queueing/base/PacketProcessorBase.h"
#include "inet/queueing/contract/IActivePacketSink.h"
#include "inet/queueing/contract/IActivePacketSource.h"

namespace inet {
namespace queueing {

class INET_API PacketServerBase : public PacketProcessorBase, public virtual IActivePacketSink, public virtual IActivePacketSource
{
  public:
    static simsignal_t packetServedSignal;

  protected:
    cGate *inputGate = nullptr;
    IPassivePacketSource *provider = nullptr;

    cGate *outputGate = nullptr;
    IPassivePacketSink *consumer = nullptr;

  protected:
    virtual void initialize(int stage) override;

  public:
    virtual IPassivePacketSource *getProvider(cGate *gate) override { return provider; }
    virtual IPassivePacketSink *getConsumer(cGate *gate) override { return consumer; }

    virtual bool supportsPacketPushing(cGate *gate) const override { return outputGate == gate; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return inputGate == gate; }

    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override;
    virtual void handlePullPacketProcessed(Packet *packet, cGate *gate, bool successful) override;
};

} // namespace queueing
} // namespace inet

#endif


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

#ifndef __INET_PASSIVEPACKETSINK_H
#define __INET_PASSIVEPACKETSINK_H

#include "inet/common/clock/ClockUserModuleMixin.h"
#include "inet/queueing/base/PassivePacketSinkBase.h"
#include "inet/queueing/contract/IActivePacketSource.h"

namespace inet {
namespace queueing {

class INET_API PassivePacketSink : public ClockUserModuleMixin<PassivePacketSinkBase>
{
  protected:
    cPar *consumptionIntervalParameter = nullptr;
    ClockEvent *consumptionTimer = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void scheduleConsumptionTimer();
    virtual void consumePacket(Packet *packet);

  public:
    virtual ~PassivePacketSink() { cancelAndDeleteClockEvent(consumptionTimer); }

    virtual bool supportsPacketPushing(cGate *gate) const override { return gate == inputGate; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return false; }

    virtual bool canPushSomePacket(cGate *gate) const override { return !consumptionTimer->isScheduled(); }
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override { return canPushSomePacket(gate); }
    virtual void pushPacket(Packet *packet, cGate *gate) override;
};

} // namespace queueing
} // namespace inet

#endif


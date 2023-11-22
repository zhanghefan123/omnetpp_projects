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

#ifndef __INET_PASSIVEPACKETSOURCE_H
#define __INET_PASSIVEPACKETSOURCE_H

#include "inet/common/clock/ClockUserModuleMixin.h"
#include "inet/queueing/base/PassivePacketSourceBase.h"

namespace inet {
namespace queueing {

class INET_API PassivePacketSource : public ClockUserModuleMixin<PassivePacketSourceBase>
{
  protected:
    cPar *providingIntervalParameter = nullptr;
    ClockEvent *providingTimer = nullptr;

    mutable Packet *nextPacket = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void scheduleProvidingTimer();
    virtual Packet *providePacket(cGate *gate);

  public:
    virtual ~PassivePacketSource() { delete nextPacket; cancelAndDeleteClockEvent(providingTimer); }

    virtual bool supportsPacketPushing(cGate *gate) const override { return false; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return outputGate == gate; }

    virtual bool canPullSomePacket(cGate *gate) const override { return !providingTimer->isScheduled(); }
    virtual Packet *canPullPacket(cGate *gate) const override;

    virtual Packet *pullPacket(cGate *gate) override;
    virtual Packet *pullPacketStart(cGate *gate, bps datarate) override { throw cRuntimeError("Invalid operation"); }
    virtual Packet *pullPacketEnd(cGate *gate) override { throw cRuntimeError("Invalid operation"); }
    virtual Packet *pullPacketProgress(cGate *gate, bps datarate, b position, b extraProcessableLength) override { throw cRuntimeError("Invalid operation"); }
};

} // namespace queueing
} // namespace inet

#endif


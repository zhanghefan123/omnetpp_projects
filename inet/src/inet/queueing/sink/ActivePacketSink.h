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

#ifndef __INET_ACTIVEPACKETSINK_H
#define __INET_ACTIVEPACKETSINK_H

#include "inet/common/clock/ClockUserModuleMixin.h"
#include "inet/queueing/base/ActivePacketSinkBase.h"

namespace inet {
namespace queueing {

class INET_API ActivePacketSink : public ClockUserModuleMixin<ActivePacketSinkBase>
{
  protected:
    cPar *collectionIntervalParameter = nullptr;
    ClockEvent *collectionTimer = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void scheduleCollectionTimer();
    virtual void collectPacket();

  public:
    virtual ~ActivePacketSink() { cancelAndDeleteClockEvent(collectionTimer); }

    virtual void handleCanPullPacketChanged(cGate *gate) override;
    virtual void handlePullPacketProcessed(Packet *packet, cGate *gate, bool successful) override;
};

} // namespace queueing
} // namespace inet

#endif


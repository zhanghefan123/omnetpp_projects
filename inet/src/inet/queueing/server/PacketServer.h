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

#ifndef __INET_PACKETSERVER_H
#define __INET_PACKETSERVER_H

#include "inet/common/clock/ClockUserModuleMixin.h"
#include "inet/queueing/base/PacketServerBase.h"

namespace inet {
namespace queueing {

class INET_API PacketServer : public ClockUserModuleMixin<PacketServerBase>
{
  protected:
    ClockEvent *processingTimer = nullptr;
    Packet *packet = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;
    virtual void scheduleProcessingTimer();
    virtual bool canStartProcessingPacket();
    virtual void startProcessingPacket();
    virtual void endProcessingPacket();

  public:
    virtual ~PacketServer() { cancelAndDeleteClockEvent(processingTimer); delete packet; }

    virtual void handleCanPushPacketChanged(cGate *gate) override;
    virtual void handleCanPullPacketChanged(cGate *gate) override;

    virtual const char *resolveDirective(char directive) const override;
};

} // namespace queueing
} // namespace inet

#endif


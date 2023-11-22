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

#include "inet/queueing/common/PacketDelayer.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/PacketEventTag.h"
#include "inet/common/TimeTag.h"

namespace inet {
namespace queueing {

Define_Module(PacketDelayer);

void PacketDelayer::handleMessage(cMessage *message)
{
    if (message->isSelfMessage()) {
        auto packet = message->isPacket() ? check_and_cast<Packet *>(message) : static_cast<Packet *>(message->getContextPointer());
        if (!message->isPacket())
            delete message;
        simtime_t delay = simTime() - message->getSendingTime();
        insertPacketEvent(this, packet, PEK_DELAYED, delay / packet->getBitLength());
        increaseTimeTag<DelayingTimeTag>(packet, delay / packet->getBitLength());
        pushOrSendPacket(packet, outputGate, consumer);
    }
    else
        PacketPusherBase::handleMessage(message);
}

cGate *PacketDelayer::getRegistrationForwardingGate(cGate *gate)
{
    if (gate == outputGate)
        return inputGate;
    else if (gate == inputGate)
        return outputGate;
    else
        throw cRuntimeError("Unknown gate");
}

void PacketDelayer::pushPacket(Packet *packet, cGate *gate)
{
    Enter_Method("pushPacket");
    take(packet);
#ifdef INET_WITH_CLOCK
    if (clock != nullptr) {
        clocktime_t delay = par("delay");
        EV_INFO << "Delaying packet" << EV_FIELD(delay) << EV_FIELD(packet) << EV_ENDL;
        auto clockEvent = new ClockEvent("DelayTimer");
        clockEvent->setContextPointer(packet);
        scheduleClockEventAfter(delay, clockEvent);
    }
    else {
#else
    {
#endif
        simtime_t delay = par("delay");
        EV_INFO << "Delaying packet" << EV_FIELD(delay) << EV_FIELD(packet) << EV_ENDL;
        scheduleAfter(delay, packet);
    }
    handlePacketProcessed(packet);
    updateDisplayString();
}

void PacketDelayer::handleCanPushPacketChanged(cGate *gate)
{
    Enter_Method("handleCanPushPacketChanged");
    if (producer != nullptr)
        producer->handleCanPushPacketChanged(inputGate->getPathStartGate());
}

void PacketDelayer::handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful)
{
    Enter_Method("handlePushPacketProcessed");
    if (producer != nullptr)
        producer->handlePushPacketProcessed(packet, gate, successful);
}

} // namespace queueing
} // namespace inet


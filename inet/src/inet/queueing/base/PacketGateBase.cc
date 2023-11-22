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

#include "inet/queueing/base/PacketGateBase.h"

namespace inet {
namespace queueing {

simsignal_t PacketGateBase::gateStateChangedSignal = registerSignal("gateStateChanged");

void PacketGateBase::initialize(int stage)
{
    PacketFlowBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
        WATCH(isOpen_);
    else if (stage == INITSTAGE_QUEUEING)
        emit(gateStateChangedSignal, isOpen_);
}

void PacketGateBase::open()
{
    ASSERT(!isOpen_);
    EV_DEBUG << "Opening gate" << EV_ENDL;
    isOpen_ = true;
    if (producer != nullptr)
        producer->handleCanPushPacketChanged(inputGate->getPathStartGate());
    if (collector != nullptr)
        collector->handleCanPullPacketChanged(outputGate->getPathEndGate());
    emit(gateStateChangedSignal, isOpen_);
}

void PacketGateBase::close()
{
    ASSERT(isOpen_);
    EV_DEBUG << "Closing gate" << EV_ENDL;
    isOpen_ = false;
    if (producer != nullptr)
        producer->handleCanPushPacketChanged(inputGate->getPathStartGate());
    if (collector != nullptr)
        collector->handleCanPullPacketChanged(outputGate->getPathEndGate());
    emit(gateStateChangedSignal, isOpen_);
}

void PacketGateBase::processPacket(Packet *packet)
{
    EV_INFO << "Passing through packet" << EV_FIELD(packet) << EV_ENDL;
}

bool PacketGateBase::canPushSomePacket(cGate *gate) const
{
    return isOpen_ && consumer->canPushSomePacket(outputGate->getPathStartGate());
}

bool PacketGateBase::canPushPacket(Packet *packet, cGate *gate) const
{
    return isOpen_ && consumer->canPushPacket(packet, outputGate->getPathStartGate());
}

bool PacketGateBase::canPullSomePacket(cGate *gate) const
{
    return isOpen_ && provider->canPullSomePacket(inputGate->getPathStartGate());
}

Packet *PacketGateBase::canPullPacket(cGate *gate) const
{
    return isOpen_ ? provider->canPullPacket(inputGate->getPathStartGate()) : nullptr;
}

void PacketGateBase::handleCanPushPacketChanged(cGate *gate)
{
    Enter_Method("handleCanPushPacketChanged");
    if (isOpen_)
        PacketFlowBase::handleCanPushPacketChanged(gate);
}

void PacketGateBase::handleCanPullPacketChanged(cGate *gate)
{
    Enter_Method("handleCanPullPacketChanged");
    if (isOpen_)
        PacketFlowBase::handleCanPullPacketChanged(gate);
}

} // namespace queueing
} // namespace inet


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

#include "inet/queueing/common/PacketMultiplexer.h"

#include "inet/common/ModuleAccess.h"

namespace inet {
namespace queueing {

Define_Module(PacketMultiplexer);

void PacketMultiplexer::initialize(int stage)
{
    PacketProcessorBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        for (int i = 0; i < gateSize("in"); i++) {
            auto inputGate = gate("in", i);
            auto input = findConnectedModule<IActivePacketSource>(inputGate);
            inputGates.push_back(inputGate);
            producers.push_back(input);
        }
        outputGate = gate("out");
        consumer = findConnectedModule<IPassivePacketSink>(outputGate);
    }
    else if (stage == INITSTAGE_QUEUEING) {
        for (auto& inputGate : inputGates)
            checkPacketOperationSupport(inputGate);
        checkPacketOperationSupport(outputGate);
    }
}

void PacketMultiplexer::handleMessage(cMessage *message)
{
    auto packet = check_and_cast<Packet *>(message);
    pushPacket(packet, packet->getArrivalGate());
}

void PacketMultiplexer::checkPacketStreaming(Packet *packet)
{
    if (inProgressStreamId != -1 && (packet == nullptr || packet->getTreeId() != inProgressStreamId))
        throw cRuntimeError("Another packet streaming operation is already in progress");
}

void PacketMultiplexer::startPacketStreaming(Packet *packet)
{
    inProgressStreamId = packet->getTreeId();
}

void PacketMultiplexer::endPacketStreaming(Packet *packet)
{
    emit(packetPushedSignal, packet);
    handlePacketProcessed(packet);
    inProgressStreamId = -1;
}

void PacketMultiplexer::pushPacket(Packet *packet, cGate *gate)
{
    Enter_Method("pushPacket");
    take(packet);
    EV_INFO << "Forwarding packet" << EV_FIELD(packet) << EV_ENDL;
    handlePacketProcessed(packet);
    pushOrSendPacket(packet, outputGate, consumer);
    updateDisplayString();
}

void PacketMultiplexer::pushPacketStart(Packet *packet, cGate *gate, bps datarate)
{
    Enter_Method("pushPacketStart");
    take(packet);
    EV_INFO << "Forwarding packet" << EV_FIELD(packet) << EV_ENDL;
    checkPacketStreaming(packet);
    startPacketStreaming(packet);
    pushOrSendPacketStart(packet, outputGate, consumer, datarate, packet->getTransmissionId());
    updateDisplayString();
}

void PacketMultiplexer::pushPacketEnd(Packet *packet, cGate *gate)
{
    Enter_Method("pushPacketEnd");
    take(packet);
    EV_INFO << "Forwarding packet" << EV_FIELD(packet) << EV_ENDL;
    if (!isStreamingPacket())
        startPacketStreaming(packet);
    else
        checkPacketStreaming(packet);
    endPacketStreaming(packet);
    pushOrSendPacketEnd(packet, outputGate, consumer, packet->getTransmissionId());
    updateDisplayString();
}

void PacketMultiplexer::pushPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength)
{
    Enter_Method("pushPacketProgress");
    take(packet);
    EV_INFO << "Forwarding packet" << EV_FIELD(packet) << EV_ENDL;
    if (!isStreamingPacket())
        startPacketStreaming(packet);
    else
        checkPacketStreaming(packet);
    if (packet->getTotalLength() == position + extraProcessableLength)
        endPacketStreaming(packet);
    pushOrSendPacketProgress(packet, outputGate, consumer, datarate, position, extraProcessableLength, packet->getTransmissionId());
    updateDisplayString();
}

void PacketMultiplexer::handleCanPushPacketChanged(cGate *gate)
{
    Enter_Method("handleCanPushPacketChanged");
    for (int i = 0; i < (int)inputGates.size(); i++)
        // NOTE: notifying a listener may prevent others from pushing
        if (producers[i] != nullptr && consumer->canPushSomePacket(outputGate))
            producers[i]->handleCanPushPacketChanged(inputGates[i]->getPathStartGate());
}

void PacketMultiplexer::handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful)
{
    Enter_Method("handlePushPacketProcessed");
}

void PacketMultiplexer::handleRegisterService(const Protocol& protocol, cGate *g, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterService");
    if (g == outputGate) {
        int size = gateSize("in");
        for (int i = 0; i < size; i++)
            registerService(protocol, gate("in", i), servicePrimitive);
    }
}

void PacketMultiplexer::handleRegisterProtocol(const Protocol& protocol, cGate *g, ServicePrimitive servicePrimitive)
{
    Enter_Method("handleRegisterProtocol");
    // NOTE: this may be called before initstage local
    auto outputGate = gate("out");
    if (g != outputGate)
        registerProtocol(protocol, outputGate, servicePrimitive);
    else if (g == outputGate && servicePrimitive == SP_INDICATION)
        for (auto& inputGate : inputGates)
            registerProtocol(protocol, inputGate, servicePrimitive);
}

} // namespace queueing
} // namespace inet


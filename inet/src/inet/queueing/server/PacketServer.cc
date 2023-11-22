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

#include "inet/queueing/server/PacketServer.h"

#include "inet/common/PacketEventTag.h"
#include "inet/common/Simsignals.h"
#include "inet/common/TimeTag.h"

namespace inet {
namespace queueing {

Define_Module(PacketServer);

void PacketServer::initialize(int stage)
{
    ClockUserModuleMixin::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
        processingTimer = new ClockEvent("ProcessingTimer");
}

void PacketServer::handleMessage(cMessage *message)
{
    if (message == processingTimer) {
        endProcessingPacket();
        if (canStartProcessingPacket()) {
            startProcessingPacket();
            scheduleProcessingTimer();
        }
        updateDisplayString();
    }
    else
        throw cRuntimeError("Unknown message");
}

void PacketServer::scheduleProcessingTimer()
{
    clocktime_t processingTime = par("processingTime");
    auto processingBitrate = bps(par("processingBitrate"));
    processingTime += s(packet->getTotalLength() / processingBitrate).get();
    scheduleClockEventAfter(processingTime, processingTimer);
}

bool PacketServer::canStartProcessingPacket()
{
    return provider->canPullSomePacket(inputGate->getPathStartGate()) &&
           consumer->canPushSomePacket(outputGate->getPathEndGate());
}

void PacketServer::startProcessingPacket()
{
    packet = provider->pullPacket(inputGate->getPathStartGate());
    take(packet);
    EV_INFO << "Processing packet started" << EV_FIELD(packet) << EV_ENDL;
}

void PacketServer::endProcessingPacket()
{
    EV_INFO << "Processing packet ended" << EV_FIELD(packet) << EV_ENDL;
    simtime_t processingTime = (simTime() - processingTimer->getSendingTime()) / packet->getBitLength();
    insertPacketEvent(this, packet, PEK_PROCESSED, processingTime);
    increaseTimeTag<ProcessingTimeTag>(packet, processingTime);
    processedTotalLength += packet->getDataLength();
    emit(packetServedSignal, packet);
    pushOrSendPacket(packet, outputGate, consumer);
    numProcessedPackets++;
    packet = nullptr;
}

void PacketServer::handleCanPushPacketChanged(cGate *gate)
{
    Enter_Method("handleCanPushPacketChanged");
    if (!processingTimer->isScheduled() && canStartProcessingPacket()) {
        startProcessingPacket();
        scheduleProcessingTimer();
    }
}

void PacketServer::handleCanPullPacketChanged(cGate *gate)
{
    Enter_Method("handleCanPullPacketChanged");
    if (!processingTimer->isScheduled() && canStartProcessingPacket()) {
        startProcessingPacket();
        scheduleProcessingTimer();
    }
}

const char *PacketServer::resolveDirective(char directive) const
{
    static std::string result;
    switch (directive) {
        case 's':
            result = processingTimer->isScheduled() ? "processing" : "";
            break;
        default:
            return PacketServerBase::resolveDirective(directive);
    }
    return result.c_str();
}

} // namespace queueing
} // namespace inet


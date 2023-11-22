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

#include "inet/linklayer/ieee8022/Ieee8022LlcInserter.h"

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/Ieee802SapTag_m.h"

namespace inet {

Define_Module(Ieee8022LlcInserter);

void Ieee8022LlcInserter::initialize(int stage)
{
    PacketFlowBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        registerService(Protocol::ieee8022llc, inputGate, nullptr);
        registerProtocol(Protocol::ieee8022llc, outputGate, outputGate);
    }
}

void Ieee8022LlcInserter::processPacket(Packet *packet)
{
    const auto& protocolTag = packet->findTag<PacketProtocolTag>();
    auto protocol = protocolTag ? protocolTag->getProtocol() : nullptr;
    const auto& llcHeader = makeShared<Ieee8022LlcHeader>();
    int sapData = ProtocolGroup::ieee8022protocol.findProtocolNumber(protocol);
    if (sapData != -1) {
        llcHeader->setSsap((sapData >> 8) & 0xFF);
        llcHeader->setDsap(sapData & 0xFF);
        llcHeader->setControl(3);
    }
    else {
        auto sapReq = packet->getTag<Ieee802SapReq>();
        llcHeader->setSsap(sapReq->getSsap());
        llcHeader->setDsap(sapReq->getDsap());
        llcHeader->setControl(3); // TODO get from sapTag
    }
    packet->insertAtFront(llcHeader);
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::ieee8022llc);
}

const Protocol *Ieee8022LlcInserter::getProtocol(const Ptr<const Ieee8022LlcHeader>& llcHeader)
{
    int32_t sapData = ((llcHeader->getSsap() & 0xFF) << 8) | (llcHeader->getDsap() & 0xFF);
    return ProtocolGroup::ieee8022protocol.findProtocol(sapData); // do not use getProtocol
}

} // namespace inet


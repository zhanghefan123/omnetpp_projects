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

#include "inet/linklayer/ethernet/modular/EthernetTypeOrLengthChecker.h"

#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/EtherType_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/ethernet/common/EthernetMacHeader_m.h"
#include "inet/networklayer/common/NetworkInterface.h"

namespace inet {

Define_Module(EthernetTypeOrLengthChecker);

void EthernetTypeOrLengthChecker::processPacket(Packet *packet)
{
    const auto& header = packet->popAtFront<EthernetTypeOrLengthField>();
    auto typeOrLength = header->getTypeOrLength();
    const Protocol *protocol;
    if (isIeee8023Length(typeOrLength))
        protocol = &Protocol::ieee8022llc;
    else
        protocol = ProtocolGroup::ethertype.getProtocol(typeOrLength);
    auto packetProtocolTag = packet->addTagIfAbsent<PacketProtocolTag>();
    packetProtocolTag->setFrontOffset(b(0));
    packetProtocolTag->setBackOffset(b(0));
    packetProtocolTag->setProtocol(protocol);
    packet->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(protocol);
}

bool EthernetTypeOrLengthChecker::matchesPacket(const Packet *packet) const
{
    const auto& header = packet->peekAtFront<EthernetTypeOrLengthField>();
    auto typeOrLength = header->getTypeOrLength();
    if (isIeee8023Length(typeOrLength))
        return true;
    auto protocol = ProtocolGroup::ethertype.findProtocol(typeOrLength);
    return protocol != nullptr;
}

void EthernetTypeOrLengthChecker::dropPacket(Packet *packet)
{
    PacketFilterBase::dropPacket(packet, NO_PROTOCOL_FOUND);
}

} // namespace inet


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

#include "inet/queueing/marker/EcnMarker.h"

#include "inet/common/ProtocolGroup.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/common/EtherType_m.h"
#include "inet/networklayer/common/L3Tools.h"

#ifdef INET_WITH_ETHERNET
#include "inet/linklayer/ethernet/common/Ethernet.h"
#include "inet/linklayer/ethernet/common/EthernetMacHeader_m.h"
#endif // #ifdef INET_WITH_ETHERNET

#ifdef INET_WITH_IPv4
#include "inet/networklayer/ipv4/Ipv4.h"
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#endif // ifdef INET_WITH_IPv4

namespace inet {
namespace queueing {

Define_Module(EcnMarker);

void EcnMarker::markPacket(Packet *packet)
{
    const auto& ecnReq = packet->findTag<EcnReq>();
    if (ecnReq != nullptr) {
        EV_DETAIL << "Marking packet with ECN" << EV_ENDL;
        setEcn(packet, static_cast<IpEcnCode>(ecnReq->getExplicitCongestionNotification()));
    }
}

void EcnMarker::setEcn(Packet *packet, IpEcnCode ecn)
{
    auto protocol = packet->getTag<PacketProtocolTag>()->getProtocol();
    if (protocol == &Protocol::ethernetMac) {
#if defined(INET_WITH_ETHERNET)
        packet->trim();
        auto ethHeader = packet->removeAtFront<EthernetMacHeader>();
        auto ethFcs = packet->removeAtBack<EthernetFcs>(ETHER_FCS_BYTES);
        if (isEth2Header(*ethHeader)) {
            const Protocol *payloadProtocol = ProtocolGroup::ethertype.getProtocol(ethHeader->getTypeOrLength());
#if defined(INET_WITH_IPv4)
            if (payloadProtocol == &Protocol::ipv4) {
                auto ipv4Header = removeNetworkProtocolHeader<Ipv4Header>(packet);
                ipv4Header->setEcn(ecn);
                Ipv4::insertCrc(ipv4Header); // recalculate IP header checksum
                insertNetworkProtocolHeader(packet, Protocol::ipv4, ipv4Header);
                packet->insertAtFront(ethHeader);
                ethFcs->setFcs(0);
                packet->insertAtBack(ethFcs);
                packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(protocol);
            }
#else
            throw cRuntimeError("IPv4 feature is disabled");
#endif
        }
        else {
            packet->insertAtFront(ethHeader);
            packet->insertAtBack(ethFcs);
        }
#else
        throw cRuntimeError("Ethernet feature is disabled");
#endif // #if defined(INET_WITH_ETHERNET) && defined(INET_WITH_IPv4)
    }
}

IpEcnCode EcnMarker::getEcn(const Packet *packet)
{
#if defined(INET_WITH_ETHERNET) && defined(INET_WITH_IPv4)
    auto protocol = packet->getTag<PacketProtocolTag>()->getProtocol();
    if (protocol == &Protocol::ethernetMac) {
        auto ethHeader = packet->peekAtFront<EthernetMacHeader>();
        if (isEth2Header(*ethHeader)) {
            const Protocol *payloadProtocol = ProtocolGroup::ethertype.getProtocol(ethHeader->getTypeOrLength());
            if (payloadProtocol == &Protocol::ipv4) {
                auto ipv4Header = packet->peekDataAt<Ipv4Header>(ethHeader->getChunkLength());
                return static_cast<IpEcnCode>(ipv4Header->getEcn());
            }
        }
    }
#endif // #if defined(INET_WITH_ETHERNET) && defined(INET_WITH_IPv4)
    return IP_ECN_NOT_ECT;
}

} // namespace queueing
} // namespace inet


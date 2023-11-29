//
// Copyright (C) 2013 OpenSim Ltd.
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

#include "inet/common/ProtocolGroup.h"
#include "inet/networklayer/common/IpProtocolId_m.h"

namespace inet {

ProtocolGroup::ProtocolGroup(const char *name, std::map<int, const Protocol *> protocolNumberToProtocol) :
    name(name),
    protocolNumberToProtocol(protocolNumberToProtocol)
{
    for (auto it : protocolNumberToProtocol) {
        protocols.push_back(it.second);
        protocolToProtocolNumber[it.second] = it.first;
    }
}

const Protocol *ProtocolGroup::findProtocol(int protocolNumber) const
{
    auto it = protocolNumberToProtocol.find(protocolNumber);
    return it != protocolNumberToProtocol.end() ? it->second : nullptr;
}

const Protocol *ProtocolGroup::getProtocol(int protocolNumber) const
{
    auto protocol = findProtocol(protocolNumber);
    if (protocol != nullptr)
        return protocol;
    else
        throw cRuntimeError("Unknown protocol: number = %d", protocolNumber);
}

int ProtocolGroup::findProtocolNumber(const Protocol *protocol) const
{
    auto it = protocolToProtocolNumber.find(protocol);
    return it != protocolToProtocolNumber.end() ? it->second : -1;
}

int ProtocolGroup::getProtocolNumber(const Protocol *protocol) const
{
    auto protocolNumber = findProtocolNumber(protocol);
    if (protocolNumber != -1)
        return protocolNumber;
    else
        throw cRuntimeError("Unknown protocol: id = %d, name = %s", protocol->getId(), protocol->getName());
}

void ProtocolGroup::addProtocol(int protocolId, const Protocol *protocol)
{
    protocols.push_back(protocol);
    protocolNumberToProtocol[protocolId] = protocol;
    protocolToProtocolNumber[protocol] = protocolId;
}

// FIXME use constants instead of numbers

// excerpt from http://www.iana.org/assignments/ieee-802-numbers/ieee-802-numbers.xhtml
ProtocolGroup ProtocolGroup::ethertype("ethertype", {
    { 0x0800, &Protocol::ipv4 },
    { 0x0806, &Protocol::arp },
    { 0x0807, &Protocol::lipsin_network},
    { 0x2000, &Protocol::cdp },               // TODO remove it, it's a CISCO code for LLC, ANSAINET project use it currently
    { 0x22EA, &Protocol::srp },
    { 0x22F0, &Protocol::tsn },
    { 0x22F3, &Protocol::trill },
    { 0x22F4, &Protocol::l2isis },
    { 0x36FC, &Protocol::flooding },          // INET specific non-standard protocol
    { 0x8100, &Protocol::ieee8021qCTag },
    { 0x86DD, &Protocol::ipv6 },
    { 0x86FD, &Protocol::probabilistic },     // INET specific non-standard protocol
    { 0x86FE, &Protocol::wiseRoute },         // INET specific non-standard protocol
    { 0x86FF, &Protocol::nextHopForwarding }, // INET specific non-standard protocol
    { 0x8808, &Protocol::ethernetFlowCtrl },
    { 0x8847, &Protocol::mpls },
    { 0x88A8, &Protocol::ieee8021qSTag },
    { 0x88CC, &Protocol::lldp },
    { 0x88E5, &Protocol::ieee8021ae },
    { 0x891d, &Protocol::tteth },
});

// excerpt from http://www.iana.org/assignments/ppp-numbers/ppp-numbers.xhtml
ProtocolGroup ProtocolGroup::pppprotocol("pppprotocol", {
    { 0x0021, &Protocol::ipv4 },
    { 0x0057, &Protocol::ipv6 },
    { 0x0281, &Protocol::mpls },
    { 0x39FC, &Protocol::flooding },          // INET specific non-standard protocol
    { 0x39FD, &Protocol::probabilistic },     // INET specific non-standard protocol
    { 0x39FE, &Protocol::wiseRoute },         // INET specific non-standard protocol
    { 0x39FF, &Protocol::nextHopForwarding }, // INET specific non-standard protocol
});

// excerpt from http://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml
ProtocolGroup ProtocolGroup::ipprotocol("ipprotocol", {
    { 1, &Protocol::icmpv4 }, // enum
    { 2, &Protocol::igmp },
    { 4, &Protocol::ipv4 },
    { 6, &Protocol::tcp },
    { 8, &Protocol::egp },
    { 9, &Protocol::igp },
    { 17, &Protocol::udp },
    { 36, &Protocol::xtp },
    { 41, &Protocol::ipv6 },
    { 46, &Protocol::rsvpTe },
    { 48, &Protocol::dsr },
    { 58, &Protocol::icmpv6 },
    { 88, &Protocol::eigrp },
    { 89, &Protocol::ospf },
    { 90, &Protocol::dtn  }, // zhf add code for dtn
    { 91, &Protocol::lipsin_app}, // zhf add code for lipsin_app
    { 92,  &Protocol::lipsin_network}, // zhf add code for lipsin_network
    { 93, &Protocol::lipsin_sender_app}, // zhf add code for lipsin_sender
    { 103, &Protocol::pim },
    { 132, &Protocol::sctp },
    { 135, &Protocol::mobileipv6 },
    { 138, &Protocol::manet },

    { 249, &Protocol::linkStateRouting },
    { 250, &Protocol::flooding },          // INET specific non-standard protocol
    { 251, &Protocol::probabilistic },     // INET specific non-standard protocol
    { 252, &Protocol::wiseRoute },         // INET specific non-standard protocol
    { 253, &Protocol::nextHopForwarding }, // INET specific non-standard protocol
    { 254, &Protocol::echo },              // INET specific non-standard protocol
});

ProtocolGroup ProtocolGroup::snapOui("snapOui", {
    //TODO do not add {0, .... }, it is a  special value: the protocolId contains the ethertype value
    // { 0x00000C, &Protocol::ciscoSnap } //TODO
});

ProtocolGroup ProtocolGroup::ieee8022protocol("ieee8022protocol", {
    { 0x4242, &Protocol::stp },
    { 0xAAAA, &Protocol::ieee8022snap },
    { 0xFE00, &Protocol::isis },
});

ProtocolGroup ProtocolGroup::udpprotocol("udpprotocol", {
    { 554, &Protocol::rtsp },
    { 6696, &Protocol::babel },
});

ProtocolGroup ProtocolGroup::tcpprotocol("tcpprotocol", {
    { 21, &Protocol::ftp },
    { 22, &Protocol::ssh },
    { 23, &Protocol::telnet },
    { 80, &Protocol::http },
    { 554, &Protocol::rtsp },
});

} // namespace inet


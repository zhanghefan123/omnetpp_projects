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

#include "inet/networklayer/contract/ipv6/Ipv6AddressType.h"

#ifdef INET_WITH_IPv6
#include "inet/networklayer/ipv6/Ipv6InterfaceData.h"
#endif // ifdef INET_WITH_IPv6

namespace inet {

Ipv6AddressType Ipv6AddressType::INSTANCE;

const Ipv6Address Ipv6AddressType::ALL_RIP_ROUTERS_MCAST("FF02::9");

L3Address Ipv6AddressType::getLinkLocalAddress(const NetworkInterface *ie) const
{
#ifdef INET_WITH_IPv6
    if (auto ipv6Data = ie->findProtocolData<Ipv6InterfaceData>())
        return ipv6Data->getLinkLocalAddress();
#endif // ifdef INET_WITH_IPv6
    return Ipv6Address::UNSPECIFIED_ADDRESS;
}

} // namespace inet


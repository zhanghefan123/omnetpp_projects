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

#ifndef __INET_ACCESSORYPROTOCOL_H
#define __INET_ACCESSORYPROTOCOL_H

#include "inet/common/Protocol.h"
#include "inet/common/packet/Packet.h"
#include "inet/queueing/contract/IPacketProcessor.h"

namespace inet {

class INET_API AccessoryProtocol
{
  public:
    static const Protocol acknowledge;
    static const Protocol aggregation;
    static const Protocol crc;
    static const Protocol destinationL3Address;
    static const Protocol destinationMacAddress;
    static const Protocol destinationPort;
    static const Protocol fcs;
    static const Protocol forwarding;
    static const Protocol fragmentation;
    static const Protocol hopLimit;
    static const Protocol sequenceNumber;
    static const Protocol withAcknowledge;
};

} // namespace inet

#endif


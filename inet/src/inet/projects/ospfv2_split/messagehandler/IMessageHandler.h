//
// Copyright (C) 2006 Andras Babos and Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//

#ifndef __INET_IMESSAGEHANDLER_H
#define __INET_IMESSAGEHANDLER_H

#include "inet/common/packet/Packet.h"
#include "inet/projects/ospfv2_split/Ospfv2Packet_m.h"

namespace inet {

namespace ospfv2_split {

class Router;
class Ospfv2Interface;
class Neighbor;

class INET_API IMessageHandler
{
  protected:
    Router *router;

  public:
    IMessageHandler(Router *containingRouter) { router = containingRouter; }
    virtual ~IMessageHandler() {}

    virtual void processPacket(Packet *, Ospfv2Interface *intf, Neighbor *neighbor) = 0;
};

} // namespace ospfv2_split

} // namespace inet

#endif


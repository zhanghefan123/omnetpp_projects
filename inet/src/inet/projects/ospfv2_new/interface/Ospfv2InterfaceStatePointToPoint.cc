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

#include "inet/projects/ospfv2_new/interface/Ospfv2InterfaceStatePointToPoint.h"

#include "inet/projects/ospfv2_new/interface/Ospfv2InterfaceStateDown.h"
#include "inet/projects/ospfv2_new/interface/Ospfv2InterfaceStateLoopback.h"
#include "inet/projects/ospfv2_new/messagehandler/MessageHandler.h"
#include "inet/projects/ospfv2_new/router/Ospfv2Area.h"
#include "inet/projects/ospfv2_new/router/Ospfv2Router.h"

namespace inet {
namespace ospfv2_new {

void InterfaceStatePointToPoint::processEvent(Ospfv2Interface *intf, Ospfv2Interface::Ospfv2InterfaceEventType event)
{
    if (event == Ospfv2Interface::INTERFACE_DOWN) {
        intf->reset();
        changeState(intf, new InterfaceStateDown, this);
    }
    else if (event == Ospfv2Interface::LOOP_INDICATION) {
        intf->reset();
        changeState(intf, new InterfaceStateLoopback, this);
    }
    else if (event == Ospfv2Interface::HELLO_TIMER) {
        if (intf->getType() == Ospfv2Interface::VIRTUAL) {
            if (intf->getNeighborCount() > 0) {
                intf->sendHelloPacket(intf->getNeighbor(0)->getAddress(), VIRTUAL_LINK_TTL);
            }
        }
        else {
            intf->sendHelloPacket(Ipv4Address::ALL_OSPF_ROUTERS_MCAST);
        }
        intf->getArea()->getRouter()->getMessageHandler()->startTimer(intf->getHelloTimer(), intf->getHelloInterval());
    }
    else if (event == Ospfv2Interface::ACKNOWLEDGEMENT_TIMER) {
        intf->sendDelayedAcknowledgements();
    }
}

} // namespace ospfv2_new
} // namespace inet


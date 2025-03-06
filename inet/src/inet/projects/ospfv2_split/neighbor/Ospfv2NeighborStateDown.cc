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

#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborStateDown.h"

#include "inet/projects/ospfv2_split/interface/Ospfv2Interface.h"
#include "inet/projects/ospfv2_split/messagehandler/MessageHandler.h"
#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborStateAttempt.h"
#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborStateInit.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Area.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Router.h"

namespace inet {

namespace ospfv2_split {

void NeighborStateDown::processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event)
{
    if (event == Neighbor::START) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        int ttl = (neighbor->getInterface()->getType() == Ospfv2Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;

        messageHandler->clearTimer(neighbor->getPollTimer());
        neighbor->getInterface()->
        sendHelloPacket(neighbor->getAddress(), ttl);
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
        changeState(neighbor, new NeighborStateAttempt, this);
    }
    else if (event == Neighbor::HELLO_RECEIVED) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getPollTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
        changeState(neighbor, new NeighborStateInit, this);
    }
    else if (event == Neighbor::POLL_TIMER) {
        int ttl = (neighbor->getInterface()->getType() == Ospfv2Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
        neighbor->getInterface()->sendHelloPacket(neighbor->getAddress(), ttl);
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->startTimer(neighbor->getPollTimer(), neighbor->getInterface()->getPollInterval());
    }
}

} // namespace ospfv2_split

} // namespace inet


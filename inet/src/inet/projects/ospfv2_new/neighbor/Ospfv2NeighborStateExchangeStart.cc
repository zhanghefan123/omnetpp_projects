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

#include "inet/projects/ospfv2_new/neighbor/Ospfv2NeighborStateExchangeStart.h"

#include "inet/projects/ospfv2_new/interface/Ospfv2Interface.h"
#include "inet/projects/ospfv2_new/messagehandler/MessageHandler.h"
#include "inet/projects/ospfv2_new/neighbor/Ospfv2NeighborStateDown.h"
#include "inet/projects/ospfv2_new/neighbor/Ospfv2NeighborStateExchange.h"
#include "inet/projects/ospfv2_new/neighbor/Ospfv2NeighborStateInit.h"
#include "inet/projects/ospfv2_new/neighbor/Ospfv2NeighborStateTwoWay.h"
#include "inet/projects/ospfv2_new/router/Ospfv2Area.h"
#include "inet/projects/ospfv2_new/router/Ospfv2Router.h"

namespace inet {

namespace ospfv2_new {

void NeighborStateExchangeStart::processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event)
{
    if ((event == Neighbor::KILL_NEIGHBOR) || (event == Neighbor::LINK_DOWN)) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        neighbor->reset();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        changeState(neighbor, new NeighborStateDown, this);
    }
    else if (event == Neighbor::INACTIVITY_TIMER) {
        neighbor->reset();
        if (neighbor->getInterface()->getType() == Ospfv2Interface::NBMA) {
            MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
            messageHandler->startTimer(neighbor->getPollTimer(), neighbor->getInterface()->getPollInterval());
        }
        changeState(neighbor, new NeighborStateDown, this);
    }
    else if (event == Neighbor::ONEWAY_RECEIVED) {
        neighbor->reset();
        changeState(neighbor, new NeighborStateInit, this);
    }
    else if (event == Neighbor::HELLO_RECEIVED) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
    }
    else if (event == Neighbor::IS_ADJACENCY_OK) {
        if (!neighbor->needAdjacency()) {
            neighbor->reset();
            changeState(neighbor, new NeighborStateTwoWay, this);
        }
    }
    else if (event == Neighbor::DD_RETRANSMISSION_TIMER) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        neighbor->retransmitDatabaseDescriptionPacket();
        messageHandler->startTimer(neighbor->getDDRetransmissionTimer(), neighbor->getInterface()->getRetransmissionInterval());
    }
    else if (event == Neighbor::NEGOTIATION_DONE) {
        neighbor->createDatabaseSummary();
        neighbor->sendDatabaseDescriptionPacket();
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getDDRetransmissionTimer());
        changeState(neighbor, new NeighborStateExchange, this);
    }
}

} // namespace ospfv2_new

} // namespace inet


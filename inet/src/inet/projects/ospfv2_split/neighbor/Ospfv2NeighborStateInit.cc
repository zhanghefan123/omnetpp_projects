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

#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborStateInit.h"

#include "inet/projects/ospfv2_split/interface/Ospfv2Interface.h"
#include "inet/projects/ospfv2_split/messagehandler/MessageHandler.h"
#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborStateDown.h"
#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborStateExchangeStart.h"
#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborStateTwoWay.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Area.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Router.h"

namespace inet {
namespace ospfv2_split {

void NeighborStateInit::processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event)
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
    else if (event == Neighbor::HELLO_RECEIVED) {
        MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
    }
    else if (event == Neighbor::TWOWAY_RECEIVED) {
        if (neighbor->needAdjacency()) {
            MessageHandler *messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
            if (!(neighbor->isFirstAdjacencyInited())) {
                neighbor->initFirstAdjacency();
            }
            else {
                neighbor->incrementDDSequenceNumber();
            }
            neighbor->sendDatabaseDescriptionPacket(true);
            messageHandler->startTimer(neighbor->getDDRetransmissionTimer(), neighbor->getInterface()->getRetransmissionInterval());
            changeState(neighbor, new NeighborStateExchangeStart, this);
        }
        else {
            changeState(neighbor, new NeighborStateTwoWay, this);
        }
    }
}

} // namespace ospfv2_split
} // namespace inet


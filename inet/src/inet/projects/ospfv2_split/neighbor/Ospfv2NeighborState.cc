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

#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborState.h"

#include "inet/projects/ospfv2_split/interface/Ospfv2Interface.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Area.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Router.h"

namespace inet {
namespace ospfv2_split {

void NeighborState::changeState(Neighbor *neighbor, NeighborState *newState, NeighborState *currentState)
{
    neighbor->changeState(newState, currentState);

    if ((currentState->getState() == Neighbor::FULL_STATE) || (newState->getState() == Neighbor::FULL_STATE))
        if (updateLsa(neighbor))
            neighbor->getInterface()->getArea()->getRouter()->rebuildRoutingTable();
}

bool NeighborState::updateLsa(Neighbor *neighbor)
{
    bool shouldRebuildRoutingTable = false;
    RouterId routerID = neighbor->getInterface()->getArea()->getRouter()->getRouterID();
    RouterLsa *routerLSA = neighbor->getInterface()->getArea()->findRouterLSA(routerID);

    if (routerLSA != nullptr) {
        long sequenceNumber = routerLSA->getHeader().getLsSequenceNumber();
        if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
            routerLSA->getHeaderForUpdate().setLsAge(MAX_AGE);
            neighbor->getInterface()->getArea()->floodLSA(routerLSA);
            routerLSA->incrementInstallTime();
        }
        else {
            RouterLsa *newLSA = neighbor->getInterface()->getArea()->originateRouterLSA();

            newLSA->getHeaderForUpdate().setLsSequenceNumber(sequenceNumber + 1);
            shouldRebuildRoutingTable |= routerLSA->update(newLSA);
            delete newLSA;

            neighbor->getInterface()->getArea()->floodLSA(routerLSA);
        }
    }

    if (neighbor->getInterface()->getState() == Ospfv2Interface::DESIGNATED_ROUTER_STATE) {
        NetworkLsa *networkLSA = neighbor->getInterface()->getArea()->findNetworkLSA(neighbor->getInterface()->getAddressRange().address);

        if (networkLSA != nullptr) {
            long sequenceNumber = networkLSA->getHeader().getLsSequenceNumber();
            if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
                networkLSA->getHeaderForUpdate().setLsAge(MAX_AGE);
                neighbor->getInterface()->getArea()->floodLSA(networkLSA);
                networkLSA->incrementInstallTime();
            }
            else {
                NetworkLsa *newLSA = neighbor->getInterface()->getArea()->originateNetworkLSA(neighbor->getInterface());

                if (newLSA != nullptr) {
                    newLSA->getHeaderForUpdate().setLsSequenceNumber(sequenceNumber + 1);
                    shouldRebuildRoutingTable |= networkLSA->update(newLSA);
                    delete newLSA;
                }
                else { // no neighbors on the network -> old NetworkLsa must be flushed
                    networkLSA->getHeaderForUpdate().setLsAge(MAX_AGE);
                    networkLSA->incrementInstallTime();
                }

                neighbor->getInterface()->getArea()->floodLSA(networkLSA);
            }
        }
    }

    return shouldRebuildRoutingTable;
}

} // namespace ospfv2_split
} // namespace inet


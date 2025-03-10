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

#include "inet/projects/ospfv2_split/messagehandler/HelloHandler.h"

#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/projects/ospfv2_split/interface/Ospfv2Interface.h"
#include "inet/projects/ospfv2_split/neighbor/Ospfv2Neighbor.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Area.h"
#include "inet/projects/ospfv2_split/router/Ospfv2Router.h"

namespace inet {
namespace ospfv2_split {

HelloHandler::HelloHandler(Router *containingRouter) :
    IMessageHandler(containingRouter)
{
}

void HelloHandler::processPacket(Packet *packet, Ospfv2Interface *intf, Neighbor *unused)
{
    const auto& helloPacket = packet->peekAtFront<Ospfv2HelloPacket>();
    bool shouldRebuildRoutingTable = false;

    /* The values of the Network Mask, HelloInterval,
       and RouterDeadInterval fields in the received Hello packet must
       be checked against the values configured for the receiving
       interface.  Any mismatch causes processing to stop and the
       packet to be dropped.
     */
    if ((intf->getHelloInterval() == helloPacket->getHelloInterval()) &&
        (intf->getRouterDeadInterval() == helloPacket->getRouterDeadInterval()))
    {
        Ospfv2Interface::Ospfv2InterfaceType interfaceType = intf->getType();
        /* There is one exception to the above rule: on point-to-point
           networks and on virtual links, the Network Mask in the received
           Hello Packet should be ignored.
         */
        if (!((interfaceType != Ospfv2Interface::POINTTOPOINT) &&
              (interfaceType != Ospfv2Interface::VIRTUAL) &&
              (intf->getAddressRange().mask != helloPacket->getNetworkMask())
              )
            )
        {
            /* The setting of the E-bit found in the Hello Packet's Options field must match this area's
               ExternalRoutingCapability.
             */
            if (intf->getArea()->getExternalRoutingCapability() == helloPacket->getOptions().E_ExternalRoutingCapability) {
                Ipv4Address srcAddress = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv4();
                bool neighborChanged = false;
                bool neighborsDRStateChanged = false;
                bool drChanged = false;
                bool backupSeen = false;
                Neighbor *neighbor;

                /* If the receiving interface connects to a broadcast, Point-to-
                   MultiPoint or NBMA network the source is identified by the IP
                   source address found in the Hello's IP header.
                 */
                if ((interfaceType == Ospfv2Interface::BROADCAST) ||
                    (interfaceType == Ospfv2Interface::POINTTOMULTIPOINT) ||
                    (interfaceType == Ospfv2Interface::NBMA))
                {
                    neighbor = intf->getNeighborByAddress(srcAddress);
                }
                else {
                    /* If the receiving interface connects to a point-to-point link or a virtual link,
                       the source is identified by the Router ID found in the Hello's OSPF packet header.
                     */
                    neighbor = intf->getNeighborById(helloPacket->getRouterID());
                }

                if (neighbor != nullptr) {
                    router->getMessageHandler()->printEvent("Hello packet received", intf, neighbor);

                    Ipv4Address designatedAddress = neighbor->getDesignatedRouter().ipInterfaceAddress;
                    Ipv4Address backupAddress = neighbor->getBackupDesignatedRouter().ipInterfaceAddress;
                    char newPriority = helloPacket->getRouterPriority();
                    Ipv4Address source = srcAddress;
                    Ipv4Address newDesignatedRouter = helloPacket->getDesignatedRouter();
                    Ipv4Address newBackupRouter = helloPacket->getBackupDesignatedRouter();
                    DesignatedRouterId dRouterID;

                    if ((interfaceType == Ospfv2Interface::VIRTUAL) &&
                        (neighbor->getState() == Neighbor::DOWN_STATE))
                    {
                        neighbor->setPriority(helloPacket->getRouterPriority());
                        neighbor->setRouterDeadInterval(helloPacket->getRouterDeadInterval());
                    }

                    /* If a change in the neighbor's Router Priority field
                       was noted, the receiving interface's state machine is
                       scheduled with the event NEIGHBOR_CHANGE.
                     */
                    if (neighbor->getPriority() != newPriority) {
                        neighborChanged = true;
                    }

                    /* If the neighbor is both declaring itself to be Designated
                       Router(Hello Packet's Designated Router field = Neighbor IP
                       address) and the Backup Designated Router field in the
                       packet is equal to 0.0.0.0 and the receiving interface is in
                       state Waiting, the receiving interface's state machine is
                       scheduled with the event BACKUP_SEEN.
                     */
                    if ((newDesignatedRouter == source) &&
                        (newBackupRouter == NULL_IPV4ADDRESS) &&
                        (intf->getState() == Ospfv2Interface::WAITING_STATE))
                    {
                        backupSeen = true;
                    }
                    else {
                        /* Otherwise, if the neighbor is declaring itself to be Designated Router and it
                           had not previously, or the neighbor is not declaring itself
                           Designated Router where it had previously, the receiving
                           interface's state machine is scheduled with the event
                           NEIGHBOR_CHANGE.
                         */
                        if (((newDesignatedRouter == source) &&
                             (newDesignatedRouter != designatedAddress)) ||
                            ((newDesignatedRouter != source) &&
                             (source == designatedAddress)))
                        {
                            neighborChanged = true;
                            neighborsDRStateChanged = true;
                        }
                    }

                    /* If the neighbor is declaring itself to be Backup Designated
                       Router(Hello Packet's Backup Designated Router field =
                       Neighbor IP address) and the receiving interface is in state
                       Waiting, the receiving interface's state machine is
                       scheduled with the event BACKUP_SEEN.
                     */
                    if ((newBackupRouter == source) &&
                        (intf->getState() == Ospfv2Interface::WAITING_STATE))
                    {
                        backupSeen = true;
                    }
                    else {
                        /* Otherwise, if the neighbor is declaring itself to be Backup Designated Router
                           and it had not previously, or the neighbor is not declaring
                           itself Backup Designated Router where it had previously, the
                           receiving interface's state machine is scheduled with the
                           event NEIGHBOR_CHANGE.
                         */
                        if (((newBackupRouter == source) &&
                             (newBackupRouter != backupAddress)) ||
                            ((newBackupRouter != source) &&
                             (source == backupAddress)))
                        {
                            neighborChanged = true;
                        }
                    }

                    neighbor->setNeighborID(helloPacket->getRouterID());
                    neighbor->setPriority(newPriority);
                    neighbor->setAddress(srcAddress);
                    dRouterID.routerID = newDesignatedRouter;
                    dRouterID.ipInterfaceAddress = newDesignatedRouter;
                    if (newDesignatedRouter != designatedAddress) {
                        designatedAddress = dRouterID.ipInterfaceAddress;
                        drChanged = true;
                    }
                    neighbor->setDesignatedRouter(dRouterID);
                    dRouterID.routerID = newBackupRouter;
                    dRouterID.ipInterfaceAddress = newBackupRouter;
                    if (newBackupRouter != backupAddress) {
                        backupAddress = dRouterID.ipInterfaceAddress;
                        drChanged = true;
                    }
                    neighbor->setBackupDesignatedRouter(dRouterID);
                    if (drChanged) {
                        neighbor->setupDesignatedRouters(false);
                    }

                    /* If the neighbor router's Designated or Backup Designated Router
                       has changed it's necessary to look up the Router IDs belonging to the
                       new addresses.
                     */
                    if (!neighbor->designatedRoutersAreSetUp()) {
                        Neighbor *designated = intf->getNeighborByAddress(designatedAddress);
                        Neighbor *backup = intf->getNeighborByAddress(backupAddress);

                        if (designated != nullptr) {
                            dRouterID.routerID = designated->getNeighborID();
                            dRouterID.ipInterfaceAddress = designated->getAddress();
                            neighbor->setDesignatedRouter(dRouterID);
                        }
                        if (backup != nullptr) {
                            dRouterID.routerID = backup->getNeighborID();
                            dRouterID.ipInterfaceAddress = backup->getAddress();
                            neighbor->setBackupDesignatedRouter(dRouterID);
                        }
                        if ((designated != nullptr) && (backup != nullptr)) {
                            neighbor->setupDesignatedRouters(true);
                        }
                    }
                }
                else {
                    DesignatedRouterId dRouterID;
                    bool designatedSetUp = false;
                    bool backupSetUp = false;

                    neighbor = new Neighbor(helloPacket->getRouterID());

                    // =================== zhf add code to set area id ===================
                    neighbor->setArea(helloPacket->getArea());
                    // =================== zhf add code to set area id ===================

                    neighbor->setPriority(helloPacket->getRouterPriority());
                    neighbor->setAddress(srcAddress);
                    neighbor->setRouterDeadInterval(helloPacket->getRouterDeadInterval());

                    router->getMessageHandler()->printEvent("Hello packet received", intf, neighbor);

                    dRouterID.routerID = helloPacket->getDesignatedRouter();
                    dRouterID.ipInterfaceAddress = dRouterID.routerID;

                    Neighbor *designated = intf->getNeighborByAddress(dRouterID.ipInterfaceAddress);

                    // Get the Designated Router ID from the corresponding Neighbor Object.
                    if (designated != nullptr) {
                        if (designated->getNeighborID() != dRouterID.routerID) {
                            dRouterID.routerID = designated->getNeighborID();
                        }
                        designatedSetUp = true;
                    }
                    neighbor->setDesignatedRouter(dRouterID);

                    dRouterID.routerID = helloPacket->getBackupDesignatedRouter();
                    dRouterID.ipInterfaceAddress = dRouterID.routerID;

                    Neighbor *backup = intf->getNeighborByAddress(dRouterID.ipInterfaceAddress);

                    // Get the Backup Designated Router ID from the corresponding Neighbor Object.
                    if (backup != nullptr) {
                        if (backup->getNeighborID() != dRouterID.routerID) {
                            dRouterID.routerID = backup->getNeighborID();
                        }
                        backupSetUp = true;
                    }
                    neighbor->setBackupDesignatedRouter(dRouterID);
                    if (designatedSetUp && backupSetUp) {
                        neighbor->setupDesignatedRouters(true);
                    }
                    intf->addNeighbor(neighbor);
                }

                neighbor->processEvent(Neighbor::HELLO_RECEIVED);
                if ((interfaceType == Ospfv2Interface::NBMA) &&
                    (intf->getRouterPriority() == 0) &&
                    (neighbor->getState() >= Neighbor::INIT_STATE))
                {
                    intf->sendHelloPacket(neighbor->getAddress());
                }

                Ipv4Address interfaceAddress = intf->getAddressRange().address;
                unsigned int neighborsNeighborCount = helloPacket->getNeighborArraySize();
                unsigned int i;
                /* The list of neighbors contained in the Hello Packet is
                   examined.  If the router itself appears in this list, the
                   neighbor state machine should be executed with the event TWOWAY_RECEIVED.
                 */
                for (i = 0; i < neighborsNeighborCount; i++) {
                    if (helloPacket->getNeighbor(i) == interfaceAddress) {
                        neighbor->processEvent(Neighbor::TWOWAY_RECEIVED);
                        break;
                    }
                }
                /* Otherwise, the neighbor state machine should
                   be executed with the event ONEWAY_RECEIVED, and the processing
                   of the packet stops.
                 */
                if (i == neighborsNeighborCount) {
                    neighbor->processEvent(Neighbor::ONEWAY_RECEIVED);
                }

                if (neighborChanged) {
                    intf->processEvent(Ospfv2Interface::NEIGHBOR_CHANGE);
                    /* In some cases neighbors get stuck in TwoWay state after a DR
                       or Backup change. (calculateDesignatedRouter runs before the
                       neighbors' signal of DR change + this router does not become
                       neither DR nor backup -> IS_ADJACENCY_OK does not get called.)
                       So to make it work(workaround) we'll call IS_ADJACENCY_OK for
                       all neighbors in TwoWay state from here. This shouldn't break
                       anything because if the neighbor state doesn't have to change
                       then needAdjacency returns false and nothing happnes in
                       IS_ADJACENCY_OK.
                     */
                    unsigned int neighborCount = intf->getNeighborCount();
                    for (i = 0; i < neighborCount; i++) {
                        Neighbor *stuckNeighbor = intf->getNeighbor(i);
                        if (stuckNeighbor->getState() == Neighbor::TWOWAY_STATE) {
                            stuckNeighbor->processEvent(Neighbor::IS_ADJACENCY_OK);
                        }
                    }

                    if (neighborsDRStateChanged) {
                        RouterLsa *routerLSA = intf->getArea()->findRouterLSA(router->getRouterID());

                        if (routerLSA != nullptr) {
                            long sequenceNumber = routerLSA->getHeader().getLsSequenceNumber();
                            if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
                                routerLSA->getHeaderForUpdate().setLsAge(MAX_AGE);
                                intf->getArea()->floodLSA(routerLSA);
                                routerLSA->incrementInstallTime();
                            }
                            else {
                                RouterLsa *newLSA = intf->getArea()->originateRouterLSA();

                                newLSA->getHeaderForUpdate().setLsSequenceNumber(sequenceNumber + 1);
                                shouldRebuildRoutingTable |= routerLSA->update(newLSA);
                                delete newLSA;

                                intf->getArea()->floodLSA(routerLSA);
                            }
                        }
                    }
                }

                if (backupSeen) {
                    intf->processEvent(Ospfv2Interface::BACKUP_SEEN);
                }
            }
        }
    }

    if (shouldRebuildRoutingTable) {
        router->rebuildRoutingTable();
    }
}

} // namespace ospfv2_split
} // namespace inet


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

#ifndef __INET_MESSAGEHANDLER_H
#define __INET_MESSAGEHANDLER_H

#include "inet/projects/ospfv2_new/interface/Ospfv2Interface.h"
#include "inet/projects/ospfv2_new/messagehandler/DatabaseDescriptionHandler.h"
#include "inet/projects/ospfv2_new/messagehandler/HelloHandler.h"
#include "inet/projects/ospfv2_new/messagehandler/IMessageHandler.h"
#include "inet/projects/ospfv2_new/messagehandler/LinkStateAcknowledgementHandler.h"
#include "inet/projects/ospfv2_new/messagehandler/LinkStateRequestHandler.h"
#include "inet/projects/ospfv2_new/messagehandler/LinkStateUpdateHandler.h"

namespace inet {
namespace ospfv2_new {

class INET_API MessageHandler : public IMessageHandler
{
  private:
    cSimpleModule *ospfModule;

    HelloHandler helloHandler;
    DatabaseDescriptionHandler ddHandler;
    LinkStateRequestHandler lsRequestHandler;
    LinkStateUpdateHandler lsUpdateHandler;
    LinkStateAcknowledgementHandler lsAckHandler;

  public:
    MessageHandler(Router *containingRouter, cSimpleModule *containingModule);

    void messageReceived(cMessage *message);
    void handleTimer(cMessage *timer);

    void processPacket(Packet *packet, Ospfv2Interface *unused1 = nullptr, Neighbor *unused2 = nullptr) override;

    void sendPacket(Packet *packet, Ipv4Address destination, Ospfv2Interface *outputIf, short ttl = 1);
    void clearTimer(cMessage *timer);
    void startTimer(cMessage *timer, simtime_t delay);

    void printEvent(const char *eventString, const Ospfv2Interface *onInterface = nullptr, const Neighbor *forNeighbor = nullptr) const;
    void printHelloPacket(const Ospfv2HelloPacket *helloPacket, Ipv4Address destination, int outputIfIndex) const;
    void printDatabaseDescriptionPacket(const Ospfv2DatabaseDescriptionPacket *ddPacket, Ipv4Address destination, int outputIfIndex) const;
    void printLinkStateRequestPacket(const Ospfv2LinkStateRequestPacket *requestPacket, Ipv4Address destination, int outputIfIndex) const;
    void printLinkStateUpdatePacket(const Ospfv2LinkStateUpdatePacket *updatePacket, Ipv4Address destination, int outputIfIndex) const;
    void printLinkStateAcknowledgementPacket(const Ospfv2LinkStateAcknowledgementPacket *ackPacket, Ipv4Address destination, int outputIfIndex) const;

    // Authentication not implemented
    bool authenticatePacket(const Ospfv2Packet *packet) { return true; }
};

} // namespace ospfv2_new
} // namespace inet

#endif


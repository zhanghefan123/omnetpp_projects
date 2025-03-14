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

#ifndef __INET_LINKSTATEUPDATEHANDLER_H
#define __INET_LINKSTATEUPDATEHANDLER_H

#include "inet/projects/ospfv2_new/messagehandler/IMessageHandler.h"
#include "inet/projects/ospfv2_new/router/Ospfv2Common.h"

namespace inet {

namespace ospfv2_new {

class INET_API LinkStateUpdateHandler : public IMessageHandler
{
  private:
    struct AcknowledgementFlags {
        bool floodedBackOut;
        bool lsaIsNewer;
        bool lsaIsDuplicate;
        bool impliedAcknowledgement;
        bool lsaReachedMaxAge;
        bool noLSAInstanceInDatabase;
        bool anyNeighborInExchangeOrLoadingState;
    };

  private:
    bool validateLSChecksum(const Ospfv2Lsa *lsa) { return true; } // not implemented
    void acknowledgeLSA(const Ospfv2LsaHeader& lsaHeader, Ospfv2Interface *intf, AcknowledgementFlags acknowledgementFlags, RouterId lsaSource);

  public:
    LinkStateUpdateHandler(Router *containingRouter);

    void processPacket(Packet *packet, Ospfv2Interface *intf, Neighbor *neighbor) override;
};

} // namespace ospfv2_new

} // namespace inet

#endif


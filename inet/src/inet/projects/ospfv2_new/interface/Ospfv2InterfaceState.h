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

#ifndef __INET_OSPFV2INTERFACESTATE_H
#define __INET_OSPFV2INTERFACESTATE_H

#include "inet/projects/ospfv2_new/interface/Ospfv2Interface.h"

namespace inet {

namespace ospfv2_new {

class INET_API Ospfv2InterfaceState
{
  protected:
    void changeState(Ospfv2Interface *intf, Ospfv2InterfaceState *newState, Ospfv2InterfaceState *currentState);
    void calculateDesignatedRouter(Ospfv2Interface *intf);
    void printElectionResult(const Ospfv2Interface *onInterface, DesignatedRouterId DR, DesignatedRouterId BDR);

  public:
    virtual ~Ospfv2InterfaceState() {}

    virtual void processEvent(Ospfv2Interface *intf, Ospfv2Interface::Ospfv2InterfaceEventType event) = 0;
    virtual Ospfv2Interface::Ospfv2InterfaceStateType getState() const = 0;
};

} // namespace ospfv2_new

} // namespace inet

#endif


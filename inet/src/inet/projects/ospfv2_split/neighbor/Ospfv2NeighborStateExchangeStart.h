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

#ifndef __INET_OSPFV2NEIGHBORSTATEEXCHANGESTART_H
#define __INET_OSPFV2NEIGHBORSTATEEXCHANGESTART_H

#include "inet/projects/ospfv2_split/neighbor/Ospfv2NeighborState.h"

namespace inet {

namespace ospfv2_split {

class INET_API NeighborStateExchangeStart : public NeighborState
{
  public:
    virtual void processEvent(Neighbor *neighbor, Neighbor::NeighborEventType event) override;
    virtual Neighbor::NeighborStateType getState() const override { return Neighbor::EXCHANGE_START_STATE; }
};

} // namespace ospfv2_split

} // namespace inet

#endif


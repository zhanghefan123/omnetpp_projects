//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __INET_FRAGMENTERBASE_H
#define __INET_FRAGMENTERBASE_H

#include "inet/protocolelement/fragmentation/contract/IFragmenterPolicy.h"
#include "inet/queueing/base/PacketPusherBase.h"

namespace inet {

using namespace inet::queueing;

class INET_API FragmenterBase : public PacketPusherBase
{
  protected:
    bool deleteSelf;
    IFragmenterPolicy *fragmenterPolicy = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual IFragmenterPolicy *createFragmenterPolicy(const char *fragmenterPolicyClass) const;
    virtual Packet *createFragmentPacket(Packet *packet, b fragmentOffset, b fragmentLength, int fragmentNumber, int numFragments);

  public:
    virtual void pushPacket(Packet *packet, cGate *gate) override;
};

} // namespace inet

#endif


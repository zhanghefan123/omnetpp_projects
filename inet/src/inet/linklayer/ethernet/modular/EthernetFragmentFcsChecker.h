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

#ifndef __INET_ETHERNETFRAGMENTFCSCHECKER_H
#define __INET_ETHERNETFRAGMENTFCSCHECKER_H

#include "inet/protocolelement/checksum/base/FcsCheckerBase.h"

namespace inet {

using namespace inet::queueing;

class INET_API EthernetFragmentFcsChecker : public FcsCheckerBase
{
  protected:
    uint32_t lastFragmentCompleteFcs = 0;
    mutable uint32_t currentFragmentCompleteFcs = 0;

  protected:
    virtual bool checkComputedFcs(const Packet *packet, uint32_t fcs) const override;
    virtual bool checkFcs(const Packet *packet, FcsMode fcsMode, uint32_t fcs) const override;
    virtual void processPacket(Packet *packet) override;
    virtual void dropPacket(Packet *packet) override;

  public:
    virtual bool matchesPacket(const Packet *packet) const override;
};

} // namespace inet

#endif


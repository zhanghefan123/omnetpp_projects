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

#ifndef __INET_IEEE8022LLCCHECKER_H
#define __INET_IEEE8022LLCCHECKER_H

#include "inet/common/Protocol.h"
#include "inet/linklayer/ieee8022/Ieee8022LlcHeader_m.h"
#include "inet/queueing/base/PacketFilterBase.h"

namespace inet {

using namespace inet::queueing;

class INET_API Ieee8022LlcChecker : public PacketFilterBase
{
  protected:
    virtual void initialize(int stage) override;
    virtual void processPacket(Packet *packet) override;
    virtual void dropPacket(Packet *packet) override;

  public:
    virtual bool matchesPacket(const Packet *packet) const override;

    static const Protocol *getProtocol(const Ptr<const Ieee8022LlcHeader>& header);
};

} // namespace inet

#endif


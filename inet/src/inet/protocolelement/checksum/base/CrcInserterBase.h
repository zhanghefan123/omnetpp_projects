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

#ifndef __INET_CRCINSERTERBASE_H
#define __INET_CRCINSERTERBASE_H

#include "inet/queueing/base/PacketFlowBase.h"
#include "inet/transportlayer/common/CrcMode_m.h"

namespace inet {

using namespace inet::queueing;

class INET_API CrcInserterBase : public PacketFlowBase
{
  protected:
    CrcMode crcMode = CRC_MODE_UNDEFINED;

  protected:
    virtual void initialize(int stage) override;

    virtual uint16_t computeDisabledCrc(const Packet *packet) const;
    virtual uint16_t computeDeclaredCorrectCrc(const Packet *packet) const;
    virtual uint16_t computeDeclaredIncorrectCrc(const Packet *packet) const;
    virtual uint16_t computeComputedCrc(const Packet *packet) const;
    virtual uint16_t computeCrc(const Packet *packet, CrcMode crcMode) const;
};

} // namespace inet

#endif


//
// Copyright (C) 2012 OpenSim Ltd.
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

#ifndef __INET_TOKENBUCKETMETER_H
#define __INET_TOKENBUCKETMETER_H

#include "inet/common/INETMath.h"
#include "inet/networklayer/diffserv/PacketMeterBase.h"

namespace inet {

/**
 * Simple token bucket meter.
 */
class INET_API TokenBucketMeter : public PacketMeterBase
{
  protected:
    double CIR = NaN; // Commited Information Rate (bits/sec)
    long CBS = 0; // Committed Burst Size (in bits)
    bool colorAwareMode = false;

    long Tc = 0; // token bucket for committed burst
    simtime_t lastUpdateTime;

    int numRcvd = 0;
    int numRed = 0;

  public:
    TokenBucketMeter() {}

  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void pushPacket(Packet *packet, cGate *gate) override;
    virtual void refreshDisplay() const override;

    virtual int meterPacket(Packet *packet) override;
};

} // namespace inet

#endif


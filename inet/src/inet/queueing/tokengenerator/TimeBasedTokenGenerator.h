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

#ifndef __INET_TIMEBASEDTOKENGENERATOR_H
#define __INET_TIMEBASEDTOKENGENERATOR_H

#include "inet/common/clock/ClockUserModuleMixin.h"
#include "inet/queueing/base/TokenGeneratorBase.h"

namespace inet {
namespace queueing {

class INET_API TimeBasedTokenGenerator : public ClockUserModuleMixin<TokenGeneratorBase>
{
  protected:
    cPar *generationIntervalParameter = nullptr;
    cPar *numTokensParameter = nullptr;

    ClockEvent *generationTimer = nullptr;

  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void scheduleGenerationTimer();

  public:
    virtual ~TimeBasedTokenGenerator() { cancelAndDeleteClockEvent(generationTimer); }

    virtual bool supportsPacketPushing(cGate *gate) const override { return false; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return false; }
};

} // namespace queueing
} // namespace inet

#endif


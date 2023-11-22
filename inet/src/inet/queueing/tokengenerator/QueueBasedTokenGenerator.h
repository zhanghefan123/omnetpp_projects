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

#ifndef __INET_QUEUEBASEDTOKENGENERATOR_H
#define __INET_QUEUEBASEDTOKENGENERATOR_H

#include "inet/queueing/base/TokenGeneratorBase.h"
#include "inet/queueing/contract/IPacketQueue.h"

namespace inet {
namespace queueing {

class INET_API QueueBasedTokenGenerator : public TokenGeneratorBase, public cListener
{
  protected:
    int minNumPackets = -1;
    b minTotalLength = b(-1);
    IPacketQueue *queue = nullptr;
    cPar *numTokensParameter = nullptr;

  protected:
    virtual void initialize(int stage) override;

    virtual void generateTokens();

  public:
    virtual bool supportsPacketPushing(cGate *gate) const override { return false; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return false; }

    virtual void receiveSignal(cComponent *source, simsignal_t signal, cObject *object, cObject *details) override;
};

} // namespace queueing
} // namespace inet

#endif


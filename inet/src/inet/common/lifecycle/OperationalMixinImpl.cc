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

#include "inet/common/lifecycle/OperationalMixinImpl.h"

#include "inet/protocolelement/transceiver/base/PacketReceiverBase.h"
#include "inet/protocolelement/transceiver/base/PacketTransmitterBase.h"

namespace inet {

template class OperationalMixin<cSimpleModule>;

#ifdef INET_WITH_QUEUEING
template class OperationalMixin<PacketProcessorBase>;
#endif // #ifdef INET_WITH_QUEUEING

} // namespace inet


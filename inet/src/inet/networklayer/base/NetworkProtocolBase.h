//
// Copyright (C) 2013 OpenSim Ltd.
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

#ifndef __INET_NETWORKPROTOCOLBASE_H
#define __INET_NETWORKPROTOCOLBASE_H

#include <map>
#include <set>

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/networklayer/contract/IInterfaceTable.h"

namespace inet {

class INET_API NetworkProtocolBase : public LayeredProtocolBase, public DefaultProtocolRegistrationListener
{
  protected:
    struct SocketDescriptor {
        int socketId = -1;
        int protocolId = -1;
        L3Address localAddress;
        L3Address remoteAddress;

        SocketDescriptor(int socketId, int protocolId, L3Address localAddress)
            : socketId(socketId), protocolId(protocolId), localAddress(localAddress) {}
    };

    IInterfaceTable *interfaceTable;
    // working vars
    std::set<const Protocol *> upperProtocols;
    std::map<int, SocketDescriptor *> socketIdToSocketDescriptor;

  protected:
    NetworkProtocolBase();
    virtual ~NetworkProtocolBase() { for (auto entry : socketIdToSocketDescriptor) delete entry.second; }

    virtual void initialize(int stage) override;

    virtual void sendUp(cMessage *message);
    virtual void sendDown(cMessage *message, int interfaceId = -1);

    virtual bool isUpperMessage(cMessage *message) override;
    virtual bool isLowerMessage(cMessage *message) override;

    virtual bool isInitializeStage(int stage) override { return stage == INITSTAGE_NETWORK_LAYER; }
    virtual bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_NETWORK_LAYER; }
    virtual bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_NETWORK_LAYER; }

    virtual void handleUpperCommand(cMessage *msg) override;

    virtual const Protocol& getProtocol() const = 0;

  public:
    virtual void handleRegisterService(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;
    virtual void handleRegisterProtocol(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;
};

} // namespace inet

#endif


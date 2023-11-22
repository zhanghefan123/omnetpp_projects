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

#ifndef __INET_MESSAGEDISPATCHER_H
#define __INET_MESSAGEDISPATCHER_H

#include "inet/common/IInterfaceRegistrationListener.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/packet/Message.h"
#include "inet/common/packet/Packet.h"
#ifdef INET_WITH_QUEUEING
#include "inet/queueing/base/PacketProcessorBase.h"
#include "inet/queueing/contract/IActivePacketSource.h"
#include "inet/queueing/contract/IPassivePacketSink.h"
#endif // #ifdef INET_WITH_QUEUEING

namespace inet {

/**
 * This class implements the corresponding module. See module documentation for more details.
 */
class INET_API MessageDispatcher :
#ifdef INET_WITH_QUEUEING
    public queueing::PacketProcessorBase, public queueing::IActivePacketSource, public queueing::IPassivePacketSink,
#else
    public cSimpleModule,
#endif // #ifdef INET_WITH_QUEUEING
    public DefaultProtocolRegistrationListener, public IInterfaceRegistrationListener
{
  public:
    class Key {
      protected:
        int protocolId;
        int servicePrimitive;

      public:
        Key(int protocolId, ServicePrimitive servicePrimitive) : protocolId(protocolId), servicePrimitive(servicePrimitive) {}

        bool operator<(const MessageDispatcher::Key& other) const {
            if (protocolId < other.protocolId)
                return true;
            else if (protocolId > other.protocolId)
                return false;
            else
                return servicePrimitive < other.servicePrimitive;
        }

        friend std::ostream& operator<<(std::ostream& out, const MessageDispatcher::Key& foo);
    };

  protected:
    std::map<int, int> socketIdToGateIndex;
    std::map<int, int> interfaceIdToGateIndex;
    std::map<Key, int> serviceToGateIndex;
    std::map<Key, int> protocolToGateIndex;

  protected:
    virtual void initialize(int stage) override;
    virtual void arrived(cMessage *message, cGate *gate, const SendOptions& options, simtime_t time) override;
    virtual cGate *handlePacket(Packet *packet, cGate *inGate);
    virtual cGate *handleMessage(Message *request, cGate *inGate);

  public:
#ifdef INET_WITH_QUEUEING
    virtual bool supportsPacketSending(cGate *gate) const override { return true; }
    virtual bool supportsPacketPushing(cGate *gate) const override { return true; }
    virtual bool supportsPacketPulling(cGate *gate) const override { return false; }
    virtual bool supportsPacketPassing(cGate *gate) const override { return true; }
    virtual bool supportsPacketStreaming(cGate *gate) const override { return false; }

    virtual IPassivePacketSink *getConsumer(cGate *gate) override { throw cRuntimeError("Invalid operation"); }

    virtual bool canPushSomePacket(cGate *gate) const override;
    virtual bool canPushPacket(Packet *packet, cGate *gate) const override;

    virtual void pushPacket(Packet *packet, cGate *gate) override;
    virtual void pushPacketStart(Packet *packet, cGate *gate, bps datarate) override;
    virtual void pushPacketEnd(Packet *packet, cGate *gate) override;
    virtual void pushPacketProgress(Packet *packet, cGate *gate, bps datarate, b position, b extraProcessableLength = b(0)) override { throw cRuntimeError("Invalid operation"); }

    virtual void handleCanPushPacketChanged(cGate *gate) override;
    virtual void handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful) override;
#endif // #ifdef INET_WITH_QUEUEING

    virtual void handleRegisterInterface(const NetworkInterface& interface, cGate *out, cGate *in) override;

    virtual void handleRegisterService(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;
    virtual void handleRegisterAnyService(cGate *gate, ServicePrimitive servicePrimitive) override;

    virtual void handleRegisterProtocol(const Protocol& protocol, cGate *gate, ServicePrimitive servicePrimitive) override;
    virtual void handleRegisterAnyProtocol(cGate *gate, ServicePrimitive servicePrimitive) override;
};

std::ostream& operator<<(std::ostream& out, const MessageDispatcher::Key& foo) {
    out << "[" << foo.protocolId << ", " << omnetpp::cEnum::get("inet::ServicePrimitive")->getStringFor(foo.servicePrimitive) << "]";
    return out;
}

} // namespace inet

#endif


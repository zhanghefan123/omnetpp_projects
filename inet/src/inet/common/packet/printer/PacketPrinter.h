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

#ifndef __INET_PACKETPRINTER_H
#define __INET_PACKETPRINTER_H

#include "inet/common/StringFormat.h"
#include "inet/common/packet/dissector/PacketDissector.h"
#include "inet/common/packet/printer/ProtocolPrinter.h"

#ifdef INET_WITH_PHYSICALLAYERWIRELESSCOMMON
#include "inet/physicallayer/common/Signal.h"
#endif // INET_WITH_PHYSICALLAYERWIRELESSCOMMON

namespace inet {

class INET_API PacketPrinter : public cMessagePrinter
{
  protected:
    class INET_API Context {
      public:
        int infoLevel = -1;
        bool isCorrect = true;
        std::stringstream sourceColumn;
        std::stringstream destinationColumn;
        std::stringstream protocolColumn;
        std::stringstream lengthColumn;
        std::stringstream typeColumn;
        std::stringstream infoColumn;
    };

    class DirectiveResolver : public StringFormat::IDirectiveResolver {
      protected:
        const Context& context;
        const int numPacket;

      public:
        DirectiveResolver(const Context& context, const int numPacket) : context(context), numPacket(numPacket) {}

        virtual const char *resolveDirective(char directive) const override;
    };

  protected:
    mutable int numPacket = 0;

  protected:
    virtual bool isEnabledOption(const Options *options, const char *name) const;
    virtual bool isEnabledInfo(const Options *options, const Protocol *protocol) const;
    virtual const ProtocolPrinter& getProtocolPrinter(const Protocol *protocol) const;
    virtual void printContext(std::ostream& stream, const Options *options, Context& context) const;
#ifdef INET_WITH_PHYSICALLAYERWIRELESSCOMMON
    virtual void printSignal(physicallayer::Signal *signal, const Options *options, Context& context) const;
#endif // INET_WITH_PHYSICALLAYERWIRELESSCOMMON
    virtual void printPacket(Packet *packet, const Options *options, Context& context) const;
    virtual void printPacketInsideOut(const Ptr<const PacketDissector::ProtocolDataUnit>& protocolDataUnit, const Options *options, Context& context) const;
    virtual void printPacketLeftToRight(const Ptr<const PacketDissector::ProtocolDataUnit>& protocolDataUnit, const Options *options, Context& context) const;
    virtual void printSourceColumn(const std::string source, const Protocol *protocol, const Options *options, Context& context) const;
    virtual void printDestinationColumn(const std::string destination, const Protocol *protocol, const Options *options, Context& context) const;
    virtual void printProtocolColumn(const Protocol *protocol, const Options *options, Context& context) const;
    virtual void printLengthColumn(const Ptr<const PacketDissector::ProtocolDataUnit>& protocolDataUnit, const Options *options, Context& context) const;

  public:
    virtual int getScoreFor(cMessage *msg) const override;

    virtual std::set<std::string> getSupportedTags() const override;
    virtual std::set<std::string> getDefaultEnabledTags() const override;
    virtual std::vector<std::string> getColumnNames(const Options *options) const override;

    virtual void printMessage(std::ostream& stream, cMessage *message) const;
    virtual void printMessage(std::ostream& stream, cMessage *message, const Options *options) const override;

#ifdef INET_WITH_PHYSICALLAYERWIRELESSCOMMON
    virtual void printSignal(std::ostream& stream, physicallayer::Signal *signal) const;
    virtual void printSignal(std::ostream& stream, physicallayer::Signal *signal, const Options *options) const;
#endif // INET_WITH_PHYSICALLAYERWIRELESSCOMMON

    virtual void printPacket(std::ostream& stream, Packet *packet, const char *format = nullptr) const;
    virtual void printPacket(std::ostream& stream, Packet *packet, const Options *options, const char *format = nullptr) const;

    virtual std::string printPacketToString(Packet *packet, const char *format = nullptr) const;
    virtual std::string printPacketToString(Packet *packet, const Options *options, const char *format = nullptr) const;
};

} // namespace

#endif


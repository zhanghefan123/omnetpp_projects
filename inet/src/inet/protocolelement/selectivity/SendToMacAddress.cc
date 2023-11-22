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

#include "inet/protocolelement/selectivity/SendToMacAddress.h"

#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/ModuleAccess.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/protocolelement/common/AccessoryProtocol.h"
#include "inet/protocolelement/selectivity/DestinationMacAddressHeader_m.h"

namespace inet {

Define_Module(SendToMacAddress);

void SendToMacAddress::initialize(int stage)
{
    PacketFlowBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        const char *addressAsString = par("address");
        if (strlen(addressAsString) != 0)
            address = MacAddress(addressAsString);
        registerService(AccessoryProtocol::destinationMacAddress, inputGate, nullptr);
        registerProtocol(AccessoryProtocol::destinationMacAddress, outputGate, nullptr);
    }
}

void SendToMacAddress::pushPacket(Packet *packet, cGate *inGate)
{
    Enter_Method("pushPacket");
    take(packet);
    handleMessage(packet);
}

void SendToMacAddress::handleCanPushPacketChanged(cGate *outGate)
{
    producer->handleCanPushPacketChanged(inputGate->getPathStartGate());
}

void SendToMacAddress::processPacket(Packet *packet)
{
    const auto& macAddressReq = packet->findTag<MacAddressReq>();
    auto destinationAddress = macAddressReq != nullptr ? macAddressReq->getDestAddress() : address;
    auto header = makeShared<DestinationMacAddressHeader>();
    header->setDestinationAddress(destinationAddress);
    packet->insertAtFront(header);
    packet->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&AccessoryProtocol::destinationMacAddress);
}

void SendToMacAddress::handlePushPacketProcessed(Packet *packet, cGate *gate, bool successful)
{
    producer->handlePushPacketProcessed(packet, gate, successful);
}

} // namespace inet


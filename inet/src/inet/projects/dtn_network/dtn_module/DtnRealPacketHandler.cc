#include "inet/projects/dtn_network/dtn_module/DtnRealPacketHandler.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
#include "inet/networklayer/common/InterfaceTable.h"
namespace inet{
    DtnRealPacketHandler::DtnRealPacketHandler(cSimpleModule* containingModule) {
        this->containingModule = containingModule;
    }

    void DtnRealPacketHandler::processPacket(Packet * packet, DtnNeighbor* dtnNeighbor) {
        dtn* dtn_module = dynamic_cast<dtn*>(this->containingModule);
        auto * ift = dynamic_cast<InterfaceTable*>(this->containingModule->getParentModule()->getSubmodule("interfaceTable"));
        // get neighborAck
        auto epidemicHeader = packet->peekAtFront<EpidemicHeader>();
        // get the packet id
        std::string packetId = epidemicHeader->getUuid();
        // judge the key
        if(dtn_module->packets_buffer.count(packetId) > 0)
        {
            delete packet;
        } else {
            // store the packet in on buffer
            dtn_module->packets_buffer[packetId] = std::make_pair(packet, simTime());
            dtn_module->packetIds.insert(packetId);// store the packet id in dtn -- used for later swap
            // get the destination address of the packet
            Ipv4Address destAddr = epidemicHeader->getDestAddr();
            if(ift->isLocalAddress(destAddr)){
                // get the time of the packet
                double packetTime = epidemicHeader->getStartTime()->getTime();
                double timeElapsed = simTime().dbl() - packetTime;
                std::string output_str = "packet " + packetId + " reach final destination in " + std::to_string(timeElapsed) + " s";
                std::cout << module_log(dtn_module, output_str) << std::endl;
                // update the time
                dtn_module->total_packet_received += 1;
                dtn_module->total_packet_delay += timeElapsed;
                std::cout << "total packet received: "  <<  std::to_string(dtn_module->total_packet_received) << std::endl;
            }
            // resolve the request
            dtnNeighbor->requestIds.erase(packetId);
        }
        std::string output_str = "received dtn real packet id: " + packetId;
        std::cout << module_log(dtn_module, output_str) << std::endl;
    }
}

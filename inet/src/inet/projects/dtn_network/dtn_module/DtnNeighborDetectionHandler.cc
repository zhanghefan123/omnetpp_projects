#include "inet/projects/dtn_network/dtn_module/DtnNeighborDetectionHandler.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
#include "inet/projects/dtn_network/tools/tools.h"
namespace inet{
    DtnNeighborDetectionHandler::DtnNeighborDetectionHandler(cSimpleModule* containingModule) {
        this->containingModule = containingModule;
    }

    void DtnNeighborDetectionHandler::processPacket(Packet * packet, DtnNeighbor* dtnNeighbor) {
        // get header
        auto epidemicHeader = packet->peekAtFront<EpidemicHeader>();
        // get neighbor ack to judge if neighbor ack me or not
        bool neighborAck = epidemicHeader->getNeighborAck();
        // get ipv4 address
        Ipv4Address sourceAddr = packet->getTag<L3AddressInd>()->getSrcAddress().toIpv4();
        // get node name
        std::string node_name = this->containingModule->getParentModule()->getName();
        // set neighbor ip address
        dtnNeighbor->neighborAddress = sourceAddr;
        // update neighbor's last seen time
        dtnNeighbor->lastSeenTime = simTime();
        // then we gonna let neighbor process event
        if(neighborAck && (dtnNeighbor->state->getState() != DtnNeighbor::NEIGHBOR_TWO_WAY_STATE)){
            // change the state to the two way state, because we both know each other
            dtnNeighbor->processEvent(DtnNeighbor::NEIGHBOR_DETECT_PACKET_TWO_WAY_RECEIVED);
            dtnNeighbor->processEvent(DtnNeighbor::NEIGHBOR_START_EXCHANGE_MSG);
        } else if(neighborAck && (dtnNeighbor->state->getState() == DtnNeighbor::NEIGHBOR_TWO_WAY_STATE)) {
            // do nothing
        } else {
            dtnNeighbor->processEvent(DtnNeighbor::NEIGHBOR_DETECT_PACKET_RECEIVED);
        }
        // we gonna print we received a packet
        std::string output_str = "received dtn neighbor detection packet from neighbor " + sourceAddr.str();
        std::cout << module_log(this->containingModule, output_str) << std::endl;
        // we need to delete the packet finally
        delete packet;
    }
}

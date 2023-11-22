#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateUp.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateDown.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateTwoWay.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
namespace inet{
    void DtnNeighborStateUp::processEvent(inet::DtnNeighbor *neighbor, DtnNeighbor::DtnNeighborEventType event) {
        switch (event) {
            // within any state, we should send neighbor detect packet
            // 1. send neighbor detect packet
            // 2. restart timer dtn neighbor detect timer
            case DtnNeighbor::NEIGHBOR_DETECT_TIMER_RECEIVED:
            {
                EV_INFO << "NEIGHBOR_DETECT_TIMER" << std::endl;
                neighbor->sendNeighborDetectPacket(Ipv4Address::DTN_NEIGHBOR_DETECTION_MCAST, 1);
                // restart the timer to send neighbor detect packet
                dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                dtn_module->messageHandler->startTimer(neighbor->neighborDetectTimer, neighbor->neighbor_detection_interval);
                break;
            }
            // within any state, we should check if neighbor expire
            // 1. check if neighbor expire
            // 2. restart dtn neighbor expire timer
            case DtnNeighbor::NEIGHBOR_EXPIRE_TIMER_RECEIVED:
            {
                EV_INFO << "NEIGHBOR_EXPIRE_TIMER" << std::endl;
                // if expire, change the state to down
                if(((simTime())-neighbor->lastSeenTime) > neighbor->neighbor_expiration_time){
                    // change the neighbor state from up to down, set neighor ack = false
                    std::cout << "(expired) time period since last seen: " << (simTime()) - neighbor->lastSeenTime << " s" << std::endl;
                    // neighbor->neighborAck = false;
                    this->changeState(neighbor, new DtnNeighborStateDown(), this);
                    dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                    dtn_module->messageHandler->startTimer(neighbor->neighborExpireTimer, neighbor->check_neighbor_expiration_interval);
                }
                // if not expire, restart the timer to send neighbor expire check timer
                else {
                    std::string output_str = "(not expired) time period since last seen: " +
                            std::string(((simTime()) - neighbor->lastSeenTime).str()) + " s";
                    std::cout << module_log(neighbor->dtn_module,output_str) << std::endl;
                    // restart the timer to send neighbor expire check timer
                    dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                    dtn_module->messageHandler->startTimer(neighbor->neighborExpireTimer, neighbor->check_neighbor_expiration_interval);
                }
                break;
            }
            // if receive neighbor detect packet
            case DtnNeighbor::NEIGHBOR_DETECT_PACKET_RECEIVED:
            {
                // do nothing
                break;
            }
            // if receive neighbor detect packet two way
            case DtnNeighbor::NEIGHBOR_DETECT_PACKET_TWO_WAY_RECEIVED:
            {
                this->changeState(neighbor, new DtnNeighborStateTwoWay(), this);
                break;
            }
            default:
                break;
        }
    }
}

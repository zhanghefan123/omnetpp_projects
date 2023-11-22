#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateDown.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateUp.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
#include <iostream>
namespace inet{
    void DtnNeighborStateDown::processEvent(inet::DtnNeighbor *neighbor, DtnNeighbor::DtnNeighborEventType event) {
        switch (event) {
            // INTERFACE_UP means we should send packet from this interface
            case DtnNeighbor::DTN_INTERFACE_UP:
            {
                // get the dtn_module
                dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                // schedule neighbor detect timer
                dtn_module->messageHandler->startTimer(neighbor->neighborDetectTimer, neighbor->neighbor_detection_interval);
                // schedule neighbor expire timer
                dtn_module->messageHandler->startTimer(neighbor->neighborExpireTimer, neighbor->check_neighbor_expiration_interval);
                break;
            }
            // within any state, we should send neighbor detect packet
            // 1. send neighbor detect packet
            // 2. restart timer dtn neighbor detect timer
            case DtnNeighbor::NEIGHBOR_DETECT_TIMER_RECEIVED:
            {
                EV_INFO << "NEIGHBOR_DETECT_TIMER" << std::endl;
                neighbor->sendNeighborDetectPacket(Ipv4Address::DTN_NEIGHBOR_DETECTION_MCAST, 1);
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
                // if expired then change state to down
                if(((simTime())-neighbor->lastSeenTime) > neighbor->neighbor_expiration_time){
                    std::cout << "(expired) time period since last seen: " << (simTime()) - neighbor->lastSeenTime << " s" << std::endl;
                    // change the neighbor state from up to down
                    this->changeState(neighbor, new DtnNeighborStateDown(), this);
                    // get the containing module as the dtn module
                    dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                    // restart the check neighbor expiration timer
                    dtn_module->messageHandler->startTimer(neighbor->neighborExpireTimer, neighbor->check_neighbor_expiration_interval);
                }
                // if not expired, then restart the timer
                else {
                    std::string output_str = "(not expired) time period since last seen: " +
                                             std::string(((simTime()) - neighbor->lastSeenTime).str()) + " s";
                    std::cout << module_log(neighbor->dtn_module,output_str) << std::endl;
                    // restart the timer to send neighbor expire check timer
                    dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                    // restart the check neighbor expiration timer
                    dtn_module->messageHandler->startTimer(neighbor->neighborExpireTimer, neighbor->check_neighbor_expiration_interval);
                }
                break;
            }
            // if received neighbor detect packet, then change state to up
            case DtnNeighbor::NEIGHBOR_DETECT_PACKET_RECEIVED:
            {
                // one-way neighbor detection (I acknowledge you, but you don't acknowledge me)
                this->changeState(neighbor, new DtnNeighborStateUp(), this);
                // setting the neighborAck = true to indicate that the neighbor has been acknowledged
                // neighbor->neighborAck = true;
                break;
            }
            default:
                break;
        }
    }
}
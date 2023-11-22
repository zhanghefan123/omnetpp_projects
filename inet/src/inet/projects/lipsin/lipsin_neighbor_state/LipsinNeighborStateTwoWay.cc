#include "LipsinNeighborStateTwoWay.h"
#include "LipsinNeighborStateDown.h"
#include "LipsinNeighborStateOneWay.h"
#include "inet/projects/lipsin/lipsin_neighbor/LipsinNeighbor.h"
#include <omnetpp.h>
namespace inet{
    void LipsinNeighborStateTwoWay::processEvent(LipsinNeighbor* lipsinNeighbor, LipsinNeighborEventType event) {
        if(event == LipsinNeighborState::LipsinNeighborEventType::ROUTER_DEAD_TIMER_EXPIRED){
            lipsinNeighbor->changeState(new LipsinNeighborStateDown(), this);
        } else if(event == LipsinNeighborState::LipsinNeighborEventType::HELLO_WITHOUT_MY_ID_RECEIVED){
            lipsinNeighbor->changeState(new LipsinNeighborStateOneWay(), this);
        } else if(event == LipsinNeighborState::LipsinNeighborEventType::HELLO_WITH_MY_ID_RECEIVED){
            // remain the state
        } else {
            throw omnetpp::cRuntimeError("LipsinNeighborStateTwoWay::processEvent: Unrecognized event"); // NOLINT
        }
    }
}
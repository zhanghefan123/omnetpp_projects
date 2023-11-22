#include "LipsinNeighborStateDown.h"
#include "LipsinNeighborStateOneWay.h"
#include <omnetpp.h>
#include "inet/projects/lipsin/lipsin_neighbor/LipsinNeighbor.h"
namespace inet{
    void LipsinNeighborStateDown::processEvent(LipsinNeighbor* lipsinNeighbor, LipsinNeighborEventType event){
        // if the event is the HELLO message, then the state will change to the one way state
        if(event == LipsinNeighborState::LipsinNeighborEventType::HELLO_WITHOUT_MY_ID_RECEIVED){
            // change the neighbor state to one way state
            lipsinNeighbor->changeState(new LipsinNeighborStateOneWay(), this);
        } else if(event == LipsinNeighborState::LipsinNeighborEventType::ROUTER_DEAD_TIMER_EXPIRED){
            // remain the state
        } else {
            throw omnetpp::cRuntimeError("LipsinNeighborStateDown::processEvent: Unrecognized event"); // NOLINT
        }
    }
}
#include "LipsinNeighborStateOneWay.h"
#include "LipsinNeighborStateDown.h"
#include "LipsinNeighborStateTwoWay.h"
#include "inet/projects/lipsin/lipsin_neighbor/LipsinNeighbor.h"
namespace inet{
    void LipsinNeighborStateOneWay::processEvent(LipsinNeighbor* lipsinNeighbor, LipsinNeighborEventType event) {
        if(event == LipsinNeighborState::LipsinNeighborEventType::ROUTER_DEAD_TIMER_EXPIRED){
            lipsinNeighbor->changeState(new LipsinNeighborStateDown(), this);
        } else if(event == LipsinNeighborState::LipsinNeighborEventType::HELLO_WITHOUT_MY_ID_RECEIVED){
            // remain the state
        }
        else if(event == LipsinNeighborState::LipsinNeighborEventType::HELLO_WITH_MY_ID_RECEIVED){
            lipsinNeighbor->changeState(new LipsinNeighborStateTwoWay(), this);
        }
    }
}
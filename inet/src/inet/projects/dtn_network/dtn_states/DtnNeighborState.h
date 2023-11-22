#ifndef __INET_DTN_NEIGHBOR_STATE_H
#define __INET_DTN_NEIGHBOR_STATE_H
#include "inet/projects/dtn_network/dtn_neighbors/DtnNeighbor.h"
#include "inet/projects/dtn_network/tools/tools.h"
namespace inet{
    // The state of neighbor
    class DtnNeighborState{
    public:
        // change the neighbor state from current state to new state
        void changeState(DtnNeighbor* neighbor, DtnNeighborState *newState, DtnNeighborState *currentState);
        virtual ~DtnNeighborState() = default;
        // let neighbor process some event
        virtual void processEvent(DtnNeighbor *neighbor, DtnNeighbor::DtnNeighborEventType event) = 0;
        // get the curret state of the neighbor
        virtual DtnNeighbor::DtnNeighborStateType getState() const = 0;
    };
}
#endif

#ifndef INET_LIPSIN_NEIGHBOR_STATE_ONE_WAY_H
#define INET_LIPSIN_NEIGHBOR_STATE_ONE_WAY_H
#include "LipsinNeighborState.h"
namespace inet{
    class LipsinNeighborStateOneWay : public LipsinNeighborState{
        public:
            LipsinNeighborStateType getState() override {return LipsinNeighborStateType::NEIGHBOR_ONE_WAY_STATE;}
            /**
             * @brief pass the neighbor and event into the state, and state perform the corresponding operation
             * 
             * @param lipsinNeighbor 
             * @param event 
             */
            void processEvent(LipsinNeighbor* lipsinNeighbor, LipsinNeighborEventType event) override;
    };
}
#endif
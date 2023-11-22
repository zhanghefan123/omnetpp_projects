#ifndef INET_LIPSIN_NEIGHBOR_STATE_TWO_WAY_H
#define INET_LIPSIN_NEIGHBOR_STATE_TWO_WAY_H
#include "LipsinNeighborState.h"
namespace inet{
    class LipsinNeighborStateTwoWay : public LipsinNeighborState{
        public:
            LipsinNeighborStateType getState() override {return LipsinNeighborStateType::NEIGHBOR_TWO_WAY_STATE;}

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
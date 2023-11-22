#ifndef INET_LIPSIN_NEIGHBOR_STATE_DOWN_H
#define INET_LIPSIN_NEIGHBOR_STATE_DOWN_H
#include "LipsinNeighborState.h"
namespace inet{
    class LipsinNeighborStateDown : public LipsinNeighborState{
        public:
            LipsinNeighborStateType getState() override {return LipsinNeighborStateType::NEIGHBOR_DOWN_STATE;}
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
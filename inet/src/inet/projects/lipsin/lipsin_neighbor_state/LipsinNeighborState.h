#ifndef INET_LIPSIN_NEIGHBOR_STATE_H
#define INET_LIPSIN_NEIGHBOR_STATE_H
namespace inet{
    class LipsinNeighbor;
    class LipsinNeighborState{
        public:
            enum class LipsinNeighborStateType{
                NEIGHBOR_DOWN_STATE = 0,
                NEIGHBOR_ONE_WAY_STATE = 1,
                NEIGHBOR_TWO_WAY_STATE = 2,
            };
            // define the event type
            enum class LipsinNeighborEventType{
                ROUTER_DEAD_TIMER_EXPIRED, // 4 * HELLO_INTERVAL
                HELLO_WITHOUT_MY_ID_RECEIVED, // receive hello packet without my id
                HELLO_WITH_MY_ID_RECEIVED, // receive hello packet with my id
            };
        public:
            LipsinNeighborState() = default;
            virtual ~LipsinNeighborState() = default;
            virtual LipsinNeighborStateType getState() = 0;
            virtual void processEvent(LipsinNeighbor* lipsinNeighbor, LipsinNeighborEventType event) = 0;
    };
}
#endif
#ifndef INET_LIPSIN_NEIGHBOR_H
#define INET_LIPSIN_NEIGHBOR_H
#include "inet/projects/lipsin/lipsin_neighbor_state/LipsinNeighborState.h"
#include <string>
#include <omnetpp.h>
using namespace omnetpp;
namespace inet{
    class Packet;
    class LipsinNeighborState;
    class LipsinNeighborStateDown;
    class LipsinForwarder;
    class LinkInfo;
    class LipsinNeighbor{
        public:
            int neighborSatelliteId = -1;
            LinkInfo* correspondingLinkInfo = nullptr;
            cModule* containingModule = nullptr;
            LipsinForwarder* lipsinForwarder = nullptr;
            double lastTimeReceivedHelloPacket = 0;
            double helloInterval;
        public:
            // the current state
            LipsinNeighborState* state;
            // the previous state
            LipsinNeighborState* previousState;
        public:
            static std::string getStateString(LipsinNeighborState::LipsinNeighborStateType state) ; // used to convert state to string
        public:
            // check if the neighbor reached router dead interval
            void checkNeighborReachedRouterDeadInterval();
            // constructor
            explicit LipsinNeighbor(LinkInfo* correspondingLinkInfo, cModule* containingModule, double helloInterval);
            // destructor
            virtual ~LipsinNeighbor();
            // processEvent
            void processEvent(LipsinNeighborState::LipsinNeighborEventType event);
            // change state
            void changeState(LipsinNeighborState *newState, LipsinNeighborState *currentState);
            // send hello packets
            Packet* generateHelloPacket() const;
    };
}
#endif

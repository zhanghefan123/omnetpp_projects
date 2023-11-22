#include <sstream>
#include "LipsinNeighbor.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/projects/lipsin/lipsin_packets/LipsinHeader_m.h"
#include "inet/projects/lipsin/const_vars/LipsinConstVar.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/projects/lipsin/lipsin_forwarder/LipsinForwarder.h"
#include "inet/projects/lipsin/lipsin_neighbor_state/LipsinNeighborStateDown.h"
namespace inet{

    /**
     * @brief process event and change state
     * @param event the event type
     */
    void LipsinNeighbor::processEvent(LipsinNeighborState::LipsinNeighborEventType event){
        // when state is processing the event, the change state function will be called
        this->state->processEvent(this, event);
    }

    LipsinNeighbor::LipsinNeighbor(LinkInfo* correspondingLinkInfo,
                                   cModule* containingModule,
                                   double helloInterval){
        state = new LipsinNeighborStateDown();
        previousState = nullptr;
        this->correspondingLinkInfo = correspondingLinkInfo;
        this->containingModule = containingModule;
        this->helloInterval = helloInterval;
        this->lipsinForwarder = dynamic_cast<LipsinForwarder*>(containingModule->getSubmodule("lipsinNetworkLayer")->getSubmodule("forwarder"));
    }

    void LipsinNeighbor::changeState(LipsinNeighborState *newState, LipsinNeighborState *currentState){
        std::stringstream ss;
        ss << "LipsinNeighbor::changeState: " << correspondingLinkInfo->getNetworkInterface()->getFullName()
        << " change state from " << getStateString(currentState->getState()) << " to "
        << getStateString(newState->getState());
        // we can analyze the state change and do something here
        // --------------------------------------------------------------------
        std::vector<Packet*> generatedLsaPackets;
        if(newState->getState() == LipsinNeighborState::LipsinNeighborStateType::NEIGHBOR_DOWN_STATE){
            // we need to set the neighbor satellite id to -1
            this->neighborSatelliteId = -1;
            // this means when the constellation is just created, the connection is assumed up, and don't need to flood lsas.
            if(simTime().dbl() > 3 * this->helloInterval){
                // we need to generate the lsa packets link down
                generatedLsaPackets = this->lipsinForwarder->generateLsaPackets(this->correspondingLinkInfo->getNetworkInterface());
                std::cout << "generate lsa packets when interface down" << std::endl;
            }
        } else if(newState->getState() == LipsinNeighborState::LipsinNeighborStateType::NEIGHBOR_TWO_WAY_STATE){
            // this means when the constellation is just created, the connection is assumed up, and don't need to flood lsas.
            if(simTime().dbl() > 3 * this->helloInterval){
                // we need to generate the lsa packets with link up
                generatedLsaPackets = this->lipsinForwarder->generateLsaPackets(this->correspondingLinkInfo->getNetworkInterface());
                std::cout << "generated lsa packets when interface up" << std::endl;
            }
        }
        for(auto lsaPacket : generatedLsaPackets){
            this->lipsinForwarder->send(lsaPacket, "queueOut");
        }
        // --------------------------------------------------------------------
        if(previousState != nullptr){ // NOLINT
            delete previousState;
        }
        state = newState;
        previousState = currentState;
    }

    std::string LipsinNeighbor::getStateString(LipsinNeighborState::LipsinNeighborStateType state){
        switch(state){
            case LipsinNeighborState::LipsinNeighborStateType::NEIGHBOR_DOWN_STATE:
                return "NEIGHBOR_DOWN_STATE";
            case LipsinNeighborState::LipsinNeighborStateType::NEIGHBOR_ONE_WAY_STATE:
                return "NEIGHBOR_ONE_WAY_STATE";
            case LipsinNeighborState::LipsinNeighborStateType::NEIGHBOR_TWO_WAY_STATE:
                return "NEIGHBOR_TWO_WAY_STATE";
            default:
                return "UNKNOWN_STATE";
        }
    }

    /**
     * @brief Destroy the Lipsin Neighbor:: Lipsin Neighbor object
     */
    LipsinNeighbor::~LipsinNeighbor(){
        if(this->state != nullptr){ // NOLINT
            delete this->state;
        }
        if(this->previousState != nullptr){ // NOLINT
            delete this->previousState;
        }
    }

    void LipsinNeighbor::checkNeighborReachedRouterDeadInterval() {
        double timeElapsed = simTime().dbl() - lastTimeReceivedHelloPacket;
        // the routerDeadInterval equals to 4 times helloInterval
        double routerDeadInterval = this->helloInterval * 4;
        if(timeElapsed >= routerDeadInterval){
            // change state to down
            this->processEvent(LipsinNeighborState::LipsinNeighborEventType::ROUTER_DEAD_TIMER_EXPIRED);
        }
    }

    Packet* LipsinNeighbor::generateHelloPacket() const {
        auto* newHelloPacket = new Packet(LipsinConstVar::LIPSIN_HELLO_PACKET_NAME.c_str());

        // ------------------ add tag for hello packet ------------------
        newHelloPacket->addTagIfAbsent<InterfaceReq>()->setInterfaceId(this->correspondingLinkInfo->getNetworkInterface()->getInterfaceId());
        newHelloPacket->addTagIfAbsent<MacAddressReq>()->setDestAddress(MacAddress::BROADCAST_ADDRESS);
        newHelloPacket->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::lipsin_network);
        // ------------------ add tag for hello packet ------------------

        // ------------------ create lipsin header ------------------------
        const auto& lipsinHeader = makeShared<LipsinHeader>();
        lipsinHeader->setPacketType(LipsinConstVar::LIPSIN_HELLO_PACKET_TYPE);
        lipsinHeader->setUuid(LipsinTools::generate_uuid().c_str());
        lipsinHeader->setSource(this->containingModule->getFullName());
        lipsinHeader->setNonce(LipsinTools::generate_nonce());
        lipsinHeader->setRealLidsBf(nullptr);
        lipsinHeader->setVirtualLidsBf(nullptr);
        lipsinHeader->setPathHeader(nullptr);
        lipsinHeader->setNeighborSatelliteId(this->neighborSatelliteId);
        // ------------------ create lipsin header ------------------------

        // ------------------ insert the header into the packet ------------------
        newHelloPacket->insertAtFront(lipsinHeader);
        // ------------------ insert the header into the packet ------------------

        // return the hello packet (lipsin forwarder will send the packet out)
        return newHelloPacket;
    }
}

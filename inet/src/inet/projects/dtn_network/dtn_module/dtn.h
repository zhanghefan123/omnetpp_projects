#ifndef __INET_DTN_H
#define __INET_DTN_H
#include "inet/projects/dtn_network/dtn_neighbors/DtnNeighbor.h"
#include "inet/projects/dtn_network/dtn_module/MessageHandler.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/OperationalBase.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/common/packet/Packet.h"
#include "inet/routing/base/RoutingProtocolBase.h"
#include <vector>
#include <map>
namespace inet{
class dtn : public OperationalBase, protected cListener {
public:
    // zhf add code - result section
    int total_packet_received = 0;
    double total_packet_delay = 0;
    std::string output_dir_path;

public:
    // zhf add code - self message kind
    enum SelfMsgKind {
        DTN_START_MSG_KIND = -1,
        CHECK_BUFFER_EXPIRED_MSG_KIND = -2,
    };

public:
    // zhf add code - messageHandler of dtn
    MessageHandler* messageHandler;

public:
    // zhf add code - the first timer
    cMessage* check_buffer_expired_timer;

public:
    // zhf add code : members
    cMessage* dtn_start_msg; // this new var will be deleted
    std::map<std::string, DtnNeighbor*> neighbor_map; // this new var will be deleted
    std::set<std::string> packetIds;
    std::map<std::string, std::pair<Packet*,simtime_t>> packets_buffer; // the key is uuid and the value is the packet

public:
    // zhf add code : paramters get from ned - used to initialize neighbors
    double neighbor_detection_interval; // neighbor detection packet will be send with this interval
    double neighbor_expiration_time; // if the neighbor is not detected for this time, then it will be expired
    double check_neighbor_expiration_interval; // we will check the neighbor expiration with this interval
    double buffer_expiration_time; // the packet in the buffer will be expired after this time
    double check_buffer_expiration_interval; // we will check the buffer expiration with this interval
    double neighbor_exchange_interval; // we will exchange the neighbor table with this interval
    double send_packet_interval; // we will send the packet with this interval, otherwise the packet will be sent immediately


public:
    dtn() = default;
    ~dtn() override;
    std::string getFullPath() const override { return cSimpleModule::getFullPath(); }
    static std::string generateUuid();
    void initializeNeighbors();
    void allNeighborsInterfaceUp();
    void allInterfacesJoinMulticastGroups();
    DtnNeighbor* findNeighborByInterfaceId(int interfaceId);
    void checkBufferExpired();
    virtual void finish() override;

protected:
    int numInitStages() const override {return NUM_INIT_STAGES; }
    void initialize(int stage) override;
    void handleMessageWhenUp(cMessage *) override;


public:
    // lifecycle method
    bool isInitializeStage(int stage) override { return stage == INITSTAGE_LINK_LAYER; }
    bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_LINK_LAYER; }
    bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_LINK_LAYER; }
    void handleStartOperation(LifecycleOperation *operation) override;
    void handleStopOperation(LifecycleOperation *operation) override;
    void handleCrashOperation(LifecycleOperation *operation) override;
};
}
#endif

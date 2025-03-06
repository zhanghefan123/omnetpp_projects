#ifndef INET_GLOBAL_MODULE_H
#define INET_GLOBAL_MODULE_H
#include <omnetpp.h>
#include "inet/common/InitStages.h" // for NUM_INIT_STAGES
using namespace omnetpp;
namespace inet{
    class GlobalModule : public cSimpleModule{
    public:
        int ddCount = 0;
        int lsuCount = 0;
        int lsrCount = 0;
        int lsaAck = 0;
        bool startFromQtEnv = false;
    public:
        void getQtOrCmd();
    private:
        std::string START_TO_FAIL_PAR_NAME = "start_to_fail";
        double start_to_fail;
        double ospf_consumption = 0;
        double routing_table_rebuild_time;
        double final_not_hello_packet_time;
    protected:
        void initialize(int stage) override;
        int numInitStages() const override {return NUM_INIT_STAGES;}
    public:
        void update_final_not_hello_packet_time();
        void update_routing_table_rebuild_time();
        void update_ospf_consumption_in_bytes(double packet_size);
        void output_result();
        void finish() override;
        int get_start_to_fail() const {return start_to_fail;}
    };
}
#endif

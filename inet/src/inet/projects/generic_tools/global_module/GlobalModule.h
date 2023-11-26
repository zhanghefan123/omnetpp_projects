#ifndef INET_GLOBAL_MODULE_H
#define INET_GLOBAL_MODULE_H
#include <omnetpp.h>
#include "inet/common/InitStages.h" // for NUM_INIT_STAGES
using namespace omnetpp;
namespace inet{
    class GlobalModule : public cSimpleModule{
    public:
        bool startFromQtEnv = false;
    public:
        void getQtOrCmd();
    protected:
        void initialize(int stage) override;
        int numInitStages() const override {return NUM_INIT_STAGES;}
    };
}
#endif
//
// Created by 张贺凡 on 2024/5/5.
//

#ifndef INET_PROJECTS_DELAYTOLERANTNETWORK_SRCONFIGLOADER_H
#define INET_PROJECTS_DELAYTOLERANTNETWORK_SRCONFIGLOADER_H
#include <omnetpp.h>
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"
#include "inet/projects/lipsin/lipsin_table/LipsinLinkTable.h"
#include "inet/networklayer/common/InterfaceTable.h"
using namespace omnetpp;
namespace inet{
    class SRConfigLoader : public cSimpleModule{
    private:
        // ------------ PARAMS ------------
        cXMLElement* allSRConfig;
        cModule* satelliteModule;
        int currentSatelliteId;
        // ------------ PARAMS ------------
        // ------------ TABLES ------------
        LinkInfoTable* linkInfoTable = nullptr;
        LipsinLinkTable* plt = nullptr;
        InterfaceTable* interfaceTable = nullptr;
        // ------------ TABLES ------------
    public:
        SRConfigLoader() = default;
        void loadAllSRConfig();
        void loadPhyInterfaceParameters(cXMLElement* link, int tagSatelliteId);
        int resolveSatelliteId();
        void resolveTables();
    protected:
        void initialize(int stage) override;
        int numInitStages() const override { return NUM_INIT_STAGES; }
    };
}
#endif //INET_PROJECTS_DELAYTOLERANTNETWORK_SRCONFIGLOADER_H

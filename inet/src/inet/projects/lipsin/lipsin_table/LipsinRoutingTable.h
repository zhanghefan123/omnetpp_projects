/*
 * LipsinRoutingTable.h
 *
 *  Created on: Sep 10, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LIPSINROUTINGTABLE_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LIPSINROUTINGTABLE_H_
#include <omnetpp.h>
#include <map>
#include <vector>
#include "inet/projects/lipsin/lipsin_table/LinkInfo.h"
using namespace omnetpp;
namespace inet {

class LipsinRoutingTable : public cSimpleModule {
private:
    std::map<int, std::vector<LinkInfo*>> destinationRoutesMap;
    std::map<std::string, std::vector<LinkInfo*>> sourceToDestinationRoutesMap;
public:
    void updateGlobalRoutingTable(const std::map<std::string, std::vector<LinkInfo*>>& newGlobalRoutingTable);
    void updateRoutingTable(const std::map<int, std::vector<LinkInfo*>>& newRoutingTable);
    std::vector<LinkInfo*> getRouteForUnicast(int nodeId);
    std::vector<LinkInfo*> getSourceRoutesByDestId(int nodeId);
    std::vector<LinkInfo*> getSourceRoutesByDestIds(const std::vector<int>& nodeIds);
    std::vector<LinkInfo*> getMulticastRoutesByDestIds(const std::vector<int>& nodeIds);
    void printSourceRoutingTable();
    void addWatches();
protected:
    void initialize(int stage) override;
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LIPSINROUTINGTABLE_H_ */

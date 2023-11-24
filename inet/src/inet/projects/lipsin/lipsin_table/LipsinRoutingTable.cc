/*
 * LipsinRoutingTable.cc
 *
 *  Created on: Sep 10, 2023
 *      Author: zhf
 */

#include "LipsinRoutingTable.h"
#include "inet/projects/lipsin/lipsin_operator_reload/LipsinOperatorReload.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
namespace inet {

    Define_Module(LipsinRoutingTable);

    void LipsinRoutingTable::initialize(int stage){
        if(stage == INITSTAGE_LOCAL){
            this->addWatches();
        } else if(stage == INITSTAGE_LAST){

        }
    }

    void LipsinRoutingTable::addWatches() {
        WATCH_MAP(this->destinationRoutesMap);
        WATCH_MAP(this->sourceToDestinationRoutesMap);
    }

    void LipsinRoutingTable::updateGlobalRoutingTable(
            const std::map<std::string, std::vector<LinkInfo *>> &newGlobalRoutingTable) {
        this->sourceToDestinationRoutesMap = newGlobalRoutingTable;
    }

    void LipsinRoutingTable::updateRoutingTable(const std::map<int, std::vector<LinkInfo *>>& newRoutingTable) {
        this->destinationRoutesMap = newRoutingTable;
    }

    std::vector<LinkInfo*> LipsinRoutingTable::getSourceRoutesByDestId(int nodeId) {
        std::string currentSatelliteName = this->getParentModule()->getFullName();
        int currentSatelliteId = LipsinTools::getSatelliteId(currentSatelliteName);
        std::string fromCurrentToNodeStr = std::to_string(currentSatelliteId) + "->" + std::to_string(nodeId);
        return this->sourceToDestinationRoutesMap[fromCurrentToNodeStr];
    }

    std::vector<LinkInfo*> LipsinRoutingTable::getRouteForUnicast(int nodeId){
        return this->destinationRoutesMap[nodeId];
    }

    std::vector<LinkInfo*> LipsinRoutingTable::getSourceRoutesByDestIds(const std::vector<int>& nodeIds) {
        std::vector<LinkInfo*> final_result;
        for(int nodeId : nodeIds){
            std::vector<LinkInfo*> routes = this->destinationRoutesMap[nodeId];
            final_result.insert(final_result.end(), routes.begin(), routes.end());
        }
        return final_result;
    }

    std::vector<LinkInfo*> LipsinRoutingTable::getMulticastRoutesByDestIds(const std::vector<int> &nodeIds) {
        std::vector<LinkInfo*> final_result;
        // first we need to create the [currentSatelliteId]->[firstNodeId] string
        int firstNodeId = nodeIds[0];
        std::string currentSatelliteName = this->getParentModule()->getFullName();
        int currentSatelliteId = LipsinTools::getSatelliteId(currentSatelliteName);
        std::string fromCurrentToFirstStr = std::to_string(currentSatelliteId) + "->" + std::to_string(firstNodeId);
        // second we need to get the first route
        std::vector<LinkInfo*> firstRoute = this->sourceToDestinationRoutesMap[fromCurrentToFirstStr];
        final_result.insert(final_result.end(),firstRoute.begin(),firstRoute.end());
        // third we need to create the [firstNode]->[other nodes] string
        for(int index = 1; index < nodeIds.size(); index++){
            std::string fromFirstToOther = std::to_string(firstNodeId) + "->" + std::to_string(nodeIds[index]);
            std::vector<LinkInfo*> otherRoute = this->sourceToDestinationRoutesMap[fromFirstToOther];
            final_result.insert(final_result.end(), otherRoute.begin(), otherRoute.end());
        }
        return final_result;
    }

    void LipsinRoutingTable::printSourceRoutingTable() {
        for(const auto& link: this->destinationRoutesMap){
            std::cout << "to destination satellite " << link.first << " route: " << std::endl;
            for(auto linkInfo : link.second){
                std::cout << "link id: " << linkInfo->getId()
                          << " link src: " << linkInfo->getSrc()
                          << " link dest: " << linkInfo->getDest()
                          << " link cost: " << linkInfo->getCost()
                          << std::endl;
            }
            std::cout << std::endl;
        }
    }
} /* namespace inet */

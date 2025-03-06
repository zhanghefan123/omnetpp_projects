/*
 * LipsinRoutingTable.cc
 *
 *  Created on: Sep 10, 2023
 *      Author: zhf
 */
#include <fstream>
#include <unistd.h>
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"
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

    void LipsinRoutingTable::updateGlobalRoutingTable(const std::map<std::string, std::vector<LinkInfo *>> &newGlobalRoutingTable) {
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

    int LipsinRoutingTable::findMaxLinkLength() {
        int maxLength = 0;
        for(const auto& item : this->destinationRoutesMap){
            int currentLength = int(item.second.size());
            if(currentLength > maxLength){
                maxLength = currentLength;
            }
        }
        return maxLength;
    }

    std::vector<LinkInfo*> LipsinRoutingTable::getSourceRoutesByDestIds(const std::vector<int>& nodeIds) {
        std::vector<LinkInfo*> final_result;
        for(int nodeId : nodeIds){
            std::vector<LinkInfo*> routes = this->destinationRoutesMap[nodeId];
            final_result.insert(final_result.end(), routes.begin(), routes.end());
        }
        return final_result;
    }

    std::vector<LinkInfo*> LipsinRoutingTable::getSPFMulticastRoutesByDestIds(const std::vector<int> &nodeIds) {
        std::vector<LinkInfo*> final_result;
        std::string currentSatelliteName = this->getParentModule()->getFullName();
        int currentSatelliteId = LipsinTools::getSatelliteId(currentSatelliteName);
        for(int index = 0; index < nodeIds.size(); index++){
            std::string fromSourceToOther = std::to_string(currentSatelliteId) + "->" + std::to_string(nodeIds[index]);
            std::vector<LinkInfo*> otherRoute = this->sourceToDestinationRoutesMap[fromSourceToOther];
            final_result.insert(final_result.end(), otherRoute.begin(), otherRoute.end());
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

    void LipsinRoutingTable::persist() {
        /**
         * @brief 将路由表持久化到文件之中
         */
        // 判断文件夹是否存在
        if(access("storage", 0) == -1){
            // 创建文件夹
            mkdir("storage", 0777);
        }
        std::stringstream ss;
        // 进行所有的链路的遍历
        for(const auto& item : this->destinationRoutesMap){
            ss << item.first << ",";
            for(const auto& linkInfo : item.second){
                ss << linkInfo->getId() << ",";
            }
            ss << std::endl;
        }
        // 构造文件名
        std::string fileName = std::string("storage/lipsin_routing_table_") + this->getParentModule()->getFullName() + ".txt";
        // 判断文件是否存在
        if(access(fileName.c_str(), 0) == -1){
            // 打开文件
            std::ofstream file;
            file.open(fileName, std::ios::out | std::ios::app);
            // 写入文件
            file.write(ss.str().c_str(), int(ss.str().length()));
            // 关闭文件
            file.close();
        }
    }

    int LipsinRoutingTable::load(){
        /**
         * @brief 从文件中加载路由表
         * @return 返回值,如果为0代表一切正常，如果为-1,代表错误,比如文件不存在
         */

        // 获取到LinkInfoTable
        auto* linkInfoTable = dynamic_cast<LinkInfoTable*>(this->getParentModule()->getSubmodule("linkInfoTable"));
        // 获取linkInfoTableById
        auto linkInfoTableById = linkInfoTable->getLinkInfoTableById();
        // 构造文件名
        std::string fileName = std::string("storage/lipsin_routing_table_") + this->getParentModule()->getFullName() + ".txt";
        // 判断文件是否存在
        if(access(fileName.c_str(), 0) == -1){
            // 文件不存在
            return -1;
        }
        // 打开文件
        std::ifstream file;
        // 读取文件
        file.open(fileName, std::ios::in);
        // 读取文件内容
        std::string line;
        while(std::getline(file, line)){
            // 将这一行按照 ',' 进行分割
            std::vector<std::string> lineSplit = LipsinTools::splitString(line, ',');
            // 链路序列的存储
            std::vector<LinkInfo*> linkSequence;
            // 获取目的卫星的 id
            int destSatelliteId = std::stoi(lineSplit[0]);
            // 获取路由信息
            for(int index = 1; index < lineSplit.size(); index++){
                // 获取链路 id
                int linkId = std::stoi(lineSplit[index]);
                // 获取链路信息
                LinkInfo* linkInfo = linkInfoTableById[linkId];
                // 将链路信息存储到链路序列中
                linkSequence.push_back(linkInfo);
            }
            // 将链路序列存储到路由表中
            this->destinationRoutesMap[destSatelliteId] = linkSequence;
        }
        // 关闭文件
        file.close();
        // 正常返回
        return 0;
    }
} /* namespace inet */

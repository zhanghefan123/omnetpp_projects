//
// Created by 张贺凡 on 2024/5/5.
//
#include "inet/projects/sr/sr_config_loader/SRConfigLoader.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/projects/lipsin/lipsin_table/LinkInfo.h"


namespace inet{
    Define_Module(SRConfigLoader);

    void SRConfigLoader::initialize(int stage){
        if(stage == INITSTAGE_ROUTING_PROTOCOLS){
            this->satelliteModule = this->getParentModule();
            this->allSRConfig = this->satelliteModule->par("srConfig");
            this->currentSatelliteId = this->resolveSatelliteId();
            this->resolveTables();
            this->loadAllSRConfig();
        }
    }

    int SRConfigLoader::resolveSatelliteId() {
        std::string routerName = this->satelliteModule->getFullName();   // get the containing modules's satellite name
        int satelliteId = std::stoi(routerName.substr(routerName.find("SAT")+3, 5));
        return satelliteId;
    }

    void SRConfigLoader::resolveTables() {
        // resolve interfaceTable
        this->interfaceTable = dynamic_cast<InterfaceTable*>(this->satelliteModule->getSubmodule("interfaceTable"));
        if(this->interfaceTable == nullptr){
            throw cRuntimeError("SRConfigLoader: interfaceTable is nullptr"); // NOLINT
        }
        // resolve linkInfoTable
        this->linkInfoTable = dynamic_cast<LinkInfoTable*>(this->satelliteModule->getSubmodule("linkInfoTable"));
        if(this->linkInfoTable == nullptr){
            throw cRuntimeError("SRConfigLoader: linkInfoTable is nullptr"); // NOLINT
        }
        // resolve plt
        this->plt = dynamic_cast<LipsinLinkTable*>(this->satelliteModule->getSubmodule("plt"));
        if(this->plt == nullptr){
            throw cRuntimeError("SRConfigLoader: plt is nullptr"); // NOLINT
        }
    }

    void SRConfigLoader::loadAllSRConfig() {
        if(std::strcmp(this->allSRConfig->getTagName(), "LinksConfig") != 0){
            throw cRuntimeError("SRConfigLoader::loadAllSRConfig: wrong xml tag name: %s",
                                this->allSRConfig->getTagName());
        } else {
            cXMLElementList routers = this->allSRConfig->getElementsByTagName("Router");              // 拿到所有的卫星节点对应的 xml
            for(auto& router: routers) {                                                        // 遍历所有的卫星节点对应的 xml
                std::string routerName = LipsinTools::getStrAttr(*router, "name");               // 拿到卫星的名称
                int tagSatelliteId = std::stoi(routerName.substr(routerName.find("SAT")+3, 5)); // 拿到卫星的id
                cXMLElementList links = router->getChildren();                                                 // 拿到卫星的链路
                for(auto &link: links){                                                         // 遍历卫星的链路
                    std::string nodeName = link->getTagName();                                                 // 拿到链路类型
                    if(nodeName == "PhysicalLink"){
                        // std::cout << "load physical link" << std::endl;
                        this->loadPhyInterfaceParameters(link, tagSatelliteId);                                // 处理物理链路类型
                    }
                }
            }
        }
    }

    void SRConfigLoader::loadPhyInterfaceParameters(cXMLElement* link, int tagSatelliteId){
        // ------------------------------------- 获取链路 xml tag 属性 -------------------------------------
        int srcId = LipsinTools::getIntAttr(*link, "srcId");                    // 源节点 id
        int destId = LipsinTools::getIntAttr(*link, "destId");                  // 目的节点 id
        int cost = LipsinTools::getIntAttr(*link, "cost");                      // 开销
        int linkId = LipsinTools::getIntAttr(*link, "linkId");                  // link id
        IslType islType = LipsinTools::getIslType(*link, "linkType");           // 链路类型: 可能是 inter-orbit 可能是 intra-orbit
        std::string interfaceName = LipsinTools::getStrAttr(*link, "ifName");   // 接口的名称
        // ------------------------------------- 获取链路 xml tag 属性 -------------------------------------
        // ---------------------------------------- 遍历链路寻找接口 ----------------------------------------
        NetworkInterface* correspondingInterfaceEntry = nullptr;
        bool isTheLinkOfCurrentSatellite = false;
        // std::cout << "tag satellite id: " << tagSatelliteId << " current satellite id: " << this->currentSatelliteId << std::endl;
        if(tagSatelliteId == this->currentSatelliteId){
            for(int index = 0; index < interfaceTable->getNumInterfaces(); index++){
                NetworkInterface* interfaceEntryTmp = interfaceTable->getInterface(index);
                if(interfaceEntryTmp->getInterfaceName() == interfaceName){
                    correspondingInterfaceEntry = interfaceEntryTmp;
                    isTheLinkOfCurrentSatellite = true;
                }
            }
        }
        // ---------------------------------------- 遍历链路寻找接口 ----------------------------------------
        if(isTheLinkOfCurrentSatellite){
            // -----------------------   创建链路对象(添加到 linkInfoTable & plt)   ----------------------------------------
            if(correspondingInterfaceEntry->isUp()){
                auto* linkInfo = new LinkInfo(srcId,destId,linkId,
                                              cost,LinkState::UP,islType,
                                              correspondingInterfaceEntry, LinkType::PHYSICAL);
                auto* linkInfoForPlt = new LinkInfo(*linkInfo);
                this->linkInfoTable->addLinkInfo(linkInfo);
                this->plt->addEntry(linkInfoForPlt);
            } else {
                auto* linkInfo = new LinkInfo(srcId,destId,linkId,
                                              cost,LinkState::DOWN,islType,
                                              correspondingInterfaceEntry, LinkType::PHYSICAL);
                auto* linkInfoForPlt = new LinkInfo(*linkInfo);
                this->linkInfoTable->addLinkInfo(linkInfo);
                this->plt->addEntry(linkInfoForPlt);
            }
            // ----------------------   创建链路对象(添加到 linkInfoTable & plt)   ----------------------------------------
        } else {
            auto* linkInfo = new LinkInfo(srcId,destId,linkId,
                                          cost,LinkState::UNKNOWN_STATE,
                                          islType,nullptr,
                                          LinkType::PHYSICAL);
            this->linkInfoTable->addLinkInfo(linkInfo);
        }
    }
}
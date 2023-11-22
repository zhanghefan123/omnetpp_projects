/*
 * LipsinRouteConfigurator.cc
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */
#include <vector>
#include "LipsinRouteConfigurator.h"
#include "inet/projects/lipsin/lipsin_tools/LipsinTools.h"
#include "inet/projects/lipsin/lipsin_table/LinkInfoTable.h"
#include "inet/projects/lipsin/lipsin_table/LipsinLinkTable.h"
#include "inet/networklayer/common/InterfaceTable.h"

namespace inet {

    Define_Module(LipsinRouteConfigurator);

    void LipsinRouteConfigurator::initialize(int stage){
        // there are so many stages, we only setting our parameters in the local stage
        if(stage == INITSTAGE_LOCAL){
            this->lipsinConfig = this->getParentModule()->par("lipsinConfig");
            this->lidIncrease = this->getParentModule()->par("lidIncrease");
            this->containingModule = this->getParentModule();
        } else if (stage == INITSTAGE_ROUTING_PROTOCOLS){
            // first we need to load linkInfoTable & nodeLinkTable & plt vlt dlt
            this->loadConfigFromXml(this->lipsinConfig);
        } else if (stage == INITSTAGE_LAST){
            this->addWatches();
        }
    }

    void LipsinRouteConfigurator::addWatches(){
        WATCH(this->lidIncrease);
    }

    /**
     * load configuration
     * @param linksConfig the xmldoc lipsinConfig.xml
     */
    void LipsinRouteConfigurator::loadConfigFromXml(cXMLElement *linksConfig) {
        // check the top element tag is "LinksConfig"
        if (strcmp(linksConfig->getTagName(), "LinksConfig") != 0) {
            throw cRuntimeError("LipsinRouteConfigurator::loadConfigFromXml: wrong xml tag name: %s", // NOLINT
                                linksConfig->getTagName());
        }
        // if the check passes
        else {
            // get the <Router> tags
            cXMLElementList routers = linksConfig->getElementsByTagName("Router");
            // traverse each <Router> tag
            for (auto &router: routers) {
                // get the routerName
                std::string routerName = LipsinTools::getStrAttr(*router, "name");
                // extract the satellite id
                int tagSatelliteId = std::stoi(routerName.substr(routerName.find("SAT")+3, 5));
                // get the tags inside the <Router> tag
                cXMLElementList links = router->getChildren();
                for (auto &link: links) {
                    // if the link is the real physical link then read it
                    std::string nodeName = link->getTagName();
                    if (nodeName == "PhysicalLink") {
                        // call load physical interface function
                        loadPhyInterfaceParameters(link, tagSatelliteId);
                    } else if (nodeName == "VirtualLink"){
                        // call load virtual interface function
                        loadVirInterfaceParameters(link, tagSatelliteId);
                    }
                }
            }
        }
    }

    /**
     * load virtual interface
     * @param link the link xml tag
     * @param tagSatelliteId this belongs to which satellite
     */
    void LipsinRouteConfigurator::loadVirInterfaceParameters(omnetpp::cXMLElement *link, int tagSatelliteId) {
        // get the current satellite name
        std::string routerName = this->containingModule->getFullName();

        // extract the current satellite id from the satellite name
        int satelliteId = std::stoi(routerName.substr(routerName.find("SAT")+3, 5));

        // get link info table
        // ------------------------------------------------------------------------------------------
        auto* linkInfoTable = dynamic_cast<LinkInfoTable*>(this->containingModule->getSubmodule("linkInfoTable"));
        if(linkInfoTable == nullptr){
            throw cRuntimeError("LipsinRouteConfigurator::loadPhyInterfaceParameters: linkInfoTable is nullptr"); // NOLINT
        }
        // ------------------------------------------------------------------------------------------

        // get the attributes (srcId, destId, cost, linkId, interfaceName)
        // ------------------------------------------------------------------------------------------
        int srcId = LipsinTools::getIntAttr(*link, "srcId");
        int destId = LipsinTools::getIntAttr(*link, "destId");
        int cost = LipsinTools::getIntAttr(*link, "cost");
        int linkId = LipsinTools::getIntAttr(*link, "linkId");
        linkId = linkId + this->lidIncrease;
        std::string interfaceName = LipsinTools::getStrAttr(*link, "ifName");
        // ------------------------------------------------------------------------------------------


        // traverse the interface table to find out the interface
        // -------------------------------------------------------------------------------------
        bool isCurrentSatelliteLink = false;
        NetworkInterface *interfaceEntry = nullptr;
        if(tagSatelliteId == satelliteId){
            isCurrentSatelliteLink = true;
            auto* interfaceTable = dynamic_cast<InterfaceTable*>(this->containingModule->getSubmodule("interfaceTable"));
            for(int i = 0; i < interfaceTable->getNumInterfaces(); i++){
                NetworkInterface* interfaceEntryTmp = interfaceTable->getInterface(i);
                if(interfaceEntryTmp->getInterfaceName() == interfaceName){
                    interfaceEntry = interfaceEntryTmp;
                }
            }
        }
        // -------------------------------------------------------------------------------------
        // if the interface is current satellite's interface
        if(isCurrentSatelliteLink){
            // get the virtual link table
            auto* vltCmodule = this->containingModule->getSubmodule("lipsinNetworkLayer")->getSubmodule("vlt");
            auto* virtualLinkTable = dynamic_cast<LipsinLinkTable*>(vltCmodule);
            // get the down link table
            auto* dltCmodule = this->containingModule->getSubmodule("lipsinNetworkLayer")->getSubmodule("dlt");
            auto* downLinkTable = dynamic_cast<LipsinLinkTable*>(dltCmodule);
            // if the interface is up
            if(interfaceEntry->isUp()){
                // create link info
                auto* linkInfo = new LinkInfo(srcId,destId,linkId,
                                              cost,LinkState::UP,IslType::UNKNOWN_TYPE,
                                              interfaceEntry, LinkType::VIRTUAL);
                // add the linkInfo into the virtual link table
               virtualLinkTable->addEntry(linkInfo);
            } else {
                // add the linkInfo into the virtual link table and down link table
                auto* linkInfo = new LinkInfo(srcId,destId,linkId,
                                              cost,LinkState::DOWN,IslType::UNKNOWN_TYPE,
                                              interfaceEntry, LinkType::VIRTUAL);
                virtualLinkTable->addEntry(linkInfo);
                auto *linkInfoForDown = new LinkInfo(srcId,destId,linkId,
                                                     cost,LinkState::DOWN,IslType::UNKNOWN_TYPE,
                                                     interfaceEntry, LinkType::VIRTUAL);
                downLinkTable->addEntry(linkInfoForDown);
            }
        }
    }

    /**
     * load physical interface (the physical interfaces are corresponding to each single direction link identifiers)
     * @param link the current link tag
     * @param tagSatelliteId this link belongs to tagSatelliteId
     */
    void LipsinRouteConfigurator::loadPhyInterfaceParameters(cXMLElement *link, int tagSatelliteId) {
        // get the containing module's satellite name
        std::string routerName = this->containingModule->getFullName();

        // extract the satelliteId from the satellite name
        int satelliteId = std::stoi(routerName.substr(routerName.find("SAT")+3, 5));

        // get the attributes (srcId, destId, cost, linkId, interfaceName, interOrbit)
        // ------------------------------------------------------------------------------------------
        int srcId = LipsinTools::getIntAttr(*link, "srcId");
        int destId = LipsinTools::getIntAttr(*link, "destId");
        int cost = LipsinTools::getIntAttr(*link, "cost");
        int linkId = LipsinTools::getIntAttr(*link, "linkId");
        linkId = linkId + this->lidIncrease;
        IslType islType = LipsinTools::getIslType(*link, "linkType");
        std::string interfaceName = LipsinTools::getStrAttr(*link, "ifName");
        // ------------------------------------------------------------------------------------------

        // get the link info table
        // -----------------------------------------------------------------------------------------------------------
        auto* linkInfoTable = dynamic_cast<LinkInfoTable*>(this->containingModule->getSubmodule("linkInfoTable"));
        if(linkInfoTable == nullptr){
            throw cRuntimeError("LipsinRouteConfigurator::loadPhyInterfaceParameters: linkInfoTable is nullptr"); // NOLINT
        }
        // -----------------------------------------------------------------------------------------------------------

        // traverse the interfaceTable
        // -----------------------------------------------------------------------------------------------------------
        bool isCurrentSatelliteLink = false;
        NetworkInterface *interfaceEntry = nullptr;
        if(tagSatelliteId == satelliteId){
            isCurrentSatelliteLink = true;
            auto* interfaceTable = dynamic_cast<InterfaceTable*>(this->containingModule->getSubmodule("interfaceTable"));
            for(int i = 0; i < interfaceTable->getNumInterfaces(); i++){
                NetworkInterface* interfaceEntryTmp = interfaceTable->getInterface(i);
                if(interfaceEntryTmp->getInterfaceName() == interfaceName){
                    interfaceEntry = interfaceEntryTmp;
                }
            }
        }
        // -----------------------------------------------------------------------------------------------------------

        // if the link is current satellite's link
        // -----------------------------------------------------------------------------------------------------------
        if(isCurrentSatelliteLink) {
            auto* pltCmodule = this->containingModule->getSubmodule("lipsinNetworkLayer")->getSubmodule("plt");
            auto* physicalLinkTable = dynamic_cast<LipsinLinkTable*>(pltCmodule);
            auto* dltCmodule = this->containingModule->getSubmodule("lipsinNetworkLayer")->getSubmodule("dlt");
            auto* downLinkTable = dynamic_cast<LipsinLinkTable*>(dltCmodule);
            if(interfaceEntry->isUp()){
                // create new linkInfo and add into linkInfo table
                auto* upLinkInfo = new LinkInfo(srcId,destId,linkId,
                                              cost,LinkState::UP,islType,interfaceEntry, LinkType::PHYSICAL);
                linkInfoTable->addLinkInfo(upLinkInfo);

                // create new linkInfo and add into plt table
                auto* linkInfoForPlt = new LinkInfo(*upLinkInfo);
                physicalLinkTable->addEntry(linkInfoForPlt);
            } else {
                // create linkInfo and add into linkInfoTable
                cost = INT_MAX; // when the link state is down , the cost should be set to INT_MAX
                auto* downLinkInfo = new LinkInfo(srcId,destId,linkId,
                                              INT_MAX,LinkState::DOWN,islType,interfaceEntry, LinkType::PHYSICAL);
                linkInfoTable->addLinkInfo(downLinkInfo);

                // create linkInfo and add into plt table
                auto* linkInfoForPlt = new LinkInfo(*downLinkInfo);
                physicalLinkTable->addEntry(linkInfoForPlt);

                // create linkInfo and add into dlt table
                auto* linkInfoForDlt = new LinkInfo(*downLinkInfo);
                downLinkTable->addEntry(linkInfoForDlt);
            }
        }
        // the interface not in current router
        else {
            auto* linkInfo = new LinkInfo(srcId,destId,linkId,
                                          cost,LinkState::UNKNOWN_STATE,islType,nullptr, LinkType::PHYSICAL);
            linkInfoTable->addLinkInfo(linkInfo);
        }
        // -----------------------------------------------------------------------------------------------------------
    }

} /* namespace inet */

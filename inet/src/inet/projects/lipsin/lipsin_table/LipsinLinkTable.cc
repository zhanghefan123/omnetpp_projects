/*
 * LipsinLinkTable.cc
 *
 *  Created on: Sep 3, 2023
 *      Author: zhf
 */

#include "LipsinLinkTable.h"
#include "inet/projects/lipsin/lipsin_operator_reload/LipsinOperatorReload.h"
namespace inet {

    Define_Module(LipsinLinkTable);

    void LipsinLinkTable::initialize(int stage) {
        if(stage == INITSTAGE_LAST){
            addWatches();
        }
    }

    void LipsinLinkTable::addWatches() {
        WATCH_VECTOR(list);
    }

    LipsinLinkTable::~LipsinLinkTable(){
        // traverse the linkInfo inside
        for(auto link : this->list){
            delete link;
        }
    }

    std::vector<LinkInfo*> LipsinLinkTable::getLinkInfoVectorByInterface(NetworkInterface* interface, LinkType linkType){
        std::vector<LinkInfo*> result;
        for(auto linkInfo : this->list){
            if(linkInfo->getNetworkInterface() == interface){
                if(linkType == LinkType::ALL || (linkInfo->getLinkType() == linkType)){
                    result.push_back(new LinkInfo(*linkInfo));
                }
            }
        }
        return result;
    }

    void LipsinLinkTable::removeLinkInfosByInterface(NetworkInterface* interface){
        for(auto it = list.begin(); it != list.end(); it++){
            if((*it)->getNetworkInterface() == interface){
                delete *it;
                list.erase(it);
                it--;
            }
        }
    }

    void LipsinLinkTable::addEntry(LinkInfo* entry) {
        this->list.push_back(entry);
    }

    void LipsinLinkTable::removeEntry(int linkId) {
        // traverse the list
        for(auto it = list.begin(); it != list.end(); it++){
            if((*it)->getId() == linkId){
                list.erase(it);
                break;
            }
        }
    }

    std::vector<LinkInfo*> LipsinLinkTable::findOutputLinkIdentifiers(BloomFilter *bloomFilter){
        std::vector<LinkInfo*> outputLinkIdentifiers;
        for(auto & it : list){
            if((bloomFilter->query(it->getId()))){
                outputLinkIdentifiers.push_back(it);
            }
        }
        return outputLinkIdentifiers;
    }
} /* namespace inet */

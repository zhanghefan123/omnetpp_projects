/*
 * LipsinOperatorReload.cc
 *
 *  Created on: Sep 10, 2023
 *      Author: zhf
 */

#include "LipsinOperatorReload.h"

namespace inet {
    std::ostream& operator<< (std::ostream& os, const LinkInfo* linkInfo){
        std::string islTypeStr;
        if(linkInfo->getIslType() == IslType::INTER_ORBIT){
            islTypeStr = "INTER_ORBIT";
        }else if(linkInfo->getIslType() == IslType::INTRA_ORBIT){
            islTypeStr = "INTRA_ORBIT";
        } else {
            islTypeStr = "UNKNOWN";
        }
        std::string linkTypeStr;
        if(linkInfo->getLinkType() == LinkType::PHYSICAL){
            linkTypeStr = "PHYSICAL";
        }else{
            linkTypeStr = "VIRTUAL";
        }
        std::string linkStateStr;
        if(linkInfo->getState() == LinkState::UP){
            linkStateStr = "UP";
        }else if (linkInfo->getState() == LinkState::DOWN){
            linkStateStr = "DOWN";
        }else{
            linkStateStr = "UNKNOW";
        }
        os << "src: " << linkInfo->getSrc()
           << " dest: " << linkInfo->getDest()
           << " id: " << linkInfo->getId()
           << " cost: " << linkInfo->getCost()
           << " state: " << linkStateStr
           << " islType: " << islTypeStr;
        os << " linkType: " << linkTypeStr;
        if (linkInfo->getNetworkInterface() != nullptr){
            os << " interface: " << linkInfo->getNetworkInterface()->getInterfaceFullPath();
        } else {
            os << " interface: " << "not current satellite interface";
        }
        return os;
    }

    std::ostream& operator<< (std::ostream& os, const std::vector<LinkInfo*>& linkInfos){
        for(auto linkInfo : linkInfos){
            os << linkInfo->getSrc() << " ---> " << linkInfo->getDest() << " ";
        }
        return os;
    }

    std::ostream& operator<< (std::ostream & os, const std::tuple<int,int> sourceAndDest){
        os << std::get<0>(sourceAndDest) << " ---> " << std::get<1>(sourceAndDest) << " ";
        return os;
    }

    std::ostream& operator<< (std::ostream& os, LipsinNeighbor* lipsinNeighbor){
        os << "interface: " << lipsinNeighbor->correspondingLinkInfo->getNetworkInterface()->getInterfaceFullPath()
        << " current state: " << LipsinNeighbor::getStateString(lipsinNeighbor->state->getState())
        << " neighbor satellite id: " << lipsinNeighbor->neighborSatelliteId;
        return os;
    }

    std::ostream& operator<< (std::ostream& os, std::vector<int> destinationIds){
        for(auto destinationId : destinationIds){
            os << destinationId << ", ";
        }
        return os;
    }

} /* namespace inet */

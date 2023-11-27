/*
 * PathHeader.cc
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#include "PathHeader.h"
#include <cmath>

namespace inet {

    LinkSet* PathHeader::getSourceDecideLinkSet() const {
        return this->sourceDecideLinkSet;
    }

    LinkSet* PathHeader::getSourceDecideLinkSetNonConst() {
        return this->sourceDecideLinkSet;
    }

    LinkSet* PathHeader::getActualLinkSet() const {
        return this->actualLinkSet;
    }

    LinkSet* PathHeader::getActualLinkSetNonConst() {
        return this->actualLinkSet;
    }

    std::ostream& operator<<(std::ostream& os,const PathHeader& pathHeader) {
        os << "--------------------------------------------" << std::endl;
        os << "source decide sequence:     ";
        for(const auto& link: pathHeader.getSourceDecideLinkSet()->getInnerVector()){
            os << "(" << link->getSrc() << " --> " << link->getDest() << ")"<< " --> ";
        }
        os << std::endl;
        os << "actual forwarding sequence: ";
        for(const auto& link: pathHeader.getActualLinkSet()->getInnerVector()){
            os << "(" << link->getSrc() << " --> " << link->getDest() << ")"<< " --> ";
        }
        os << std::endl;
        os << "--------------------------------------------" << std::endl;
        return os;
    }

    int PathHeader::calculateRedundantForwarding() const {
        std::vector<LinkInfo*> sourceScheduledLinkSet = this->getSourceDecideLinkSet()->getInnerVector();
        std::vector<LinkInfo*> actualForwardLinkSet = this->getActualLinkSet()->getInnerVector();
        int largestIndex = std::min(int(sourceScheduledLinkSet.size()-1), int(actualForwardLinkSet.size()-1));
        int redundantForwardCount = 0;
        int index;
        for(index = 0 ; index <= largestIndex; index++){
            if(sourceScheduledLinkSet[index]->getId() != actualForwardLinkSet[index]->getId()){
                break;
            }
        }
        redundantForwardCount = int(actualForwardLinkSet.size()) - (index);
        return redundantForwardCount;
    }

} /* namespace inet */

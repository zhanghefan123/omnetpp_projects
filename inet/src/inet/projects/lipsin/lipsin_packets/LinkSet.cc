/*
 * LinkSet.cc
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#include "LinkSet.h"

namespace inet {

    int LinkSet::getLinkSetSize() const{
        return int(this->set.size());
    }

    void LinkSet::addLink(LinkInfo* linkInfo) {
        set.push_back(linkInfo);
    }

    void LinkSet::removeLink(int linkId) {
        for (auto it = set.begin(); it != set.end(); it++) {
            if ((*it)->getId() == linkId) {
                set.erase(it);
                break;
            }
        }
    }

    std::vector<LinkInfo*> LinkSet::getInnerVector() {
        return this->set;
    }

    LinkSet::LinkSet(const LinkSet &linkSet) {
        std::copy(linkSet.set.begin(), linkSet.set.end(), std::back_inserter(this->set));
    }
} /* namespace inet */

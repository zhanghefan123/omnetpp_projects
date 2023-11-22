/*
 * LinkSet.h
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_PACKETS_LINKSET_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_PACKETS_LINKSET_H_

#include <vector>
#include "inet/projects/lipsin/lipsin_table/LinkInfo.h"

namespace inet {

class LinkSet {
public:
    LinkSet(){this->set = {};};
    LinkSet(const LinkSet& linkSet);

    std::vector<LinkInfo*> set;

    int getLinkSetSize() const;

    void addLink(LinkInfo* linkInfo);

    void removeLink(int linkId);

    std::vector<LinkInfo*> getInnerVector();
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_PACKETS_LINKSET_H_ */

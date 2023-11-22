/*
 * PathHeader.h
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_PACKETS_PATHHEADER_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_PACKETS_PATHHEADER_H_
#include "LinkSet.h"

namespace inet {

class PathHeader {
private:
    LinkSet* actualLinkSet;
public:
    PathHeader(){
        this->actualLinkSet = new LinkSet();
    }
    ~PathHeader(){delete this->actualLinkSet;}
    PathHeader(const PathHeader& pathHeader){
        // call copy constructor of LinkSet
        this->actualLinkSet = new LinkSet(*pathHeader.actualLinkSet);
    }
public:
    LinkSet* getActualLinkSet();
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_PACKETS_PATHHEADER_H_ */

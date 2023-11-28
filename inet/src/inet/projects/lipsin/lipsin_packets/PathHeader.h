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
public:
    std::vector<int> encodingPointVector;
private:
    LinkSet* sourceDecideLinkSet = nullptr;
    LinkSet* actualLinkSet = nullptr;
public:
    PathHeader(){
        this->sourceDecideLinkSet = new LinkSet();
        this->actualLinkSet = new LinkSet();
    }

    ~PathHeader(){
        delete this->sourceDecideLinkSet;
        delete this->actualLinkSet;
    }

    PathHeader(const PathHeader& pathHeader){
        // call copy constructor of LinkSet
        this->sourceDecideLinkSet = new LinkSet(*pathHeader.sourceDecideLinkSet);
        this->actualLinkSet = new LinkSet(*pathHeader.actualLinkSet);
    }

    friend std::ostream& operator<<(std::ostream& os, const PathHeader& pathHeader);

    int calculateRedundantForwarding() const;

public:
    LinkSet* getSourceDecideLinkSet() const;
    LinkSet* getActualLinkSet() const;
    LinkSet* getSourceDecideLinkSetNonConst();
    LinkSet* getActualLinkSetNonConst();
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_PACKETS_PATHHEADER_H_ */

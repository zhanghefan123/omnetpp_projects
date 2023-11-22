/*
 * PathHeader.cc
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#include "PathHeader.h"

namespace inet {


    LinkSet *PathHeader::getActualLinkSet() {
        return this->actualLinkSet;
    }
} /* namespace inet */

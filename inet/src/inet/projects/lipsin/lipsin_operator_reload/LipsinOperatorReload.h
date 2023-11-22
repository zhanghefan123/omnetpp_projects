/*
 * LipsinOperatorReload.h
 *
 *  Created on: Sep 10, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_OPERATOR_RELOAD_LIPSINOPERATORRELOAD_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_OPERATOR_RELOAD_LIPSINOPERATORRELOAD_H_
#include <iostream>
#include <tuple>
#include <string>
#include "inet/projects/lipsin/lipsin_table/LinkInfo.h"
#include "inet/projects/lipsin/lipsin_table/LipsinRoutingTable.h"
#include "inet/projects/lipsin/lipsin_neighbor/LipsinNeighbor.h"
namespace inet {
    std::ostream& operator<< (std::ostream& os, const LinkInfo* linkInfo);
    std::ostream& operator<< (std::ostream& os, const std::vector<LinkInfo*>& linkInfos);
    std::ostream& operator<< (std::ostream& os, const std::tuple<int,int> sourceAndDest); // NOLINT
    std::ostream& operator<< (std::ostream& os, LipsinNeighbor* lipsinNeighbor);
    std::ostream& operator<< (std::ostream& os, std::vector<int> destinationIds);
}
#endif /* INET_PROJECTS_LIPSIN_LIPSIN_OPERATOR_RELOAD_LIPSINOPERATORRELOAD_H_ */

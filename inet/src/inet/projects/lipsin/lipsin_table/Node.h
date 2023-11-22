#ifndef INET_PROJECTS_LIPSIN_LIPSIN_TABLE_NODE_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_TABLE_NODE_H_
#include <vector>
#include "LinkInfo.h"
namespace inet{
    class Node{
    public:
        int nodeId;
        int cost;
        std::vector<LinkInfo*> path;
        Node(int nodeIdTmp,int costTmp,std::vector<LinkInfo*> pathTmp){
            this->nodeId = nodeIdTmp;
            this->cost = costTmp;
            this->path = std::move(pathTmp);
        }
    };
}
#endif
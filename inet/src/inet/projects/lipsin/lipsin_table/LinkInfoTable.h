//
// Created by zhf on 23-9-1.
//

#ifndef DELAYTOLERANTNETWORK_LINKINFOTABLE_H
#define DELAYTOLERANTNETWORK_LINKINFOTABLE_H
#include <map>
#include <tuple>
#include <vector>
#include "Node.h"
#include "inet/projects/lipsin/lipsin_config/LipsinRouteConfigurator.h"
#include "inet/projects/lipsin/lipsin_operator_reload/LipsinOperatorReload.h"
using namespace omnetpp;

namespace inet{
    class LinkInfoTable:public cSimpleModule{ // NOLINT
    public:
        bool isApplicationLayerRegistered = false;
        cMessage* recalculateTimer;
        double recalculateInterval;
        bool isLinkUpdated;
    private:
        int lidIncrease = 0;
        cModule* containingModule;
        std::map<std::tuple<int,int>,LinkInfo*> linkInfoTable; // each link's information <src,dest> -> LinkInfo
        std::map<int, LinkInfo*> linkInfoTableById; // each link's information <id> -> LinkInfo
        std::map<int, std::vector<LinkInfo*>> nodeLinkTable; // each node's interfaces
        LipsinRoutingTable* lipsinRoutingTable; // current node's routing table
    public:
        ~LinkInfoTable() override;
        LinkInfoTable() = default;
    public:
        void setupTimer();
        void updateLinkCostAndState(LinkInfo* linkInfo, int cost, LinkState linkState);
        void addLinkInfo(LinkInfo* linkInfo);
        void addWatches();
    public:
        // table getter
        std::map<int, LinkInfo*> getLinkInfoTableById(){return this->linkInfoTableById;}
        std::map<int, std::vector<LinkInfo*>> getNodeLinkTable(){return this->nodeLinkTable;}
        std::map<std::tuple<int,int>,LinkInfo*> getLinkInfoTable(){return this->linkInfoTable;}

        // getter and setter
        int getLidIncrease() const{return this->lidIncrease;}
        void setLidIncrease(int lidIncreaseTmp){this->lidIncrease = lidIncreaseTmp;}

        int getLinkIdBySrcAndDest(int src, int dest);
        void setLinkIdBySrcAndDest(int src, int dest, int id);

        int getLinkCostBySrcAndDest(int src, int dest);
        void setLinkCostBySrcAndDest(int src, int dest, int cost);

        LinkState getLinkStateBySrcAndDest(int src, int dest);
        void setLinkStateBySrcAndDest(int src, int dest, LinkState state);

        IslType getLinkOrbitTypeBySrcAndDest(int src, int dest);
        void setLinkOrbitTypeBySrcAndDest(int src, int dest, IslType interOrbit);

    public:
        void reCalculateRouteByFloyd();
        void reCalculateRouteByDijkstra();
        void printNodeLinkTable();
    private:
        // dijkstra's step
        void updateNodesInfo(Node* currentNode,std::map<int, Node*>& unVisitedNodesMap);
        // dijkstra's step
        Node* findMinimalCostUnvisitedNode(std::map<int, Node*>& unVisitedNodesMap);
        // dijkstra's step
        void eraseNodeFromUnvisitedNodes(std::map<int, Node*>& unVisitedNodesMap,
                                         std::vector<Node*>& unvisitedNodes,
                                         int nodeId);
    protected:
        void initialize(int stage) override;
        int numInitStages() const override { return NUM_INIT_STAGES; }
        void handleMessage(cMessage * message) override;
        void handleTimer(cMessage * message);
    };
}
#endif //DELAYTOLERANTNETWORK_LINKINFOTABLE_H

#include "LinkInfoTable.h"
namespace inet{
    Define_Module(LinkInfoTable);

    /**
     * initialize stage
     * @param stage current initilization stage
     */
    void LinkInfoTable::initialize(int stage) {
        // there are so many stages, we only setting our parameters in the local stage
        if(stage == INITSTAGE_LOCAL){
            this->lipsinRoutingTable = dynamic_cast<LipsinRoutingTable*>(this->getParentModule()->getSubmodule("lipsinRoutingTable"));
            this->setupTimer();
        } else if (stage == INITSTAGE_APPLICATION_LAYER){
            // second we need to calculate the source routing table with dijkstra algorithm.
            this->reCalculateRouteByDijkstra();
            lipsinRoutingTable->persist();
            // recalculate the route by floyd - in order to get the arbitrary two nodes routes.
            // this->reCalculateRouteByFloyd();
            // add watches.
            this->addWatches();
        }
    }

    /**
     * handle message
     * @param message the only message will be received here is the timer
     */
    void LinkInfoTable::handleMessage(cMessage *message) {
        if(message->isSelfMessage()){
            this->handleTimer(message);
        }
    }

    void LinkInfoTable::handleTimer(cMessage *message){ // NOLINT
        if(message == this->recalculateTimer){
            // we need to check whether the isLinkUpdated is set to true
            if(isLinkUpdated){
                this->reCalculateRouteByDijkstra();
            }
            // schedule the next recalculate moment
            this->scheduleAt(simTime() + this->recalculateInterval, this->recalculateTimer);
        } else {
            throw cRuntimeError("unknown timer"); // NOLINT
        }
    }


    LinkInfoTable::~LinkInfoTable() {
        // delete the timer
        if(this->recalculateTimer != nullptr){
            if(this->recalculateTimer->isSelfMessage()){
                // cancel and delete the timer
                this->cancelAndDelete(this->recalculateTimer);
            } else {
                // delete the recalculate timer
                delete this->recalculateTimer;
            }
        }

        // traverse the linkInfoTable and delete the linkInfo pointer
        for(auto& it:linkInfoTable){
            delete it.second;
        }
        // traverse the nodeLinkTable and delete the linkInfo pointer
        for(auto& out_it: nodeLinkTable){
            for(auto& inner_it: out_it.second){
                delete inner_it;
            }
        }
        // traver the linkInfoTableById and delete the linkInfo pointer
        for(auto& it : linkInfoTableById){
            delete it.second;
        }
    }

    /**
     * add watches to linkInfoTableById and nodeLinkTable
     */
    void LinkInfoTable::addWatches(){
        WATCH_MAP(this->linkInfoTableById);
        WATCH_MAP(this->nodeLinkTable);
    }

    /**
     * set up the timer
     */
    void LinkInfoTable::setupTimer(){
        this->recalculateTimer = nullptr;
        /*
        this->recalculateTimer = new cMessage("recalculateTimer");
        this->recalculateInterval = this->par("recalculateInterval").doubleValue();
        this->isLinkUpdated = false; // when link is updated we need to recalculate the route
        if(this->recalculateInterval > 0){
            this->scheduleAt(simTime()+this->recalculateInterval, this->recalculateTimer);
        }
         */
    }

    /**
     * update the link cost and linkState / once updated the isLinkUpdated is set to false
     * @param linkInfo the linkInfo need to be update
     * @param cost the updated link cost
     * @param linkState the updated link state
     */
    void LinkInfoTable::updateLinkCostAndState(LinkInfo* linkInfo, int cost, LinkState linkState){
        this->isLinkUpdated = true;
        // modify the link cost in linkInfoTable & nodeLinkTable & linkInfoTableById
        // modify the link Info Table
        std::tuple<int,int> key = std::make_tuple(linkInfo->getSrc(), linkInfo->getDest());
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            linkInfoTable[key]->setCost(cost);
            linkInfoTable[key]->setState(linkState);
        } else {
            throw cRuntimeError("the specified link doesn't exist in linkInfoTable"); // NOLINT
        }
        // modify the node link table
        bool findLinkInfo = false;
        for(auto nodeIdentifier : this->nodeLinkTable[linkInfo->getSrc()])
        {
            if(nodeIdentifier->getId() == linkInfo->getId()){
                nodeIdentifier->setCost(cost);
                nodeIdentifier->setState(linkState);
                findLinkInfo = true;
            }
        }
        if(!findLinkInfo){
            throw cRuntimeError("the specified link doesn't exist in nodeLinkTable"); // NOLINT
        }
        // modify the linkInfoTableById
        if(linkInfoTableById.find(linkInfo->getId()) != linkInfoTableById.end()){
            linkInfoTableById[linkInfo->getId()]->setCost(cost);
            linkInfoTableById[linkInfo->getId()]->setState(linkState);
        } else {
            throw cRuntimeError("the specified link doesn't exist in linkInfoTableById"); // NOLINT
        }
    }

    /**
     * add link info to three tables (linkInfoTable | nodeLinkTable | linkInfoTableById)
     * @param linkInfo
     */
    void LinkInfoTable::addLinkInfo(LinkInfo* linkInfo) {
        // add the link into linkInfoTable
        std::tuple<int,int> key = std::make_tuple(linkInfo->getSrc(),linkInfo->getDest());
        if(linkInfoTable.find(key) == linkInfoTable.end()) {
            linkInfoTable[key] = linkInfo;
        }
        else {
            std::string output = std::to_string(linkInfo->getSrc()) + " " + std::to_string(linkInfo->getDest());
            throw omnetpp::cRuntimeError("%s", output.c_str()); // NOLINT
        }
        auto* linkInfoForNodeLinkTable = new LinkInfo(*linkInfo);
        // add the link into the nodeLinkTable
        if(nodeLinkTable.find(linkInfoForNodeLinkTable->getSrc()) == nodeLinkTable.end())
        {
            nodeLinkTable[linkInfoForNodeLinkTable->getSrc()] = {};
            nodeLinkTable[linkInfoForNodeLinkTable->getSrc()].push_back(linkInfoForNodeLinkTable);
        } else {
            nodeLinkTable[linkInfoForNodeLinkTable->getSrc()].push_back(linkInfoForNodeLinkTable);
        }
        // add the link into the linkInfoTableById
        auto* linkInfoForLinkInfoTableById = new LinkInfo(*linkInfo);
        if(linkInfoTableById.find(linkInfoForLinkInfoTableById->getId()) == linkInfoTableById.end()){
            linkInfoTableById[linkInfoForLinkInfoTableById->getId()] = linkInfoForLinkInfoTableById;
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::addLinkInfo: linkInfoTableById already has this linkInfo");// NOLINT
        }
    }

    int LinkInfoTable::getLinkIdBySrcAndDest(int src, int dest) {
        std::tuple<int,int> key = std::make_tuple(src,dest);
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            return linkInfoTable[key]->getId();
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::getLinkIdBySrcAndDest: linkInfoTable does not have this linkInfo");// NOLINT
        }
    }

    void LinkInfoTable::setLinkIdBySrcAndDest(int src, int dest, int id) {
        std::tuple<int, int> key = std::make_tuple(src, dest);
        if (linkInfoTable.find(key) != linkInfoTable.end()) {
            linkInfoTable[key]->setId(id);
        } else {
            throw omnetpp::cRuntimeError(// NOLINT
                    "LinkInfoTable::setLinkIdBySrcAndDest: linkInfoTable does not have this linkInfo");
        }
    }


    int LinkInfoTable::getLinkCostBySrcAndDest(int src, int dest) {
        std::tuple<int,int> key = std::make_tuple(src,dest);
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            return linkInfoTable[key]->getCost();
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::getLinkCostBySrcAndDest: linkInfoTable does not have this linkInfo");// NOLINT
        }
    }

    void LinkInfoTable::setLinkCostBySrcAndDest(int src, int dest, int cost) {
        std::tuple<int,int> key = std::make_tuple(src,dest);
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            linkInfoTable[key]->setCost(cost);
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::setLinkCostBySrcAndDest: linkInfoTable does not have this linkInfo");// NOLINT
        }
    }

    LinkState LinkInfoTable::getLinkStateBySrcAndDest(int src, int dest) {
        std::tuple<int,int> key = std::make_tuple(src,dest);
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            return linkInfoTable[key]->getState();
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::getLinkStateBySrcAndDest: linkInfoTable does not have this linkInfo");// NOLINT
        }
    }

    void LinkInfoTable::setLinkStateBySrcAndDest(int src, int dest, LinkState state) {
        std::tuple<int,int> key = std::make_tuple(src,dest);
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            linkInfoTable[key]->setState(state);
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::setLinkStateBySrcAndDest: linkInfoTable does not have this linkInfo");// NOLINT
        }
    }

    IslType LinkInfoTable::getLinkOrbitTypeBySrcAndDest(int src, int dest) {
        std::tuple<int,int> key = std::make_tuple(src,dest);
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            return linkInfoTable[key]->getIslType();
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::getLinkInterOrbitBySrcAndDest: " // NOLINT
                                         "linkInfoTable does not have this linkInfo");
        }
    }

    void LinkInfoTable::setLinkOrbitTypeBySrcAndDest(int src, int dest, IslType islType) {
        std::tuple<int,int> key = std::make_tuple(src,dest);
        if(linkInfoTable.find(key) != linkInfoTable.end()){
            linkInfoTable[key]->setIslType(islType);
        }
        else{
            throw omnetpp::cRuntimeError("LinkInfoTable::setLinkInterOrbitBySrcAndDest: linkInfoTable does not have this linkInfo"); // NOLINT
        }
    }

    void LinkInfoTable::eraseNodeFromUnvisitedNodes(std::map<int, Node*>& unVisitedNodesMap, // NOLINT
                                                    std::vector<Node*>& unVisitedNodes, int nodeId){
        auto iterator = unVisitedNodesMap.find(nodeId);
        unVisitedNodesMap.erase(iterator);
        for(auto iter = unVisitedNodes.begin(); iter!=unVisitedNodes.end();){
            if((*iter)->nodeId == nodeId){
                iter = unVisitedNodes.erase(iter);
            } else {
                iter++;
            }
        }
    }

    Node* LinkInfoTable::findMinimalCostUnvisitedNode(std::map<int, Node*>& unVisitedNodesMap){ // NOLINT
        int minCost = INT_MAX;
        int minNodeId = -1;
        bool find = false;
        for(auto node : unVisitedNodesMap){
            if(node.second->cost < minCost){
                minCost = node.second->cost;
                minNodeId = node.first;
                find = true;
            }
        }
        if(!find){
            return nullptr;
        }
        else{
            return unVisitedNodesMap[minNodeId];
        }
    }

    /**
     * this is the subprocess of dijkstra algorithm
     * @param currentNode the current visited node
     * @param unVisitedNodesMap the unvisited nodes map
     */
    void LinkInfoTable::updateNodesInfo(Node* currentNode,std::map<int, Node*>& unVisitedNodesMap) {
        int currentSrc = currentNode->nodeId;
        int currentCost = currentNode->cost;
        for(auto linkInfo : this->nodeLinkTable[currentSrc]){
            int linkDest = linkInfo->getDest();
            int linkCost = linkInfo->getCost();
            if(unVisitedNodesMap.find(linkDest) != unVisitedNodesMap.end()){
                Node* unVisitedNode = unVisitedNodesMap[linkDest];
                int destCurrentCost = unVisitedNode->cost;
                // avoid INT_MAX + 1 underflow
                if((currentCost == INT_MAX) || (linkCost == INT_MAX)){
                    continue;
                }
                // see if we can update the cost
                if(destCurrentCost >= currentCost + linkCost){
                    unVisitedNode->path.clear();
                    unVisitedNode->path.insert(unVisitedNode->path.begin(),currentNode->path.begin(),currentNode->path.end());
                    unVisitedNode->path.push_back(linkInfo);
                    unVisitedNode->cost = currentCost + linkCost;
                }
            }
        }
    }

    /**
     * dijkstra algorithm which will be used to update the lipsin routing table
     */
    void LinkInfoTable::reCalculateRouteByDijkstra() {
        // after the recalculate the latest link info is used
        isLinkUpdated = false;
        // get satellite id
        std::string routerName = this->getParentModule()->getFullName();
        int currentSatelliteId = std::stoi(routerName.substr(routerName.find("SAT")+3, 5));
        // create source routing table
        std::map<int, std::vector<LinkInfo*>> newSourceRoutingTable;
        // each node has four links
        int nodeNums = int(nodeLinkTable.size());
        for(int i = 0; i < nodeNums; i++){
            newSourceRoutingTable[i] = std::vector<LinkInfo*>();
        }
        // visited nodes - <nodeId,cost,path>
        std::vector<Node*> visitedNodes;
        std::vector<Node*> unVisitedNodes;
        std::map<int, Node*> unVisitedNodesMap;
        // recent node
        Node* currentNode;
        // initialize the nodes
        for(int i = 0; i < nodeNums; i++){
            if(currentSatelliteId == i){
                Node* node = new Node(i,0,std::vector<LinkInfo*>());
                visitedNodes.push_back(node);
                currentNode = node;
            } else {
                Node* node = new Node(i,INT_MAX,std::vector<LinkInfo*>());
                unVisitedNodes.push_back(node);
                unVisitedNodesMap[i] = node;
            }
        }
        while(!unVisitedNodes.empty()){
            // with the help of current node to update its neighbors
            updateNodesInfo(currentNode,unVisitedNodesMap);
            // find the node with the minimum cost
            Node* minimumUnvisitedNode = findMinimalCostUnvisitedNode(unVisitedNodesMap);
            if(minimumUnvisitedNode != nullptr){
                // erase the node in unvisited structure
                eraseNodeFromUnvisitedNodes(unVisitedNodesMap, unVisitedNodes, minimumUnvisitedNode->nodeId);
                // put the node in the visited structure
                visitedNodes.push_back(minimumUnvisitedNode);
            } else {
                break;
            }
            currentNode = minimumUnvisitedNode;
        }
        // traverse the visitedNodes to get the routing table
        for(auto item : visitedNodes){
            newSourceRoutingTable[item->nodeId].insert(newSourceRoutingTable[item->nodeId].end(),item->path.begin(),item->path.end());
            item->path.clear();
        }
        this->lipsinRoutingTable->updateRoutingTable(newSourceRoutingTable);
    }

    /**
     * we can calculate the route of all <source,destination> pairs
     */
    void LinkInfoTable::reCalculateRouteByFloyd() {
        // -1. initialize the global routes
        std::map<std::string, std::vector<LinkInfo*>> global_routes;
        // 0. create the cost matrix
        std::vector<std::vector<int>> costMatrix;
        // 1. get the number of elements
        int nodeNum = int(nodeLinkTable.size());
        // 2. initialize the costMatrix [n,n] matrix
        costMatrix = std::vector<std::vector<int>>(nodeNum, std::vector<int>(nodeNum, INT_MAX));
        // 3. initialize the already know link value
        for(int source = 0;source < nodeNum; source++){
            costMatrix[source][source] = 0;
            // traverse all the links start from the node i
            for(auto linkInfo : nodeLinkTable[source]){
                int destination = linkInfo->getDest();
                std::string sourceToDest = std::to_string(source)+"->"+std::to_string(destination);
                if(global_routes.find(sourceToDest) == global_routes.end()){
                    global_routes[sourceToDest] = {linkInfo};
                } else {
                    global_routes[sourceToDest].push_back(linkInfo);
                }
                // update the cost matrix
                costMatrix[source][destination] = 1;
            }
        }

        // 4. go into the three loops
        // 4.1 the first loop is used to put each node as a transit point
        for(int k = 0; k < nodeNum; k++) {
            // 4.2 the other two loops are used to traverse the links
            for (int i = 0; i < nodeNum; i++) {
                for (int j = 0; j < nodeNum; j++) {
                    // if k == i or k == j continue cut split
                    if ((k == j) || (k == i) || (i == j)) {
                        continue;
                    }
                    // cut split
                    if ((costMatrix[i][k] == INT_MAX) || (costMatrix[k][j] == INT_MAX)) {
                        continue;
                    }
                    if ((costMatrix[i][k] + costMatrix[k][j]) < costMatrix[i][j]) {
                        costMatrix[i][j] = costMatrix[i][k] + costMatrix[k][j];
                        // create three i->j i->k k->j pairs
                        std::string i_to_j_str = std::to_string(i) + "->" + std::to_string(j);
                        std::string i_to_k_str = std::to_string(i) + "->" + std::to_string(k);
                        std::string k_to_j_str = std::to_string(k) + "->" + std::to_string(j);
                        if (global_routes.find(i_to_j_str) == global_routes.end()) {
                            global_routes[i_to_j_str] = {};
                        } else {
                            global_routes[i_to_j_str].clear();
                        }
                        for (auto item: global_routes[i_to_k_str]) {
                            global_routes[i_to_j_str].push_back(item);
                        }
                        for (auto item: global_routes[k_to_j_str]) {
                            global_routes[i_to_j_str].push_back(item);
                        }
                    }

                }
            }
        }

        this->lipsinRoutingTable->updateGlobalRoutingTable(global_routes);
    }

    /**
     * print the node Link Table
     */
    void LinkInfoTable::printNodeLinkTable() {
        for(const auto& link : this->nodeLinkTable){
            std::cout << "satellite " << link.first << " has links: " << std::endl;
            for(auto linkInfo : link.second){
                std::cout << "link id: " << linkInfo->getId() << " link dest: " << linkInfo->getDest() << " link cost: " << linkInfo->getCost() << std::endl;
            }
            std::cout << std::endl;
        }
    }
}

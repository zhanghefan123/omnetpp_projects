/*
 * LinkInfo.h
 *
 *  Created on: Sep 1, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LINKINFO_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LINKINFO_H_
#include <utility>
#include <vector>
#include "inet/networklayer/common/NetworkInterface.h"
namespace inet{

    enum LinkState{
        UP,
        DOWN,
        UNKNOWN_STATE
    };

    enum IslType{
        INTER_ORBIT,
        INTRA_ORBIT,
        UNKNOWN_TYPE
    };

    enum LinkType{
        PHYSICAL,
        VIRTUAL,
        ALL
    };

    enum BelongingTable{
        PHYSICAL_TABLE,
        VIRTUAL_TABLE
    };

    class LinkInfo{
    private:
        int src;
        int dest;
        int id;
        int cost;
        LinkState state;
        IslType islType;
        NetworkInterface *networkInterface;
        LinkType linkType;
    public:
        // destructor
        ~LinkInfo() = default;
        // constructor
        LinkInfo(int src,
                 int dest,
                 int id,
                 int cost,
                 LinkState state,
                 IslType islType,
                 NetworkInterface* networkInterface,
                 LinkType linkTypeTmp){
            this->src = src;
            this->dest = dest;
            this->id = id;
            this->cost = cost;
            this->state = state;
            this->islType = islType;
            this->networkInterface = networkInterface;
            this->linkType = linkTypeTmp;
        }
        // copy constructor
        LinkInfo(const LinkInfo& linkInfo){
            this->src = linkInfo.src;
            this->dest = linkInfo.dest;
            this->id = linkInfo.id;
            this->cost = linkInfo.cost;
            this->state = linkInfo.state;
            this->islType = linkInfo.islType;
            this->networkInterface = linkInfo.networkInterface;
            this->linkType = linkInfo.linkType;
        }


        /**
         * get the link type (PHYSICAL | VIRTUAL)
         * @return
         */
        LinkType getLinkType() const{
            return this->linkType;
        }

        /**
         * set the link type (PHYSICAL | VIRTUAL)
         * @param linkTypeTmp
         */
        void setLinkType(LinkType linkTypeTmp){
            this->linkType = linkTypeTmp;
        }

        /**
         * get the source satellite id
         * @return
         */
        int getSrc() const {
            return src;
        }

        /**
         * set the source satellite id
         * @param srcTmp
         */
        void setSrc(int srcTmp) {
            this->src = srcTmp;
        }

        /**
         * get the destination satellite id
         * @return
         */
        int getDest() const {
            return dest;
        }

        /**
         * set the destination satellite id
         * @param destTmp
         */
        void setDest(int destTmp) {
            this->dest = destTmp;
        }

        /**
         * get the link id
         * @return
         */
        int getId() const {
            return id;
        }

        /**
         * set the link id
         * @param idTmp
         */
        void setId(int idTmp) {
            this->id = idTmp;
        }

        /**
         * get the link cost
         * @return
         */
        int getCost() const {
            return cost;
        }

        /**
         * set the link cost
         * @param costTmp
         */
        void setCost(int costTmp) {
            this->cost = costTmp;
        }

        /**
         * get the link state (UP | DOWN)
         * @return
         */
        LinkState getState() const {
            return state;
        }

        /**
         * set the link state (UP | DOWN)
         * @param stateTmp
         */
        void setState(LinkState stateTmp) {
            this->state = stateTmp;
        }

        /**
         * get the isl type (INTER_ORBIT | INTRA_ORBIT)
         * @return
         */
        IslType getIslType() const{
            return this->islType;
        }

        /**
         * set the isl type (INTER_ORBIT | INTRA_ORBIT)
         * @param islTypeTmp
         */
        void setIslType(IslType islTypeTmp){
            this->islType = islTypeTmp;
        }

        /**
         * get the network interface
         * @return
         */
        NetworkInterface* getNetworkInterface() const {
            return networkInterface;
        }
    };
}
#endif /* INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LINKINFO_H_ */

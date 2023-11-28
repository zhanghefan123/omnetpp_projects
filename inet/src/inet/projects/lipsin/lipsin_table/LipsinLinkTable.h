/*
 * LipsinLinkTable.h
 *
 *  Created on: Sep 3, 2023
 *      Author: zhf
 */

#ifndef INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LIPSINLINKTABLE_H_
#define INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LIPSINLINKTABLE_H_

#include <vector>
#include "inet/projects/lipsin/lipsin_table/LinkInfo.h"
#include "inet/projects/lipsin/lipsin_packets/BloomFilter.h"

using namespace omnetpp;

namespace inet {

class LipsinLinkTable : public cSimpleModule{
private:
    std::vector<LinkInfo*> list;
public:
    LipsinLinkTable() = default;
    ~LipsinLinkTable() override;
public:
    void addWatches();
    std::vector<LinkInfo*> getInnerList(){return this->list;};
    void addEntry(LinkInfo* entry);
    void removeEntry(int linkId);
    std::vector<LinkInfo*> findOutputLinkIdentifiers(BloomFilter *bloomFilter);
    std::vector<LinkInfo*> findAllOutputLinkIdentifiers();
    int getLinkNum() const { return int(list.size()); }
    std::vector<LinkInfo*> getLinkInfoVectorByInterface(NetworkInterface* interface, LinkType linkType);
    void removeLinkInfosByInterface(NetworkInterface* interface);
protected:
    void initialize(int stage) override;
    int numInitStages() const override { return NUM_INIT_STAGES; }
};

} /* namespace inet */

#endif /* INET_PROJECTS_LIPSIN_LIPSIN_TABLE_LIPSINLINKTABLE_H_ */

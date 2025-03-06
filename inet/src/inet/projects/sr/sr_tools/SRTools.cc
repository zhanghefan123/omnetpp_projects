//
// Created by 张贺凡 on 2024/5/6.
//
#include "inet/projects/sr/sr_tools/SRTools.h"

namespace inet{
    void SRTools::PRINT_SR_HEADER(Ptr<const inet::SRHeader> srHeader) {
        std::cout << "source satellite id: " << srHeader->getSource_node_id() << std::endl;
        std::cout << "destination satellite id: " << srHeader->getDestination_node_id() << std::endl;
        std::cout << "current sid index: " << srHeader->getSid_index() << std::endl;
        std::cout << "-------------- link identifiers --------------" << std::endl;
        for(int index = 0; index < srHeader->getSidsArraySize(); index++){
            std::cout << "[" << index << "]" << "-->" << srHeader->getSids(index) << std::endl;
        }
        std::cout << "-------------- link identifiers --------------" << std::endl;
        std::cout << std::endl;
    }
}
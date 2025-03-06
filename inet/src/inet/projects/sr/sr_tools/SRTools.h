//
// Created by 张贺凡 on 2024/5/6.
//

#ifndef INET_PROJECTS_DELAYTOLERANTNETWORK_SRTOOLS_H
#define INET_PROJECTS_DELAYTOLERANTNETWORK_SRTOOLS_H
#include "inet/projects/sr/sr_packet/SRHeader_m.h"
namespace inet{
    class SRTools{
    public:
        static void PRINT_SR_HEADER(Ptr<const SRHeader> srHeader);
    };
}
#endif //INET_PROJECTS_DELAYTOLERANTNETWORK_SRTOOLS_H

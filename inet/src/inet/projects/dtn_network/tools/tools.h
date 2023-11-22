#ifndef __INET_DTN_TOOLS_H
#define __INET_DTN_TOOLS_H
#include <iostream>
#include <omnetpp/cmodule.h>
namespace inet{
    std::string module_log(omnetpp::cModule *mod, const std::string& msg);
    bool isFolderExist(const std::string& folderPath);
    int getFileCount(const std::string& folderPath);
}
#endif
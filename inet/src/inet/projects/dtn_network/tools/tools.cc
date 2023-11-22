#include "tools.h"
#include <sys/stat.h>
#include <dirent.h>
namespace inet{
    std::string module_log(omnetpp::cModule *module, const std::string& msg){
        std::string output;
        output += "[",
        output += module->getFullPath();
        output += "]-";
        output += msg;
        output += "-[";
        output += std::to_string(omnetpp::simTime().dbl());
        output += "]";
        return output;
    }

    bool isFolderExist(const std::string& folderPath){
        struct stat info{};
        if(stat(folderPath.c_str(), &info) != 0)
        {
            return false;
        } else if(info.st_mode & S_IFDIR){
            return true;
        } else {
            return false;
        }
    }

    int getFileCount(const std::string& folderPath) {
        DIR *dir;
        struct dirent *ent;
        int count = 0;
        dir = opendir(folderPath.c_str());
        if (dir != nullptr) {
            while ((ent = readdir(dir)) != nullptr) {
                if (ent->d_type == DT_REG) {
                    count++;
                }
            }
            closedir(dir);
            return count;
        } else {
            return 0;
        }
        return 0;
    }

}
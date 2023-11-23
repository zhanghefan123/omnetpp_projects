#ifndef MULTILAYER_TOOLS_H
#define MULTILAYER_TOOLS_H
#include <iostream>
#include <omnetpp.h>
#include "inet/common/geometry/common/Coord.h"
#include "osg/Drawable"
using namespace omnetpp;
namespace inet{
    class MultilayerTools{
    public:
        static std::pair<std::string, int> getNameAndIndex(const char* s);
        static double calculateDistance(const Coord& s,const Coord& d);
        static osg::ref_ptr<osg::Drawable> createLineBetweenPoints(osg::Vec3 start, osg::Vec3 end, float width, osg::Vec4 color);
    };
}

#endif // MULTILAYER_TOOLS_H
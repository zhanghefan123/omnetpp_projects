//
// Created by 张贺凡 on 2023/11/23.
//
#include "MultilayerTools.h"
#include <osg/Geometry>
#include <osgEarthUtil/LinearLineOfSight>
#include <osgUtil/UpdateVisitor>
#include <osg/LineWidth>
#include <osg/Depth>

namespace inet{
    std::pair<std::string, int> MultilayerTools::getNameAndIndex(const char* s) {
        std::string temp = s;
        char left = '[';
        char right = ']';
        std::string name = std::string(s).substr(0, temp.find(left));
        int lengthOfTheIndex = int(temp.find(right) - temp.find(left) - 1);
        int index = std::stoi(temp.substr(temp.find(left)+1, lengthOfTheIndex));
        return std::make_pair(name, index);
    }

    double MultilayerTools::calculateDistance(const Coord& s,const Coord& d){
        double x1,x2,y1,y2,z1,z2,xDis,yDis,zDis;
        x1 = s.getX();
        x2 = d.getX();
        y1 = s.getY();
        y2 = d.getY();
        z1 = s.getZ();
        z2 = d.getZ();
        xDis = std::abs(x1 - x2);
        yDis = std::abs(y1 - y2);
        zDis = std::abs(z1 - z2);
        return std::sqrt(xDis*xDis + yDis*yDis + zDis*zDis) * 2;
    }

    osg::ref_ptr<osg::Drawable> MultilayerTools::createLineBetweenPoints(osg::Vec3 start, osg::Vec3 end, float width, osg::Vec4 color){
        osg::ref_ptr<osg::Geometry> orbitGeom = new osg::Geometry;
        osg::ref_ptr<osg::DrawArrays> drawArrayLines = new  osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP);
        osg::ref_ptr<osg::Vec3Array> vertexData = new osg::Vec3Array;

        orbitGeom->addPrimitiveSet(drawArrayLines);
        auto stateSet = orbitGeom->getOrCreateStateSet();
        stateSet->setAttributeAndModes(new osg::LineWidth(width), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
        stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
        auto depth = new osg::Depth;
        depth->setWriteMask(false);
        stateSet->setAttributeAndModes(depth, osg::StateAttribute::ON);

        vertexData->push_back(start);
        vertexData->push_back(end);

        orbitGeom->setVertexArray(vertexData);
        drawArrayLines->setFirst(0);
        drawArrayLines->setCount(int(vertexData->size()));

        osg::ref_ptr<osg::Vec4Array> colorData = new osg::Vec4Array;
        colorData->push_back(osgEarth::Color(color));
        orbitGeom->setColorArray(colorData, osg::Array::BIND_OVERALL);
        return orbitGeom;
    }
}







//
// Copyright (C) 2020 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef __INET_PATHOSGVISUALIZERBASE_H
#define __INET_PATHOSGVISUALIZERBASE_H

#include <osg/ref_ptr>
#include <osg/Node>

#include "inet/visualizer/base/PathVisualizerBase.h"

namespace inet {

namespace visualizer {

class INET_API PathOsgVisualizerBase : public PathVisualizerBase
{
  protected:
    class INET_API PathOsgVisualization : public PathVisualization {
      public:
        osg::ref_ptr<osg::Node> node;

      public:
        PathOsgVisualization(const char *label, const std::vector<int>& path, osg::Node *node);
    };

  protected:
    virtual void initialize(int stage) override;
    virtual void refreshDisplay() const override;

    virtual const PathVisualization *createPathVisualization(const char *label, const std::vector<int>& path, cPacket *packet) const override;
    virtual void addPathVisualization(const PathVisualization *pathVisualization) override;
    virtual void removePathVisualization(const PathVisualization *pathVisualization) override;
    virtual void setAlpha(const PathVisualization *pathVisualization, double alpha) const override;
};

} // namespace visualizer

} // namespace inet

#endif


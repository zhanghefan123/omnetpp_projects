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

#ifndef __INET_NETWORKNODEOSGVISUALIZER_H
#define __INET_NETWORKNODEOSGVISUALIZER_H

#include <osg/ref_ptr>

#include "inet/visualizer/base/NetworkNodeVisualizerBase.h"
#include "inet/visualizer/osg/scene/NetworkNodeOsgVisualization.h"

namespace inet {

namespace visualizer {

class INET_API NetworkNodeOsgVisualizer : public NetworkNodeVisualizerBase
{
  protected:
    bool displayModuleName;
    std::map<const cModule *, osg::ref_ptr<NetworkNodeOsgVisualization>> networkNodeVisualizations;

  protected:
    virtual void initialize(int stage) override;
    virtual void refreshDisplay() const override;

    virtual NetworkNodeOsgVisualization *createNetworkNodeVisualization(cModule *networkNode) const override;
    virtual void addNetworkNodeVisualization(NetworkNodeVisualization *networkNodeVisualization) override;
    virtual void removeNetworkNodeVisualization(NetworkNodeVisualization *networkNodeVisualization) override;
    virtual void destroyNetworkNodeVisualization(NetworkNodeVisualization *networkNodeVisualization) override {}

  public:
    virtual ~NetworkNodeOsgVisualizer();
    virtual NetworkNodeOsgVisualization *getNetworkNodeVisualization(const cModule *networkNode) const override;
};

} // namespace visualizer

} // namespace inet

#endif


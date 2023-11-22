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

#ifndef __INET_TRANSPORTCONNECTIONOSGVISUALIZER_H
#define __INET_TRANSPORTCONNECTIONOSGVISUALIZER_H

#include "inet/common/ModuleRefByPar.h"
#include "inet/visualizer/base/TransportConnectionVisualizerBase.h"
#include "inet/visualizer/osg/scene/NetworkNodeOsgVisualizer.h"

namespace inet {

namespace visualizer {

class INET_API TransportConnectionOsgVisualizer : public TransportConnectionVisualizerBase
{
  protected:
    class INET_API TransportConnectionOsgVisualization : public TransportConnectionVisualization {
      public:
        osg::Node *sourceNode = nullptr;
        osg::Node *destinationNode = nullptr;

      public:
        TransportConnectionOsgVisualization(osg::Node *sourceNode, osg::Node *destinationNode, int sourceModuleId, int destinationModuleId, int count);
    };

  protected:
    ModuleRefByPar<NetworkNodeOsgVisualizer> networkNodeVisualizer;

  protected:
    virtual void initialize(int stage) override;

    virtual osg::Node *createConnectionEndNode(tcp::TcpConnection *connectionVisualization) const;
    virtual const TransportConnectionVisualization *createConnectionVisualization(cModule *source, cModule *destination, tcp::TcpConnection *tcpConnection) const override;
    virtual void addConnectionVisualization(const TransportConnectionVisualization *connectionVisualization) override;
    virtual void removeConnectionVisualization(const TransportConnectionVisualization *connectionVisualization) override;
};

} // namespace visualizer

} // namespace inet

#endif


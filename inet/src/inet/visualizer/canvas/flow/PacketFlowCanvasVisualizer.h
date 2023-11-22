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

#ifndef __INET_PACKETFLOWCANVASVISUALIZER_H
#define __INET_PACKETFLOWCANVASVISUALIZER_H

#include "inet/visualizer/canvas/base/PathCanvasVisualizerBase.h"

namespace inet {

namespace visualizer {

class INET_API PacketFlowCanvasVisualizer : public PathCanvasVisualizerBase
{
  protected:
    virtual bool isPathStart(cModule *module) const override;
    virtual bool isPathEnd(cModule *module) const override;
    virtual bool isPathElement(cModule *module) const override;

    virtual const PathVisualization *createPathVisualization(const char *label, const std::vector<int>& path, cPacket *packet) const override;

    virtual void processPathElement(cModule *networkNode, const char *label, Packet *packet) override;
};

} // namespace visualizer

} // namespace inet

#endif


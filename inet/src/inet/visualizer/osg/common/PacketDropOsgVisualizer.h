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

#ifndef __INET_PACKETDROPOSGVISUALIZER_H
#define __INET_PACKETDROPOSGVISUALIZER_H

#include <osg/ref_ptr>

#include "inet/visualizer/base/PacketDropVisualizerBase.h"

namespace inet {

namespace visualizer {

class INET_API PacketDropOsgVisualizer : public PacketDropVisualizerBase
{
  protected:
    class INET_API PacketDropOsgVisualization : public PacketDropVisualization {
      public:
        osg::ref_ptr<osg::Node> node;

      public:
        PacketDropOsgVisualization(osg::Node *node, const PacketDrop *packetDrop);
    };

  protected:
    virtual void refreshDisplay() const override;

    virtual const PacketDropVisualization *createPacketDropVisualization(PacketDrop *packetDrop) const override;
    virtual void addPacketDropVisualization(const PacketDropVisualization *packetDropVisualization) override;
    virtual void removePacketDropVisualization(const PacketDropVisualization *packetDropVisualization) override;
    virtual void setAlpha(const PacketDropVisualization *packetDropVisualization, double alpha) const override;
};

} // namespace visualizer

} // namespace inet

#endif


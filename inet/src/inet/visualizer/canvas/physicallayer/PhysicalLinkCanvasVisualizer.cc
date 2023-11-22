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

#include "inet/visualizer/canvas/physicallayer/PhysicalLinkCanvasVisualizer.h"

#include "inet/physicallayer/wireless/common/contract/packetlevel/IRadio.h"

namespace inet {

namespace visualizer {

Define_Module(PhysicalLinkCanvasVisualizer);

bool PhysicalLinkCanvasVisualizer::isLinkStart(cModule *module) const
{
    return dynamic_cast<inet::physicallayer::IRadio *>(module) != nullptr;
}

bool PhysicalLinkCanvasVisualizer::isLinkEnd(cModule *module) const
{
    return dynamic_cast<inet::physicallayer::IRadio *>(module) != nullptr;
}

const LinkVisualizerBase::LinkVisualization *PhysicalLinkCanvasVisualizer::createLinkVisualization(cModule *source, cModule *destination, cPacket *packet) const
{
    auto linkVisualization = static_cast<const LinkCanvasVisualization *>(LinkCanvasVisualizerBase::createLinkVisualization(source, destination, packet));
    linkVisualization->figure->setTags((std::string("physical_link ") + tags).c_str());
    linkVisualization->figure->setTooltip("This arrow represents a physical link between two network nodes");
    linkVisualization->shiftPriority = 1;
    return linkVisualization;
}

} // namespace visualizer

} // namespace inet


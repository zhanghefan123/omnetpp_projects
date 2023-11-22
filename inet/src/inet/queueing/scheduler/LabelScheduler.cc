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

#include "inet/queueing/scheduler/LabelScheduler.h"

#include "inet/queueing/common/LabelsTag_m.h"

namespace inet {
namespace queueing {

Define_Module(LabelScheduler);

void LabelScheduler::initialize(int stage)
{
    PacketSchedulerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        defaultGateIndex = par("defaultGateIndex");
        labels = cStringTokenizer(par("labels")).asVector();
        for (auto provider : providers)
            collections.push_back(dynamic_cast<IPacketCollection *>(provider));
    }
}

int LabelScheduler::getNumPackets() const
{
    int size = 0;
    for (auto collection : collections)
        size += collection->getNumPackets();
    return size;
}

b LabelScheduler::getTotalLength() const
{
    b totalLength(0);
    for (auto collection : collections)
        totalLength += collection->getTotalLength();
    return totalLength;
}

Packet *LabelScheduler::getPacket(int index) const
{
    throw cRuntimeError("TODO");
}

void LabelScheduler::removePacket(Packet *packet)
{
    throw cRuntimeError("TODO");
}

int LabelScheduler::schedulePacket()
{
    for (auto label : labels) {
        for (int i = 0; i < (int)providers.size(); i++) {
            auto packet = providers[i]->canPullPacket(inputGates[i]->getPathStartGate());
            const auto& labelsTag = packet->findTag<LabelsTag>();
            if (labelsTag != nullptr) {
                for (int j = 0; j < (int)labelsTag->getLabelsArraySize(); j++)
                    if (label == labelsTag->getLabels(j))
                        return i;
            }
        }
    }
    return defaultGateIndex;
}

} // namespace queueing
} // namespace inet


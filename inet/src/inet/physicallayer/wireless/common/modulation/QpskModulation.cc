//
// Copyright (C) 2014 OpenSim Ltd.
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

#include "inet/physicallayer/wireless/common/modulation/QpskModulation.h"

namespace inet {

namespace physicallayer {

const double k = 1 / sqrt(2);

const std::vector<ApskSymbol> QpskModulation::constellation = {
    k * ApskSymbol(-1, -1), k * ApskSymbol(1, -1), k * ApskSymbol(-1, 1), k * ApskSymbol(1, 1)
};

const QpskModulation QpskModulation::singleton;

QpskModulation::QpskModulation() : MqamModulationBase(k ,&constellation)
{
}

} // namespace physicallayer

} // namespace inet


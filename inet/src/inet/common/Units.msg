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

import inet.common.INETDefs;

cplusplus{{
#include "inet/common/Units.h"
}}

namespace inet;

cplusplus{{
using namespace units::values;
}}

//namespace inet::units::values;

class b    { @existingClass; @primitive; @fromString(b(string2long($)));      @toString(unit2string($)); @defaultValue(b(-1));     @toValue(cValue($.get(),"b"));   @fromValue(b($.intValueInUnit("b"))); }
class B    { @existingClass; @primitive; @fromString(B(string2long($)));      @toString(unit2string($)); @defaultValue(B(-1));     @toValue(cValue($.get(),"B"));   @fromValue(B($.intValueInUnit("B"))); }
class bps  { @existingClass; @primitive; @fromString(bps(string2double($)));  @toString(unit2string($)); @defaultValue(bps(NaN));  @toValue(cValue($.get(),"bps")); @fromValue(bps($.doubleValueInUnit("bps"))); }
class Hz   { @existingClass; @primitive; @fromString(Hz(string2double($)));   @toString(unit2string($)); @defaultValue(Hz(NaN));   @toValue(cValue($.get(),"Hz"));  @fromValue(Hz($.doubleValueInUnit("Hz"))); }
class m    { @existingClass; @primitive; @fromString(m(string2double($)));    @toString(unit2string($)); @defaultValue(m(NaN));    @toValue(cValue($.get(),"m"));   @fromValue(m($.doubleValueInUnit("m"))); }
class Ohmm { @existingClass; @primitive; @fromString(Ohmm(string2double($))); @toString(unit2string($)); @defaultValue(Ohmm(NaN)); @toValue(cValue($.get(),"Ohm")); @fromValue(Ohm($.doubleValueInUnit("Ohm"))); }
class rad  { @existingClass; @primitive; @fromString(rad(string2double($)));  @toString(unit2string($)); @defaultValue(rad(NaN));  @toValue(cValue($.get(),"rad")); @fromValue(rad($.doubleValueInUnit("rad"))); }
class W    { @existingClass; @primitive; @fromString(W(string2double($)));    @toString(unit2string($)); @defaultValue(W(NaN));    @toValue(cValue($.get(),"W"));   @fromValue(W($.doubleValueInUnit("W"))); }


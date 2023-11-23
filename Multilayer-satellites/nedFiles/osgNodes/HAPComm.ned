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
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package nedFiles.osgNodes;

import inet.node.inet.StandardHost;
import inet.routing.contract.IOspf;

module HAPComm extends StandardHost
{
    parameters:
        @display("i=misc/drone");     
        string mobilityType = default("HAPMobility"); // Define mobility module              
        bool hasOspf = default(false);
        *.routingTableModule = default("^.ipv4.routingTable");
      submodules:
        ospf: <"Ospfv2"> like IOspf if hasOspf {
            parameters:
        }
     connections allowunconnected:
        ospf.ipOut --> tn.in++ if hasOspf;
        ospf.ipIn <-- tn.out++ if hasOspf;
}

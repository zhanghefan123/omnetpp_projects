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

import nedFiles.osgNodes.SatHost;
import inet.applications.contract.IApp;
import inet.routing.contract.IOspf;
import inet.projects.dtn_network.dtn_module.dtn;
import inet.projects.dtn_network.dtn_module.DtnTraffic;

module LipsinSatellite extends SatHost
{
    parameters:
        @display("i=device/satellite_vl");
        @figure[submodules];
        forwarding = true;
        bool hasOspf = default(false);
        *.routingTableModule = default("^.ipv4.routingTable");
    submodules:
        ospf: <default("Ospfv2")> like IOspf if hasOspf {
            parameters:
                @display("p=975,226");
        }

    connections allowunconnected:
        ospf.ipOut --> tn.in++ if hasOspf;
        ospf.ipIn <-- tn.out++ if hasOspf;
}


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

package inet.projects.lipsin.lipsin_module;

import inet.networklayer.contract.INetworkLayer;
import inet.projects.lipsin.lipsin_forwarder.LipsinForwarder;
import inet.projects.lipsin.lipsin_table.LipsinLinkTable;
module LipsinNetworkLayer like INetworkLayer
{
    @display("bgb=427,230");
    gates:
        input transportIn;
        output transportOut;
        input ifIn;
        output ifOut;
    submodules:
        forwarder: LipsinForwarder {
            @display("p=203,105");
        }
        plt: LipsinLinkTable {
            @display("i=block/table;is=s;p=63,31");
        }

        vlt: LipsinLinkTable {
            @display("i=block/table;is=s;p=63,105");
        }

        dlt: LipsinLinkTable {
            @display("i=block/table;is=s;p=63,185");
        }
    connections:
        transportIn --> { @display("m=n"); } --> forwarder.transportIn;
        transportOut <-- { @display("m=n"); } <-- forwarder.transportOut;
        forwarder.queueIn <-- { @display("m=s"); } <-- ifIn;
        forwarder.queueOut --> { @display("m=s"); } --> ifOut;
}

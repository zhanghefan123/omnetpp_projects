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

package inet.projects.lipsin.lipsin_node;

import inet.node.inet.Router;
import inet.projects.lipsin.lipsin_app.LipsinSender;
import inet.projects.lipsin.lipsin_app.LipsinServer;
import inet.projects.lipsin.lipsin_app.LipsinReceiver;
import inet.projects.lipsin.lipsin_table.LinkInfoTable;
import inet.projects.lipsin.lipsin_table.LipsinRoutingTable;
import inet.projects.lipsin.lipsin_config.LipsinRouteConfigurator;
module LipsinRouter extends Router
{
    parameters:
        int lidIncrease = default(0);
        xml lipsinConfig = default(xml("<LinksConfig></LinksConfig>"));
        bool hasLipsinSender = default(false);
        bool hasLipsinServer = default(false);
        bool hasLipsinReceiver = default(false);
        hasLipsin = true;
        @display("bgb=1813.896,821.044");
    submodules:
        lipsinSender: LipsinSender if hasLipsinSender {
            @display("p=1112.9125,222.5825");
        }
        lipsinServer: LipsinServer if hasLipsinServer {
            @display("p=824.46375,222.5825");
        }
        lipsinReceiver: LipsinReceiver if hasLipsinReceiver {
            @display("p=974.3663,222.5825");
        }
        linkInfoTable: LinkInfoTable if hasLipsin {
            @display("i=block/table;is=s;p=1471.77,74.95125");
        }
        lipsinRoutingTable: LipsinRoutingTable if hasLipsin {
            @display("i=block/table;p=1471.77,374.75626;is=s");
        }
        lipsinRouteConfigurator: LipsinRouteConfigurator if hasLipsin {

            @display("p=1471.77,524.65875;is=s");
        }
    connections:
        lipsinSender.appOut --> tn.in++ if hasLipsinSender;
        lipsinSender.appIn <-- tn.out++ if hasLipsinSender;
        lipsinServer.appOut --> tn.in++ if hasLipsinServer;
        lipsinServer.appIn <-- tn.out++ if hasLipsinServer;
        lipsinReceiver.appOut --> tn.in++ if hasLipsinReceiver;
        lipsinReceiver.appIn <-- tn.out++ if hasLipsinReceiver;
}

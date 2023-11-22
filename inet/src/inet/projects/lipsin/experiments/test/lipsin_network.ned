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

package inet.projects.lipsin.experiments.test;
import inet.common.misc.ThruputMeteringChannel;
import inet.projects.lipsin.lipsin_node.LipsinRouter;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
network lipsin
{
    @display("bgb=878,624");
    types:
        channel LINK_100 extends ThruputMeteringChannel
        {
            parameters:
                delay = 50us;
                datarate = 100Mbps;
                displayAsTooltip = true;
                thruputDisplayFormat = "#N";
        }
    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=307,95;is=s");
        }
        SAT0: LipsinRouter {
            parameters:
                @display("p=254,33");
            gates:
                ethg[2];
        }
        SAT1: LipsinRouter {
            parameters:
                @display("p=150,50");
            gates:
                ethg[2];
        }
        SAT2: LipsinRouter {
            parameters:
                @display("p=111,112");
            gates:
                ethg[2];
        }
        SAT3: LipsinRouter {
            parameters:
                @display("p=85,170");
            gates:
                ethg[2];
        }
        SAT4: LipsinRouter {
            parameters:
                @display("p=72,238");
            gates:
                ethg[2];
        }
        SAT5: LipsinRouter {
            parameters:
                @display("p=72,298");
            gates:
                ethg[2];
        }
        SAT6: LipsinRouter {
            parameters:
                @display("p=178,329");
            gates:
                ethg[2];
        }
        SAT7: LipsinRouter {
            parameters:
                @display("p=299,306");
            gates:
                ethg[2];
        }
        SAT8: LipsinRouter {
            parameters:
                @display("p=364,238");
            gates:
                ethg[2];
        }
        SAT9: LipsinRouter {
            parameters:
                @display("p=403,151");
            gates:
                ethg[2];
        }
        SAT10: LipsinRouter {
            parameters:
                @display("p=364,73");
            gates:
                ethg[2];
        }
    connections:
        SAT0.ethg[0] <--> LINK_100 <--> SAT1.ethg[0];
        SAT1.ethg[1] <--> LINK_100 <--> SAT2.ethg[0];
        SAT2.ethg[1] <--> LINK_100 <--> SAT3.ethg[0];
        SAT3.ethg[1] <--> LINK_100 <--> SAT4.ethg[0];
        SAT4.ethg[1] <--> LINK_100 <--> SAT5.ethg[0];
        SAT5.ethg[1] <--> LINK_100 <--> SAT6.ethg[0];
        SAT6.ethg[1] <--> LINK_100 <--> SAT7.ethg[0];
        SAT7.ethg[1] <--> LINK_100 <--> SAT8.ethg[0];
        SAT8.ethg[1] <--> LINK_100 <--> SAT9.ethg[0];
        SAT9.ethg[1] <--> LINK_100 <--> SAT10.ethg[0];
        SAT10.ethg[1] <--> LINK_100 <--> SAT0.ethg[1];
}

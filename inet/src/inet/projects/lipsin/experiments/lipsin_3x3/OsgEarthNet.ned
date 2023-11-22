package inet.projects.lipsin.experiments.lipsin_3x3;

import inet.projects.lipsin.lipsin_node.LipsinSatellite;
import inet.common.misc.ThruputMeteringChannel;
import inet.node.ospfv2.OspfRouter;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.inet.StandardHost;
import inet.common.scenario.ScenarioManager;


network OsgEarthNet
{
    parameters:
        int rngNum = default(0);
        double sendInterval = default(1);
        @display("bgb=684,423");
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
        scenarioManager: ScenarioManager;

        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=50,150");
                config = xml("<config><interface among='**' address='10.x.x.x' netmask='255.255.255.252'/></config>");
                addStaticRoutes = false;
                addDefaultRoutes = false;
        }
        SAT0: LipsinSatellite {
            parameters:
                @display("p=160,39");
            gates:
                ethg[3];
        }
        SAT1: LipsinSatellite {
            parameters:
                @display("p=95,190");
            gates:
                ethg[3];
        }
        SAT2: LipsinSatellite {
            parameters:
                @display("p=160,351");
            gates:
                ethg[3];
        }
        SAT3: LipsinSatellite {
            parameters:
                @display("p=359,39");
            gates:
                ethg[4];
        }
        SAT4: LipsinSatellite {
            parameters:
                @display("p=290,190");
            gates:
                ethg[4];
        }
        SAT5: LipsinSatellite {
            parameters:
                @display("p=359,351");
            gates:
                ethg[4];
        }
        SAT6: LipsinSatellite {
            parameters:
                @display("p=549,39");
            gates:
                ethg[3];
        }
        SAT7: LipsinSatellite {
            parameters:
                @display("p=456,190");
            gates:
                ethg[3];
        }
        SAT8: LipsinSatellite {
            parameters:
                @display("p=549,351");
            gates:
                ethg[3];
        }
    connections:
        SAT0.ethg[0] <--> LINK_100 <--> SAT1.ethg[0];
        SAT0.ethg[1] <--> LINK_100 <--> SAT3.ethg[0];
        SAT1.ethg[1] <--> LINK_100 <--> SAT2.ethg[0];
        SAT1.ethg[2] <--> LINK_100 <--> SAT4.ethg[0];
        SAT2.ethg[1] <--> LINK_100 <--> SAT0.ethg[2];
        SAT2.ethg[2] <--> LINK_100 <--> SAT5.ethg[0];
        SAT3.ethg[1] <--> LINK_100 <--> SAT4.ethg[1];
        SAT3.ethg[2] <--> LINK_100 <--> SAT6.ethg[0];
        SAT4.ethg[2] <--> LINK_100 <--> SAT5.ethg[1];
        SAT4.ethg[3] <--> LINK_100 <--> SAT7.ethg[0];
        SAT5.ethg[2] <--> LINK_100 <--> SAT3.ethg[3];
        SAT5.ethg[3] <--> LINK_100 <--> SAT8.ethg[0];
        SAT6.ethg[1] <--> LINK_100 <--> SAT7.ethg[1];
        SAT7.ethg[2] <--> LINK_100 <--> SAT8.ethg[1];
        SAT8.ethg[2] <--> LINK_100 <--> SAT6.ethg[2];
}

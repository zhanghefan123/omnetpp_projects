package inet.projects.lipsin.experiments.lipsin_4x4;
import inet.projects.lipsin.lipsin_node.LipsinSatellite;
import inet.common.misc.ThruputMeteringChannel;
import inet.node.ospfv2.OspfRouter;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.inet.StandardHost;
import inet.common.scenario.ScenarioManager;
import inet.projects.lipsin.lipsin_global_recorder.LipsinGlobalRecorder;
network OsgEarthNet
{
    parameters:
        int rngNum = default(0);
        double sendInterval = default(1);
        @display("bgb=868,446");
    types:
        channel LINK_100 extends ThruputMeteringChannel
        {
            parameters:
                delay = 50ms;
                datarate = 10Mbps;
                displayAsTooltip = true;
                thruputDisplayFormat = "#N";
        }
    submodules:
        scenarioManager: ScenarioManager;
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=79.57,154.78");
                config = xml("<config><interface among='**' address='10.x.x.x' netmask='255.255.255.252'/></config>");
                addStaticRoutes = false;
                addDefaultRoutes = false;
        }
        lipsinGlobalRecorder: LipsinGlobalRecorder {
            parameters:
            	@display("p=79.57,256.15");
            	satelliteNum = 16;
        }
        SAT0: LipsinSatellite {
            parameters:
                @display("p=153.69,54.5");
            gates:
                ethg[3];
        }
        SAT1: LipsinSatellite {
            parameters:
                @display("p=202.74,154.78");
            gates:
                ethg[3];
        }
        SAT2: LipsinSatellite {
            parameters:
                @display("p=202.74,263.78");
            gates:
                ethg[3];
        }
        SAT3: LipsinSatellite {
            parameters:
                @display("p=153.69,356.43");
            gates:
                ethg[3];
        }
        SAT4: LipsinSatellite {
            parameters:
                @display("p=333.54,54.5");
            gates:
                ethg[4];
        }
        SAT5: LipsinSatellite {
            parameters:
                @display("p=390.22,154.78");
            gates:
                ethg[4];
        }
        SAT6: LipsinSatellite {
            parameters:
                @display("p=390.22,263.78");
            gates:
                ethg[4];
        }
        SAT7: LipsinSatellite {
            parameters:
                @display("p=333.54,356.43");
            gates:
                ethg[4];
        }
        SAT8: LipsinSatellite {
            parameters:
                @display("p=516.66003,54.5");
            gates:
                ethg[4];
        }
        SAT9: LipsinSatellite {
            parameters:
                @display("p=583.15,155.87001");
            gates:
                ethg[4];
        }
        SAT10: LipsinSatellite {
            parameters:
                @display("p=583.15,263.78");
            gates:
                ethg[4];
        }
        SAT11: LipsinSatellite {
            parameters:
                @display("p=516.66003,352.07");
            gates:
                ethg[4];
        }
        SAT12: LipsinSatellite {
            parameters:
                @display("p=650.73004,54.5");
            gates:
                ethg[3];
        }
        SAT13: LipsinSatellite {
            parameters:
                @display("p=734.66003,155.87001");
            gates:
                ethg[3];
        }
        SAT14: LipsinSatellite {
            parameters:
                @display("p=734.66003,263.78");
            gates:
                ethg[3];
        }
        SAT15: LipsinSatellite {
            parameters:
                @display("p=650.73004,357.52002");
            gates:
                ethg[3];
        }
    connections:
        SAT0.ethg[0] <--> LINK_100 <--> SAT1.ethg[0];
        SAT0.ethg[1] <--> LINK_100 <--> SAT4.ethg[0];
        SAT1.ethg[1] <--> LINK_100 <--> SAT2.ethg[0];
        SAT1.ethg[2] <--> LINK_100 <--> SAT5.ethg[0];
        SAT2.ethg[1] <--> LINK_100 <--> SAT3.ethg[0];
        SAT2.ethg[2] <--> LINK_100 <--> SAT6.ethg[0];
        SAT3.ethg[1] <--> LINK_100 <--> SAT0.ethg[2];
        SAT3.ethg[2] <--> LINK_100 <--> SAT7.ethg[0];
        SAT4.ethg[1] <--> LINK_100 <--> SAT5.ethg[1];
        SAT4.ethg[2] <--> LINK_100 <--> SAT8.ethg[0];
        SAT5.ethg[2] <--> LINK_100 <--> SAT6.ethg[1];
        SAT5.ethg[3] <--> LINK_100 <--> SAT9.ethg[0];
        SAT6.ethg[2] <--> LINK_100 <--> SAT7.ethg[1];
        SAT6.ethg[3] <--> LINK_100 <--> SAT10.ethg[0];
        SAT7.ethg[2] <--> LINK_100 <--> SAT4.ethg[3];
        SAT7.ethg[3] <--> LINK_100 <--> SAT11.ethg[0];
        SAT8.ethg[1] <--> LINK_100 <--> SAT9.ethg[1];
        SAT8.ethg[2] <--> LINK_100 <--> SAT12.ethg[0];
        SAT9.ethg[2] <--> LINK_100 <--> SAT10.ethg[1];
        SAT9.ethg[3] <--> LINK_100 <--> SAT13.ethg[0];
        SAT10.ethg[2] <--> LINK_100 <--> SAT11.ethg[1];
        SAT10.ethg[3] <--> LINK_100 <--> SAT14.ethg[0];
        SAT11.ethg[2] <--> LINK_100 <--> SAT8.ethg[3];
        SAT11.ethg[3] <--> LINK_100 <--> SAT15.ethg[0];
        SAT12.ethg[1] <--> LINK_100 <--> SAT13.ethg[1];
        SAT13.ethg[2] <--> LINK_100 <--> SAT14.ethg[1];
        SAT14.ethg[2] <--> LINK_100 <--> SAT15.ethg[1];
        SAT15.ethg[2] <--> LINK_100 <--> SAT12.ethg[2];
}

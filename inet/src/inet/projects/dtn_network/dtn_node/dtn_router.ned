
package inet.projects.dtn_network.dtn_node;

import inet.node.base.ApplicationLayerNodeBase;
import inet.projects.dtn_network.dtn_module.dtn;
import inet.projects.dtn_network.dtn_module.DtnTraffic;

// Dtn Router has a dtn module and a dtn traffic generator
module DtnRouter extends ApplicationLayerNodeBase
{
    parameters:
        @display("i=device/pc2");
        @figure[submodules];
        forwarding = default(false);  // disable routing by default
        ipv4.arp.proxyArpInterfaces = default(""); // proxy arp is disabled on hosts by default
        *.routingTableModule = default("^.ipv4.routingTable");
    submodules:
        dtn: dtn {
            @display("p=878.86395,224.672");
        }
        dtnTraffic: DtnTraffic {
            @display("p=997.808,224.672");
        }
    connections:
        dtn.ipOut --> tn.in++;  // copy the move of ospfv2
        dtn.ipIn <-- tn.out++; // copy the move of ospfv2
}

package inet.projects.sr.sr_module;
import inet.networklayer.contract.INetworkLayer;
import inet.projects.sr.sr_forwarder.SRForwarder;

module SRNetworkLayer like INetworkLayer
{
    @display("bgb=427,230");
    gates:
        input transportIn;
        output transportOut;
        input ifIn;
        output ifOut;
    submodules:
        forwarder: SRForwarder {
            @display("p=203,105");
        }
    connections:
        transportIn --> { @display("m=n"); } --> forwarder.transportIn;
        transportOut <-- { @display("m=n"); } <-- forwarder.transportOut;
        forwarder.queueIn <-- { @display("m=s"); } <-- ifIn;
        forwarder.queueOut --> { @display("m=s"); } --> ifOut;
}
package inet.projects.dtn_network.dtn_module;
// this is a simple module in omnetpp for traffic generation
simple DtnTraffic{
	parameters:
	    string destAddress = default(""); // destination ip address
	    volatile double sendInterval @unit(s) = default(0.5s); // packet send interval
	    double startTime @unit(s) = default(0s); // start time
	    double stopTime @unit(s) = default(0s); // we only need to set the stop time if we want to send packets
}
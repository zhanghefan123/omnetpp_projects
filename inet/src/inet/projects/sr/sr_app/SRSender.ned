package inet.projects.sr.sr_app;

simple SRSender {
    parameters:
        double startTime = default(-1);
        double stopTime = default(-1);
        double sendInterval = default(1);
        int packetLength = default(1024);
        int destinationSatelliteId = default(-1);
    gates:
        input appIn;
        output appOut;
}
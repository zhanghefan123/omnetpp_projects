//
// This program is property of its copyright holder. All rights reserved.
//
package nedFiles.channels;


import inet.common.misc.ThruputMeteringChannel;

//
// This channels adds support for thruput metering to the datarate channel.
// A cDatarateChannel extended with throughput calculation. Values
// are displayed on the link, using the connection's "t=" or "tt=" display
// string tag.
//
// The display can be customized with the "thruputDisplayFormat" parameter.
// In the format string, the following characters will get expanded:
//   - 'N': number of packets
//   - 'V': volume (in bytes)
//   - 'p': current packet/sec
//   - 'b': current bandwidth
//   - 'u': current channel utilization (%)
//   - 'P': average packet/sec on [0,now)
//   - 'B': average bandwidth on [0,now)
//   - 'U': average channel utilization (%) on [0,now)
//
// Other characters are copied verbatim.
//
// "Current" actually means the last measurement interval, which is
// 10 packets or 0.1s, whichever comes first.
//
channel SatToSat extends ThruputMeteringChannel
{
	parameters:
    	@class(SatToSat);
}

channel SatToSat_10Mbps extends SatToSat{
    datarate = 10Mbps;
}

channel SatToSat_100Mbps extends SatToSat{
    datarate = 100Mbps;
}

channel SatToSat_1Gbps extends SatToSat{
    datarate = 1Gbps;
}
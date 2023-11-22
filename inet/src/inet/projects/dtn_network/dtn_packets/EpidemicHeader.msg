
import inet.common.packet.chunk.Chunk;
import inet.networklayer.contract.ipv4.Ipv4Address;
import inet.projects.dtn_network.dtn_packets.TimeRecorder;
namespace inet;

// define the const variable
cplusplus {{
	const B EPIDEMIC_HEADER_LENGTH = B(6);
}}

class EpidemicHeader extends FieldsChunk {
    short type; // packet type
    string uuid; // uuid used to uniquely identify the packet
    bool neighborAck;
    int msgIdLength;
    string msgIds[];
    Ipv4Address destAddr; // we need to store the destIp
    TimeRecorder* startTime; // the time when the packet is generated
}

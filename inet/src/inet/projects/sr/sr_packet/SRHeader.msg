import inet.common.packet.chunk.Chunk;

namespace inet;

cplusplus{{
	const B SR_HEADER_LENGTH = B(10); // SR 头部长度 (后续可以更改)
}}

class SRHeader extends FieldsChunk{
    chunkLength = SR_HEADER_LENGTH;   // SR 头部长度 (后续可以更改)
    int source_node_id;               // 源节点 id
    int destination_node_id;          // 目的节点 id
    int sid_index;                    // 当前sid索引
    int sids[];                       // sid 列表
    double packet_created_time;       // 数据包构建的时间
}
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

cplusplus{{
    #include "inet/projects/lipsin/lipsin_packets/BloomFilter.h"
}}

import inet.common.packet.chunk.Chunk;
import inet.projects.lipsin.lipsin_packets.BloomFilter;
import inet.projects.lipsin.lipsin_packets.PathHeader;


namespace inet;

// following code will be inserted into namespace inet {}
cplusplus{{
	const B LIPSIN_HEADER_LENGTH = B(10); // length of the LIPSIN HEADER // send packet size = 1000 + 14(mac header) + 4(mac tail) + 10(LIPSIN_HEADER) + 8(front) = 1036 without ip header
}}


class LipsinHeader extends FieldsChunk{
	chunkLength = LIPSIN_HEADER_LENGTH;
    int packetType;
    int neighborSatelliteId;
    string uuid;
    uint64_t nonce;
	BloomFilter *realLidsBf;
    BloomFilter *virtualLidsBf;
	PathHeader *pathHeader;
    string source;
    int intermediateNode;
    int destinationList[];
    double packetCreatedTime;
    double propagationDelay;
    double transmissionDelay;
    bool wrongDirection;
    int hopCount;
}

cplusplus(LipsinHeader){{
public:
    BloomFilter* getRealLidsBfNonConst() {return this->realLidsBf;}
    BloomFilter* getVirtualLidsBfNonConst() {return this->virtualLidsBf;}
    PathHeader* getPathHeaderNonConst() {return this->pathHeader;}
}};
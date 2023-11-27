//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/projects/lipsin/lipsin_packets/LipsinHeader.msg.
//

#ifndef __INET_LIPSINHEADER_M_H
#define __INET_LIPSINHEADER_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

class LipsinHeader;

}  // namespace inet

// cplusplus {{
    #include "inet/projects/lipsin/lipsin_packets/BloomFilter.h"
// }}

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/projects/lipsin/lipsin_packets/BloomFilter_m.h" // import inet.projects.lipsin.lipsin_packets.BloomFilter

#include "inet/projects/lipsin/lipsin_packets/PathHeader_m.h" // import inet.projects.lipsin.lipsin_packets.PathHeader


namespace inet {

// cplusplus {{
	const B LIPSIN_HEADER_LENGTH = B(10); // length of the LIPSIN HEADER // send packet size = 1000 + 14(mac header) + 4(mac tail) + 10(LIPSIN_HEADER) + 8(front) = 1036 without ip header
// }}

/**
 * Class generated from <tt>inet/projects/lipsin/lipsin_packets/LipsinHeader.msg:33</tt> by opp_msgtool.
 * <pre>
 * class LipsinHeader extends FieldsChunk
 * {
 *     chunkLength = LIPSIN_HEADER_LENGTH;
 *     int packetType;
 *     int neighborSatelliteId;
 *     string uuid;
 *     uint64_t nonce;
 *     BloomFilter *realLidsBf;
 *     BloomFilter *virtualLidsBf;
 *     PathHeader *pathHeader;
 *     string source;
 *     int intermediateNode;
 *     int destinationList[];
 *     double packetCreatedTime;
 *     double propagationDelay;
 *     double transmissionDelay;
 *     bool wrongDirection;
 *     int hopCount;
 * }
 * </pre>
 */
class INET_API LipsinHeader : public ::inet::FieldsChunk
{
  protected:
    int packetType = 0;
    int neighborSatelliteId = 0;
    ::omnetpp::opp_string uuid;
    uint64_t nonce = 0;
    BloomFilter * realLidsBf = nullptr;
    BloomFilter * virtualLidsBf = nullptr;
    PathHeader * pathHeader = nullptr;
    ::omnetpp::opp_string source;
    int intermediateNode = 0;
    int *destinationList = nullptr;
    size_t destinationList_arraysize = 0;
    double packetCreatedTime = 0;
    double propagationDelay = 0;
    double transmissionDelay = 0;
    bool wrongDirection = false;
    int hopCount = 0;

  private:
    void copy(const LipsinHeader& other);

  protected:
    bool operator==(const LipsinHeader&) = delete;

  public:
    LipsinHeader();
    LipsinHeader(const LipsinHeader& other);
    virtual ~LipsinHeader();
    LipsinHeader& operator=(const LipsinHeader& other);
    virtual LipsinHeader *dup() const override {return new LipsinHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getPacketType() const;
    virtual void setPacketType(int packetType);

    virtual int getNeighborSatelliteId() const;
    virtual void setNeighborSatelliteId(int neighborSatelliteId);

    virtual const char * getUuid() const;
    virtual void setUuid(const char * uuid);

    virtual uint64_t getNonce() const;
    virtual void setNonce(uint64_t nonce);

    virtual const BloomFilter * getRealLidsBf() const;
    virtual BloomFilter * getRealLidsBfForUpdate() { handleChange();return const_cast<BloomFilter *>(const_cast<LipsinHeader*>(this)->getRealLidsBf());}
    virtual void setRealLidsBf(BloomFilter * realLidsBf);

    virtual const BloomFilter * getVirtualLidsBf() const;
    virtual BloomFilter * getVirtualLidsBfForUpdate() { handleChange();return const_cast<BloomFilter *>(const_cast<LipsinHeader*>(this)->getVirtualLidsBf());}
    virtual void setVirtualLidsBf(BloomFilter * virtualLidsBf);

    virtual const PathHeader * getPathHeader() const;
    virtual PathHeader * getPathHeaderForUpdate() { handleChange();return const_cast<PathHeader *>(const_cast<LipsinHeader*>(this)->getPathHeader());}
    virtual void setPathHeader(PathHeader * pathHeader);

    virtual const char * getSource() const;
    virtual void setSource(const char * source);

    virtual int getIntermediateNode() const;
    virtual void setIntermediateNode(int intermediateNode);

    virtual void setDestinationListArraySize(size_t size);
    virtual size_t getDestinationListArraySize() const;
    virtual int getDestinationList(size_t k) const;
    virtual void setDestinationList(size_t k, int destinationList);
    virtual void insertDestinationList(size_t k, int destinationList);
    [[deprecated]] void insertDestinationList(int destinationList) {appendDestinationList(destinationList);}
    virtual void appendDestinationList(int destinationList);
    virtual void eraseDestinationList(size_t k);

    virtual double getPacketCreatedTime() const;
    virtual void setPacketCreatedTime(double packetCreatedTime);

    virtual double getPropagationDelay() const;
    virtual void setPropagationDelay(double propagationDelay);

    virtual double getTransmissionDelay() const;
    virtual void setTransmissionDelay(double transmissionDelay);

    virtual bool getWrongDirection() const;
    virtual void setWrongDirection(bool wrongDirection);

    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);


public:
    BloomFilter* getRealLidsBfNonConst() {return this->realLidsBf;}
    BloomFilter* getVirtualLidsBfNonConst() {return this->virtualLidsBf;}
    PathHeader* getPathHeaderNonConst() {return this->pathHeader;}
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LipsinHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LipsinHeader& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::LipsinHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::LipsinHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_LIPSINHEADER_M_H


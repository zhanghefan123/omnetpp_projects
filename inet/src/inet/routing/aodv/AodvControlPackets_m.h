//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/aodv/AodvControlPackets.msg.
//

#ifndef __INET__AODV_AODVCONTROLPACKETS_M_H
#define __INET__AODV_AODVCONTROLPACKETS_M_H

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
namespace aodv {

class AodvControlPacket;
class Rreq;
class Rrep;
struct UnreachableNode;
class Rerr;
class RrepAck;
class WaitForRrep;
class PacketHolderMessage;

}  // namespace aodv
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/common/packet/Packet_m.h" // import inet.common.packet.Packet

#include "inet/networklayer/common/L3Address_m.h" // import inet.networklayer.common.L3Address


namespace inet {
namespace aodv {

/**
 * Enum generated from <tt>inet/routing/aodv/AodvControlPackets.msg:26</tt> by opp_msgtool.
 * <pre>
 * enum AodvControlPacketType
 * {
 *     RREQ = 1;
 *     RREP = 2;
 *     RERR = 3;
 *     RREPACK = 4;
 *     RREQ_IPv6 = 16;
 *     RREP_IPv6 = 17;
 *     RERR_IPv6 = 18;
 *     RREPACK_IPv6 = 19;
 * }
 * </pre>
 */
enum AodvControlPacketType {
    RREQ = 1,
    RREP = 2,
    RERR = 3,
    RREPACK = 4,
    RREQ_IPv6 = 16,
    RREP_IPv6 = 17,
    RERR_IPv6 = 18,
    RREPACK_IPv6 = 19
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AodvControlPacketType& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AodvControlPacketType& e) { int n; b->unpack(n); e = static_cast<AodvControlPacketType>(n); }

/**
 * Class generated from <tt>inet/routing/aodv/AodvControlPackets.msg:41</tt> by opp_msgtool.
 * <pre>
 * //
 * // Base packet for AODV Control Packets
 * //
 * class AodvControlPacket extends FieldsChunk
 * {
 *     AodvControlPacketType packetType = static_cast<AodvControlPacketType>(-1);       // packet type, stored in one byte
 * }
 * </pre>
 */
class INET_API AodvControlPacket : public ::inet::FieldsChunk
{
  protected:
    AodvControlPacketType packetType = static_cast<AodvControlPacketType>(-1);

  private:
    void copy(const AodvControlPacket& other);

  protected:
    bool operator==(const AodvControlPacket&) = delete;

  public:
    AodvControlPacket();
    AodvControlPacket(const AodvControlPacket& other);
    virtual ~AodvControlPacket();
    AodvControlPacket& operator=(const AodvControlPacket& other);
    virtual AodvControlPacket *dup() const override {return new AodvControlPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual AodvControlPacketType getPacketType() const;
    virtual void setPacketType(AodvControlPacketType packetType);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AodvControlPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AodvControlPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/aodv/AodvControlPackets.msg:49</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents an AODV Route Request
 * //
 * class Rreq extends AodvControlPacket
 * {
 *     // chunkLength = B(24) or B(48)
 *     // packetType = RREQ or RREQ_IPv6
 *     bool joinFlag;    // Join flag; reserved for multicast.
 *     bool repairFlag;    // Repair flag; reserved for multicast.
 *     bool gratuitousRREPFlag;    // Gratuitous RREP flag; indicates whether a gratuitous RREP should be unicast to the node specified in the Destination IP Address field
 *     bool destOnlyFlag;    // Destination only flag; indicates only the destination may respond to this RREQ
 *     bool unknownSeqNumFlag;    // Unknown sequence number; indicates the destination sequence number is unknown
 *     uint16_t reserved = 0;    // Sent as 0; ignored on reception.
 *     unsigned int hopCount;    // The number of hops from the Originator IP Address to the node handling the request.
 *     uint32_t rreqId;    // A sequence number uniquely identifying the particular RREQ when taken in conjunction with the originating node's IP address.
 *     L3Address destAddr;    // The IP address of the destination for which a route is desired.
 *     uint32_t destSeqNum;    // The latest sequence number received in the past by the originator for any route towards the destination.
 *     L3Address originatorAddr;    // The IP address of the node which originated the Route Request.
 *     uint32_t originatorSeqNum;    // The current sequence number to be used in the route entry pointing towards the originator of the route request.
 * }
 * </pre>
 */
class INET_API Rreq : public ::inet::aodv::AodvControlPacket
{
  protected:
    bool joinFlag = false;
    bool repairFlag = false;
    bool gratuitousRREPFlag = false;
    bool destOnlyFlag = false;
    bool unknownSeqNumFlag = false;
    uint16_t reserved = 0;
    unsigned int hopCount = 0;
    uint32_t rreqId = 0;
    ::inet::L3Address destAddr;
    uint32_t destSeqNum = 0;
    ::inet::L3Address originatorAddr;
    uint32_t originatorSeqNum = 0;

  private:
    void copy(const Rreq& other);

  protected:
    bool operator==(const Rreq&) = delete;

  public:
    Rreq();
    Rreq(const Rreq& other);
    virtual ~Rreq();
    Rreq& operator=(const Rreq& other);
    virtual Rreq *dup() const override {return new Rreq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getJoinFlag() const;
    virtual void setJoinFlag(bool joinFlag);

    virtual bool getRepairFlag() const;
    virtual void setRepairFlag(bool repairFlag);

    virtual bool getGratuitousRREPFlag() const;
    virtual void setGratuitousRREPFlag(bool gratuitousRREPFlag);

    virtual bool getDestOnlyFlag() const;
    virtual void setDestOnlyFlag(bool destOnlyFlag);

    virtual bool getUnknownSeqNumFlag() const;
    virtual void setUnknownSeqNumFlag(bool unknownSeqNumFlag);

    virtual uint16_t getReserved() const;
    virtual void setReserved(uint16_t reserved);

    virtual unsigned int getHopCount() const;
    virtual void setHopCount(unsigned int hopCount);

    virtual uint32_t getRreqId() const;
    virtual void setRreqId(uint32_t rreqId);

    virtual const ::inet::L3Address& getDestAddr() const;
    virtual ::inet::L3Address& getDestAddrForUpdate() { handleChange();return const_cast<::inet::L3Address&>(const_cast<Rreq*>(this)->getDestAddr());}
    virtual void setDestAddr(const ::inet::L3Address& destAddr);

    virtual uint32_t getDestSeqNum() const;
    virtual void setDestSeqNum(uint32_t destSeqNum);

    virtual const ::inet::L3Address& getOriginatorAddr() const;
    virtual ::inet::L3Address& getOriginatorAddrForUpdate() { handleChange();return const_cast<::inet::L3Address&>(const_cast<Rreq*>(this)->getOriginatorAddr());}
    virtual void setOriginatorAddr(const ::inet::L3Address& originatorAddr);

    virtual uint32_t getOriginatorSeqNum() const;
    virtual void setOriginatorSeqNum(uint32_t originatorSeqNum);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Rreq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Rreq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/aodv/AodvControlPackets.msg:70</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents an AODV Route Reply
 * //
 * class Rrep extends AodvControlPacket
 * {
 *     // chunkLength = B(20) or B(44)
 *     // packetType = RREP or RREP_IPv6
 *     bool repairFlag;    // Repair flag; used for multicast.
 *     bool ackRequiredFlag;    // Acknowledgment required.
 *     uint16_t reserved = 0;    // Sent as 0; ignored on reception.
 *     unsigned int prefixSize;    // If nonzero, the 5-bit Prefix Size specifies that the indicated next hop may be used for any nodes with the same routing prefix (as defined by the Prefix Size) as the requested destination.
 *     unsigned int hopCount;    // The number of hops from the Originator IP Address to the Destination IP Address.  For multicast route requests this indicates the number of hops to the multicast tree member sending the RREP.
 *     L3Address destAddr;    // The IP address of the destination for which a route is supplied.
 *     uint32_t destSeqNum;    // The destination sequence number associated to the route.
 *     L3Address originatorAddr;    // The IP address of the node which originated the RREQ for which the route is supplied.
 *     simtime_t lifeTime;     // The time in milliseconds for which nodes receiving the RREP consider the route to be valid.
 * }
 * </pre>
 */
class INET_API Rrep : public ::inet::aodv::AodvControlPacket
{
  protected:
    bool repairFlag = false;
    bool ackRequiredFlag = false;
    uint16_t reserved = 0;
    unsigned int prefixSize = 0;
    unsigned int hopCount = 0;
    ::inet::L3Address destAddr;
    uint32_t destSeqNum = 0;
    ::inet::L3Address originatorAddr;
    ::omnetpp::simtime_t lifeTime = SIMTIME_ZERO;

  private:
    void copy(const Rrep& other);

  protected:
    bool operator==(const Rrep&) = delete;

  public:
    Rrep();
    Rrep(const Rrep& other);
    virtual ~Rrep();
    Rrep& operator=(const Rrep& other);
    virtual Rrep *dup() const override {return new Rrep(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getRepairFlag() const;
    virtual void setRepairFlag(bool repairFlag);

    virtual bool getAckRequiredFlag() const;
    virtual void setAckRequiredFlag(bool ackRequiredFlag);

    virtual uint16_t getReserved() const;
    virtual void setReserved(uint16_t reserved);

    virtual unsigned int getPrefixSize() const;
    virtual void setPrefixSize(unsigned int prefixSize);

    virtual unsigned int getHopCount() const;
    virtual void setHopCount(unsigned int hopCount);

    virtual const ::inet::L3Address& getDestAddr() const;
    virtual ::inet::L3Address& getDestAddrForUpdate() { handleChange();return const_cast<::inet::L3Address&>(const_cast<Rrep*>(this)->getDestAddr());}
    virtual void setDestAddr(const ::inet::L3Address& destAddr);

    virtual uint32_t getDestSeqNum() const;
    virtual void setDestSeqNum(uint32_t destSeqNum);

    virtual const ::inet::L3Address& getOriginatorAddr() const;
    virtual ::inet::L3Address& getOriginatorAddrForUpdate() { handleChange();return const_cast<::inet::L3Address&>(const_cast<Rrep*>(this)->getOriginatorAddr());}
    virtual void setOriginatorAddr(const ::inet::L3Address& originatorAddr);

    virtual ::omnetpp::simtime_t getLifeTime() const;
    virtual void setLifeTime(::omnetpp::simtime_t lifeTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Rrep& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Rrep& obj) {obj.parsimUnpack(b);}

/**
 * Struct generated from inet/routing/aodv/AodvControlPackets.msg:88 by opp_msgtool.
 */
struct INET_API UnreachableNode
{
    UnreachableNode();
    ::inet::L3Address addr;
    uint32_t seqNum = 0;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const UnreachableNode& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, UnreachableNode& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const UnreachableNode& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, UnreachableNode& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>inet/routing/aodv/AodvControlPackets.msg:97</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents an AODV Route Error
 * //
 * class Rerr extends AodvControlPacket
 * {
 *     // chunkLength = B(4 + N * (4+4)) or B(4 + N * (4+16))
 *     // packetType = RERR or RERR_IPv6
 *     bool noDeleteFlag;    // No delete flag; set when a node has performed a local repair of a link, and upstream nodes should not delete the route.
 *     uint16_t reserved = 0;    // Sent as 0; ignored on reception.
 *     UnreachableNode unreachableNodes[];    // The unreachable destinations included in the message; MUST be at least 1.
 * }
 * </pre>
 */
class INET_API Rerr : public ::inet::aodv::AodvControlPacket
{
  protected:
    bool noDeleteFlag = false;
    uint16_t reserved = 0;
    UnreachableNode *unreachableNodes = nullptr;
    size_t unreachableNodes_arraysize = 0;

  private:
    void copy(const Rerr& other);

  protected:
    bool operator==(const Rerr&) = delete;

  public:
    Rerr();
    Rerr(const Rerr& other);
    virtual ~Rerr();
    Rerr& operator=(const Rerr& other);
    virtual Rerr *dup() const override {return new Rerr(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getNoDeleteFlag() const;
    virtual void setNoDeleteFlag(bool noDeleteFlag);

    virtual uint16_t getReserved() const;
    virtual void setReserved(uint16_t reserved);

    virtual void setUnreachableNodesArraySize(size_t size);
    virtual size_t getUnreachableNodesArraySize() const;
    virtual const UnreachableNode& getUnreachableNodes(size_t k) const;
    virtual UnreachableNode& getUnreachableNodesForUpdate(size_t k) { handleChange();return const_cast<UnreachableNode&>(const_cast<Rerr*>(this)->getUnreachableNodes(k));}
    virtual void setUnreachableNodes(size_t k, const UnreachableNode& unreachableNodes);
    virtual void insertUnreachableNodes(size_t k, const UnreachableNode& unreachableNodes);
    [[deprecated]] void insertUnreachableNodes(const UnreachableNode& unreachableNodes) {appendUnreachableNodes(unreachableNodes);}
    virtual void appendUnreachableNodes(const UnreachableNode& unreachableNodes);
    virtual void eraseUnreachableNodes(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Rerr& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Rerr& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/aodv/AodvControlPackets.msg:109</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents an AODV Route Reply ACK
 * //
 * class RrepAck extends AodvControlPacket
 * {
 *     chunkLength = B(2);
 *     // packetType = RREPACK or RREPACK_IPv6
 *     uint8_t reserved = 0;
 * }
 * </pre>
 */
class INET_API RrepAck : public ::inet::aodv::AodvControlPacket
{
  protected:
    uint8_t reserved = 0;

  private:
    void copy(const RrepAck& other);

  protected:
    bool operator==(const RrepAck&) = delete;

  public:
    RrepAck();
    RrepAck(const RrepAck& other);
    virtual ~RrepAck();
    RrepAck& operator=(const RrepAck& other);
    virtual RrepAck *dup() const override {return new RrepAck(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint8_t getReserved() const;
    virtual void setReserved(uint8_t reserved);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RrepAck& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RrepAck& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/aodv/AodvControlPackets.msg:119</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents an internal timer for a Route Reply packet in Aodv module
 * //
 * message WaitForRrep
 * {
 *     L3Address destAddr;
 *     unsigned int lastTTL;
 *     bool fromInvalidEntry;
 * }
 * </pre>
 */
class INET_API WaitForRrep : public ::omnetpp::cMessage
{
  protected:
    ::inet::L3Address destAddr;
    unsigned int lastTTL = 0;
    bool fromInvalidEntry = false;

  private:
    void copy(const WaitForRrep& other);

  protected:
    bool operator==(const WaitForRrep&) = delete;

  public:
    WaitForRrep(const char *name=nullptr, short kind=0);
    WaitForRrep(const WaitForRrep& other);
    virtual ~WaitForRrep();
    WaitForRrep& operator=(const WaitForRrep& other);
    virtual WaitForRrep *dup() const override {return new WaitForRrep(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const ::inet::L3Address& getDestAddr() const;
    virtual ::inet::L3Address& getDestAddrForUpdate() { return const_cast<::inet::L3Address&>(const_cast<WaitForRrep*>(this)->getDestAddr());}
    virtual void setDestAddr(const ::inet::L3Address& destAddr);

    virtual unsigned int getLastTTL() const;
    virtual void setLastTTL(unsigned int lastTTL);

    virtual bool getFromInvalidEntry() const;
    virtual void setFromInvalidEntry(bool fromInvalidEntry);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const WaitForRrep& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, WaitForRrep& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/aodv/AodvControlPackets.msg:129</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents a timer for delayed sending
 * //
 * message PacketHolderMessage
 * {
 *     Packet *ownedPacket \@owned;
 * }
 * </pre>
 */
class INET_API PacketHolderMessage : public ::omnetpp::cMessage
{
  protected:
    ::inet::Packet * ownedPacket = nullptr;

  private:
    void copy(const PacketHolderMessage& other);

  protected:
    bool operator==(const PacketHolderMessage&) = delete;

  public:
    PacketHolderMessage(const char *name=nullptr, short kind=0);
    PacketHolderMessage(const PacketHolderMessage& other);
    virtual ~PacketHolderMessage();
    PacketHolderMessage& operator=(const PacketHolderMessage& other);
    virtual PacketHolderMessage *dup() const override {return new PacketHolderMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const ::inet::Packet * getOwnedPacket() const;
    virtual ::inet::Packet * getOwnedPacketForUpdate() { return const_cast<::inet::Packet *>(const_cast<PacketHolderMessage*>(this)->getOwnedPacket());}
    virtual void setOwnedPacket(::inet::Packet * ownedPacket);
    virtual ::inet::Packet * removeOwnedPacket();
    [[deprecated]] ::inet::Packet * dropOwnedPacket() {return removeOwnedPacket();}


#if (OMNETPP_BUILDNUM < 1530)
  public:
    Packet * removeOwnedPacket() { return dropOwnedPacket(); }
#endif
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PacketHolderMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PacketHolderMessage& obj) {obj.parsimUnpack(b);}


}  // namespace aodv
}  // namespace inet


namespace omnetpp {

template<> inline inet::aodv::AodvControlPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::aodv::AodvControlPacket*>(ptr.get<cObject>()); }
template<> inline inet::aodv::Rreq *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::aodv::Rreq*>(ptr.get<cObject>()); }
template<> inline inet::aodv::Rrep *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::aodv::Rrep*>(ptr.get<cObject>()); }
inline any_ptr toAnyPtr(const inet::aodv::UnreachableNode *p) {return any_ptr(p);}
template<> inline inet::aodv::UnreachableNode *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::aodv::UnreachableNode>(); }
template<> inline inet::aodv::Rerr *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::aodv::Rerr*>(ptr.get<cObject>()); }
template<> inline inet::aodv::RrepAck *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::aodv::RrepAck*>(ptr.get<cObject>()); }
template<> inline inet::aodv::WaitForRrep *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::aodv::WaitForRrep*>(ptr.get<cObject>()); }
template<> inline inet::aodv::PacketHolderMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::aodv::PacketHolderMessage*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET__AODV_AODVCONTROLPACKETS_M_H


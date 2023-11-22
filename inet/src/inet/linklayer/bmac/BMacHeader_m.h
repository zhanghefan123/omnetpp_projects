//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/bmac/BMacHeader.msg.
//

#ifndef __INET_BMACHEADER_M_H
#define __INET_BMACHEADER_M_H

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

class BMacHeaderBase;
class BMacControlFrame;
class BMacDataFrameHeader;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress


namespace inet {

/**
 * Enum generated from <tt>inet/linklayer/bmac/BMacHeader.msg:26</tt> by opp_msgtool.
 * <pre>
 * // \@brief Types of messages (self messages and packets) the node can process
 * //TODO split to 2 enums: for packets / for self messages
 * enum BMacType
 * {
 *     // packet types
 *     BMAC_PREAMBLE = 191;
 *     BMAC_DATA = 192;
 *     BMAC_ACK = 193;
 *     // self message types
 *     BMAC_RESEND_DATA = 194;
 *     BMAC_ACK_TIMEOUT = 195;
 *     BMAC_START_BMAC = 196;
 *     BMAC_WAKE_UP = 197;
 *     BMAC_SEND_ACK = 198;
 *     BMAC_CCA_TIMEOUT = 199;
 *     BMAC_ACK_TX_OVER = 200;
 *     BMAC_SEND_PREAMBLE = 201;
 *     BMAC_STOP_PREAMBLES = 202;
 *     BMAC_DATA_TX_OVER = 203;
 *     BMAC_DATA_TIMEOUT = 204;
 * }
 * </pre>
 */
enum BMacType {
    BMAC_PREAMBLE = 191,
    BMAC_DATA = 192,
    BMAC_ACK = 193,
    BMAC_RESEND_DATA = 194,
    BMAC_ACK_TIMEOUT = 195,
    BMAC_START_BMAC = 196,
    BMAC_WAKE_UP = 197,
    BMAC_SEND_ACK = 198,
    BMAC_CCA_TIMEOUT = 199,
    BMAC_ACK_TX_OVER = 200,
    BMAC_SEND_PREAMBLE = 201,
    BMAC_STOP_PREAMBLES = 202,
    BMAC_DATA_TX_OVER = 203,
    BMAC_DATA_TIMEOUT = 204
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BMacType& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BMacType& e) { int n; b->unpack(n); e = static_cast<BMacType>(n); }

/**
 * Class generated from <tt>inet/linklayer/bmac/BMacHeader.msg:49</tt> by opp_msgtool.
 * <pre>
 * //
 * // Base class for ~BMac headers.
 * //
 * class BMacHeaderBase extends FieldsChunk
 * {
 *     MacAddress srcAddr;
 *     MacAddress destAddr;
 *     BMacType type;
 * }
 * </pre>
 */
class INET_API BMacHeaderBase : public ::inet::FieldsChunk
{
  protected:
    MacAddress srcAddr;
    MacAddress destAddr;
    BMacType type = static_cast<inet::BMacType>(-1);

  private:
    void copy(const BMacHeaderBase& other);

  protected:
    bool operator==(const BMacHeaderBase&) = delete;

  public:
    BMacHeaderBase();
    BMacHeaderBase(const BMacHeaderBase& other);
    virtual ~BMacHeaderBase();
    BMacHeaderBase& operator=(const BMacHeaderBase& other);
    virtual BMacHeaderBase *dup() const override {return new BMacHeaderBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const MacAddress& getSrcAddr() const;
    virtual MacAddress& getSrcAddrForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<BMacHeaderBase*>(this)->getSrcAddr());}
    virtual void setSrcAddr(const MacAddress& srcAddr);

    virtual const MacAddress& getDestAddr() const;
    virtual MacAddress& getDestAddrForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<BMacHeaderBase*>(this)->getDestAddr());}
    virtual void setDestAddr(const MacAddress& destAddr);

    virtual BMacType getType() const;
    virtual void setType(BMacType type);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BMacHeaderBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BMacHeaderBase& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/bmac/BMacHeader.msg:60</tt> by opp_msgtool.
 * <pre>
 * //
 * // Control Frame for ~BMac. Frame size is configurable
 * // in the MAC layer.
 * //
 * class BMacControlFrame extends BMacHeaderBase
 * {
 * }
 * </pre>
 */
class INET_API BMacControlFrame : public ::inet::BMacHeaderBase
{
  protected:

  private:
    void copy(const BMacControlFrame& other);

  protected:
    bool operator==(const BMacControlFrame&) = delete;

  public:
    BMacControlFrame();
    BMacControlFrame(const BMacControlFrame& other);
    virtual ~BMacControlFrame();
    BMacControlFrame& operator=(const BMacControlFrame& other);
    virtual BMacControlFrame *dup() const override {return new BMacControlFrame(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BMacControlFrame& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BMacControlFrame& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/linklayer/bmac/BMacHeader.msg:68</tt> by opp_msgtool.
 * <pre>
 * //
 * // Dataframe header for ~BMac. Frame size is configurable
 * // in the MAC layer.
 * //
 * class BMacDataFrameHeader extends BMacHeaderBase
 * {
 *     long sequenceId; // Sequence Number to detect duplicate messages
 *     int networkProtocol = -1;
 * }
 * </pre>
 */
class INET_API BMacDataFrameHeader : public ::inet::BMacHeaderBase
{
  protected:
    long sequenceId = 0;
    int networkProtocol = -1;

  private:
    void copy(const BMacDataFrameHeader& other);

  protected:
    bool operator==(const BMacDataFrameHeader&) = delete;

  public:
    BMacDataFrameHeader();
    BMacDataFrameHeader(const BMacDataFrameHeader& other);
    virtual ~BMacDataFrameHeader();
    BMacDataFrameHeader& operator=(const BMacDataFrameHeader& other);
    virtual BMacDataFrameHeader *dup() const override {return new BMacDataFrameHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual long getSequenceId() const;
    virtual void setSequenceId(long sequenceId);

    virtual int getNetworkProtocol() const;
    virtual void setNetworkProtocol(int networkProtocol);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const BMacDataFrameHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, BMacDataFrameHeader& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::BMacHeaderBase *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::BMacHeaderBase*>(ptr.get<cObject>()); }
template<> inline inet::BMacControlFrame *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::BMacControlFrame*>(ptr.get<cObject>()); }
template<> inline inet::BMacDataFrameHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::BMacDataFrameHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_BMACHEADER_M_H


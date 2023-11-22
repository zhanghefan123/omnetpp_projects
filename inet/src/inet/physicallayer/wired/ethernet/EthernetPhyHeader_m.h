//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wired/ethernet/EthernetPhyHeader.msg.
//

#ifndef __INET__PHYSICALLAYER_ETHERNETPHYHEADER_M_H
#define __INET__PHYSICALLAYER_ETHERNETPHYHEADER_M_H

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
namespace physicallayer {

class EthernetPhyHeaderBase;
class EthernetPhyHeader;
class EthernetFragmentPhyHeader;

}  // namespace physicallayer
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {
namespace physicallayer {

/**
 * Class generated from <tt>inet/physicallayer/wired/ethernet/EthernetPhyHeader.msg:28</tt> by opp_msgtool.
 * <pre>
 * //
 * // This is a base class for all IEEE 802.3 Ethernet PHY headers defined the IEEE
 * // Std 802.3-2018, IEEE Standard for Ethernet.
 * //
 * class EthernetPhyHeaderBase extends FieldsChunk
 * {
 *     chunkLength = B(8);
 * }
 * </pre>
 */
class INET_API EthernetPhyHeaderBase : public ::inet::FieldsChunk
{
  protected:

  private:
    void copy(const EthernetPhyHeaderBase& other);

  protected:
    bool operator==(const EthernetPhyHeaderBase&) = delete;

  public:
    EthernetPhyHeaderBase();
    EthernetPhyHeaderBase(const EthernetPhyHeaderBase& other);
    virtual ~EthernetPhyHeaderBase();
    EthernetPhyHeaderBase& operator=(const EthernetPhyHeaderBase& other);
    virtual EthernetPhyHeaderBase *dup() const override {return new EthernetPhyHeaderBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetPhyHeaderBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetPhyHeaderBase& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/wired/ethernet/EthernetPhyHeader.msg:45</tt> by opp_msgtool.
 * <pre>
 * //
 * // This class represents an Ethernet PHY header as defined in the IEEE Std
 * // 802.3-2018, IEEE Standard for Ethernet.
 * //
 * //  0                   1                   2                   3
 * //  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * // +---------------------------------------------------------------+
 * // |                        Preamble (0x55)                        |
 * // +                                               +---------------+
 * // |                                               |      SFD      |
 * // +-----------------------------------------------+---------------+
 * //
 * class EthernetPhyHeader extends EthernetPhyHeaderBase
 * {
 * }
 * </pre>
 */
class INET_API EthernetPhyHeader : public ::inet::physicallayer::EthernetPhyHeaderBase
{
  protected:

  private:
    void copy(const EthernetPhyHeader& other);

  protected:
    bool operator==(const EthernetPhyHeader&) = delete;

  public:
    EthernetPhyHeader();
    EthernetPhyHeader(const EthernetPhyHeader& other);
    virtual ~EthernetPhyHeader();
    EthernetPhyHeader& operator=(const EthernetPhyHeader& other);
    virtual EthernetPhyHeader *dup() const override {return new EthernetPhyHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetPhyHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetPhyHeader& obj) {obj.parsimUnpack(b);}

/**
 * Enum generated from <tt>inet/physicallayer/wired/ethernet/EthernetPhyHeader.msg:51</tt> by opp_msgtool.
 * <pre>
 * //
 * // http://www.enodenetworks.com/assets/docs/8023br.pdf
 * //
 * enum EthernetPhyHeaderType
 * {
 *     SFD = 1;         // 0xD5
 *     SMD_E = SFD;
 *     SMD_Verify = 2;  // 0x07
 *     SMD_Respond = 3; // 0x19
 *     SMD_Sx = 4;      // 0xE6, 0x4C, 0x7F or 0xB3, see smdNumber in EthernetPhyHeader
 *     SMD_Cx = 5;      // 0x61, 0x52, 0x9E or 0x2A, see smdNumber in EthernetPhyHeader
 * }
 * </pre>
 */
enum EthernetPhyHeaderType {
    SFD = 1,
    SMD_E = SFD,
    SMD_Verify = 2,
    SMD_Respond = 3,
    SMD_Sx = 4,
    SMD_Cx = 5
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetPhyHeaderType& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetPhyHeaderType& e) { int n; b->unpack(n); e = static_cast<EthernetPhyHeaderType>(n); }

/**
 * Class generated from <tt>inet/physicallayer/wired/ethernet/EthernetPhyHeader.msg:81</tt> by opp_msgtool.
 * <pre>
 * //
 * // This class represents an Ethernet fragment PHY header as defined in the IEEE
 * // Std 802.3-2018, IEEE Standard for Ethernet.
 * //
 * //  0                   1                   2                   3
 * //  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * // +---------------------------------------------------------------+
 * // |                        Preamble (0x55)                        |
 * // +                                               +---------------+
 * // |                                               |     SMD-Sx    |
 * // +-----------------------------------------------+---------------+
 * //
 * //  0                   1                   2                   3
 * //  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * // +---------------------------------------------------------------+
 * // |                        Preamble (0x55)                        |
 * // +                               +---------------+---------------+
 * // |                               |     SMD-Cx    |   FragNumber  |
 * // +-------------------------------+---------------+---------------+
 * //
 * class EthernetFragmentPhyHeader extends EthernetPhyHeaderBase
 * {
 *     EthernetPhyHeaderType preambleType = SFD;
 *     uint8_t smdNumber = 0;       // 0-3, see SMD_Sx or SMD_Cx
 *     uint8_t fragmentNumber = 0;  // 0-3 (real fragment number modulo 4)
 * }
 * </pre>
 */
class INET_API EthernetFragmentPhyHeader : public ::inet::physicallayer::EthernetPhyHeaderBase
{
  protected:
    EthernetPhyHeaderType preambleType = SFD;
    uint8_t smdNumber = 0;
    uint8_t fragmentNumber = 0;

  private:
    void copy(const EthernetFragmentPhyHeader& other);

  protected:
    bool operator==(const EthernetFragmentPhyHeader&) = delete;

  public:
    EthernetFragmentPhyHeader();
    EthernetFragmentPhyHeader(const EthernetFragmentPhyHeader& other);
    virtual ~EthernetFragmentPhyHeader();
    EthernetFragmentPhyHeader& operator=(const EthernetFragmentPhyHeader& other);
    virtual EthernetFragmentPhyHeader *dup() const override {return new EthernetFragmentPhyHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual EthernetPhyHeaderType getPreambleType() const;
    virtual void setPreambleType(EthernetPhyHeaderType preambleType);

    virtual uint8_t getSmdNumber() const;
    virtual void setSmdNumber(uint8_t smdNumber);

    virtual uint8_t getFragmentNumber() const;
    virtual void setFragmentNumber(uint8_t fragmentNumber);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetFragmentPhyHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetFragmentPhyHeader& obj) {obj.parsimUnpack(b);}


}  // namespace physicallayer
}  // namespace inet


namespace omnetpp {

template<> inline inet::physicallayer::EthernetPhyHeaderBase *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::EthernetPhyHeaderBase*>(ptr.get<cObject>()); }
template<> inline inet::physicallayer::EthernetPhyHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::EthernetPhyHeader*>(ptr.get<cObject>()); }
template<> inline inet::physicallayer::EthernetFragmentPhyHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::EthernetFragmentPhyHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET__PHYSICALLAYER_ETHERNETPHYHEADER_M_H


//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/ieee802/Ieee802EpdHeader.msg.
//

#ifndef __INET_IEEE802EPDHEADER_M_H
#define __INET_IEEE802EPDHEADER_M_H

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

class Ieee802EpdHeader;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/linklayer/ieee802/Ieee802EpdHeader.msg:31</tt> by opp_msgtool.
 * <pre>
 * //
 * // This class represents an IEEE 802 EtherType Protocol Discrimination (EPD)
 * // header as defined in the section 9.2 EtherTypes of the IEEE Std 802-2014,
 * // IEEE Standard for Local and Metropolitan Area Networks: Overview and
 * // Architecture.
 * //
 * class Ieee802EpdHeader extends FieldsChunk
 * {
 *     chunkLength = B(2);
 *     uint16_t etherType; // Protocol identification values are assigned by the IEEE RA 19 and are used to identify the protocol that is to be invoked to process the user data in the frame.
 * }
 * </pre>
 */
class INET_API Ieee802EpdHeader : public ::inet::FieldsChunk
{
  protected:
    uint16_t etherType = 0;

  private:
    void copy(const Ieee802EpdHeader& other);

  protected:
    bool operator==(const Ieee802EpdHeader&) = delete;

  public:
    Ieee802EpdHeader();
    Ieee802EpdHeader(const Ieee802EpdHeader& other);
    virtual ~Ieee802EpdHeader();
    Ieee802EpdHeader& operator=(const Ieee802EpdHeader& other);
    virtual Ieee802EpdHeader *dup() const override {return new Ieee802EpdHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint16_t getEtherType() const;
    virtual void setEtherType(uint16_t etherType);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ieee802EpdHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ieee802EpdHeader& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::Ieee802EpdHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ieee802EpdHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_IEEE802EPDHEADER_M_H


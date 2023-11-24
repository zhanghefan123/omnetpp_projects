//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wireless/unitdisk/UnitDiskPhyHeader.msg.
//

#ifndef __INET_UNITDISKPHYHEADER_M_H
#define __INET_UNITDISKPHYHEADER_M_H

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

class UnitDiskPhyHeader;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Protocol_m.h" // import inet.common.Protocol

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

/**
 * Class generated from <tt>inet/physicallayer/wireless/unitdisk/UnitDiskPhyHeader.msg:25</tt> by opp_msgtool.
 * <pre>
 * class UnitDiskPhyHeader extends FieldsChunk
 * {
 *     const Protocol *payloadProtocol \@toString("->str()") = nullptr; // specifies a protocol (internal class with an artificial identifier)
 * }
 * </pre>
 */
class INET_API UnitDiskPhyHeader : public ::inet::FieldsChunk
{
  protected:
    const Protocol * payloadProtocol = nullptr;

  private:
    void copy(const UnitDiskPhyHeader& other);

  protected:
    bool operator==(const UnitDiskPhyHeader&) = delete;

  public:
    UnitDiskPhyHeader();
    UnitDiskPhyHeader(const UnitDiskPhyHeader& other);
    virtual ~UnitDiskPhyHeader();
    UnitDiskPhyHeader& operator=(const UnitDiskPhyHeader& other);
    virtual UnitDiskPhyHeader *dup() const override {return new UnitDiskPhyHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const Protocol * getPayloadProtocol() const;
    virtual void setPayloadProtocol(const Protocol * payloadProtocol);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const UnitDiskPhyHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, UnitDiskPhyHeader& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::UnitDiskPhyHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::UnitDiskPhyHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_UNITDISKPHYHEADER_M_H


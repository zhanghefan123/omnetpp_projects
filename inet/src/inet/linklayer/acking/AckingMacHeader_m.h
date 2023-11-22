//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/linklayer/acking/AckingMacHeader.msg.
//

#ifndef __INET_ACKINGMACHEADER_M_H
#define __INET_ACKINGMACHEADER_M_H

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

class AckingMacHeader;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress


namespace inet {

/**
 * Class generated from <tt>inet/linklayer/acking/AckingMacHeader.msg:29</tt> by opp_msgtool.
 * <pre>
 * //
 * // Packet for ~AckingMac. Packet size is configurable
 * // in the MAC layer.
 * //
 * class AckingMacHeader extends FieldsChunk
 * {
 *     MacAddress src;     // source address
 *     MacAddress dest;    // destination address
 *     int srcModuleId;    // technical data, uses instead of sending back an ACK packet
 *     int networkProtocol = -1;
 * }
 * </pre>
 */
class INET_API AckingMacHeader : public ::inet::FieldsChunk
{
  protected:
    MacAddress src;
    MacAddress dest;
    int srcModuleId = 0;
    int networkProtocol = -1;

  private:
    void copy(const AckingMacHeader& other);

  protected:
    bool operator==(const AckingMacHeader&) = delete;

  public:
    AckingMacHeader();
    AckingMacHeader(const AckingMacHeader& other);
    virtual ~AckingMacHeader();
    AckingMacHeader& operator=(const AckingMacHeader& other);
    virtual AckingMacHeader *dup() const override {return new AckingMacHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const MacAddress& getSrc() const;
    virtual MacAddress& getSrcForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<AckingMacHeader*>(this)->getSrc());}
    virtual void setSrc(const MacAddress& src);

    virtual const MacAddress& getDest() const;
    virtual MacAddress& getDestForUpdate() { handleChange();return const_cast<MacAddress&>(const_cast<AckingMacHeader*>(this)->getDest());}
    virtual void setDest(const MacAddress& dest);

    virtual int getSrcModuleId() const;
    virtual void setSrcModuleId(int srcModuleId);

    virtual int getNetworkProtocol() const;
    virtual void setNetworkProtocol(int networkProtocol);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AckingMacHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AckingMacHeader& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::AckingMacHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::AckingMacHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_ACKINGMACHEADER_M_H

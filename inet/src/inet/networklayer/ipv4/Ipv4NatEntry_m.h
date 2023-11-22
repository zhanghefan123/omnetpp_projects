//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/ipv4/Ipv4NatEntry.msg.
//

#ifndef __INET_IPV4NATENTRY_M_H
#define __INET_IPV4NATENTRY_M_H

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

class Ipv4NatEntry;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/ipv4/Ipv4NatEntry.msg:24</tt> by opp_msgtool.
 * <pre>
 * class Ipv4NatEntry extends cObject
 * {
 *     Ipv4Address destAddress;
 *     int destPort = -1;
 *     Ipv4Address srcAddress;
 *     int srcPort = -1;
 * }
 * </pre>
 */
class INET_API Ipv4NatEntry : public ::omnetpp::cObject
{
  protected:
    Ipv4Address destAddress;
    int destPort = -1;
    Ipv4Address srcAddress;
    int srcPort = -1;

  private:
    void copy(const Ipv4NatEntry& other);

  protected:
    bool operator==(const Ipv4NatEntry&) = delete;

  public:
    Ipv4NatEntry();
    Ipv4NatEntry(const Ipv4NatEntry& other);
    virtual ~Ipv4NatEntry();
    Ipv4NatEntry& operator=(const Ipv4NatEntry& other);
    virtual Ipv4NatEntry *dup() const override {return new Ipv4NatEntry(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const Ipv4Address& getDestAddress() const;
    virtual Ipv4Address& getDestAddressForUpdate() { return const_cast<Ipv4Address&>(const_cast<Ipv4NatEntry*>(this)->getDestAddress());}
    virtual void setDestAddress(const Ipv4Address& destAddress);

    virtual int getDestPort() const;
    virtual void setDestPort(int destPort);

    virtual const Ipv4Address& getSrcAddress() const;
    virtual Ipv4Address& getSrcAddressForUpdate() { return const_cast<Ipv4Address&>(const_cast<Ipv4NatEntry*>(this)->getSrcAddress());}
    virtual void setSrcAddress(const Ipv4Address& srcAddress);

    virtual int getSrcPort() const;
    virtual void setSrcPort(int srcPort);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv4NatEntry& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv4NatEntry& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::Ipv4NatEntry *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv4NatEntry*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_IPV4NATENTRY_M_H


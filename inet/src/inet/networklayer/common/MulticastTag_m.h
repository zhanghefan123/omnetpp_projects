//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/common/MulticastTag.msg.
//

#ifndef __INET_MULTICASTTAG_M_H
#define __INET_MULTICASTTAG_M_H

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

class MulticastReq;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/TagBase_m.h" // import inet.common.TagBase


namespace inet {

/**
 * Class generated from <tt>inet/networklayer/common/MulticastTag.msg:27</tt> by opp_msgtool.
 * <pre>
 * //
 * // Determines the multicast loop mode
 * //
 * class MulticastReq extends TagBase
 * {
 *     bool multicastLoop = false;   // if true, sent multicast datagrams will be looped back
 * }
 * </pre>
 */
class INET_API MulticastReq : public ::inet::TagBase
{
  protected:
    bool multicastLoop = false;

  private:
    void copy(const MulticastReq& other);

  protected:
    bool operator==(const MulticastReq&) = delete;

  public:
    MulticastReq();
    MulticastReq(const MulticastReq& other);
    virtual ~MulticastReq();
    MulticastReq& operator=(const MulticastReq& other);
    virtual MulticastReq *dup() const override {return new MulticastReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getMulticastLoop() const;
    virtual void setMulticastLoop(bool multicastLoop);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MulticastReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MulticastReq& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::MulticastReq *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::MulticastReq*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_MULTICASTTAG_M_H


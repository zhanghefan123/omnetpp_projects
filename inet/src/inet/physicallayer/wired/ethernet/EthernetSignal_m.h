//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/physicallayer/wired/ethernet/EthernetSignal.msg.
//

#ifndef __INET__PHYSICALLAYER_ETHERNETSIGNAL_M_H
#define __INET__PHYSICALLAYER_ETHERNETSIGNAL_M_H

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

class EthernetSignalBase;
class EthernetSignal;
class EthernetJamSignal;
class EthernetFilledIfgSignal;

}  // namespace physicallayer
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/physicallayer/common/Signal_m.h" // import inet.physicallayer.common.Signal

// cplusplus {{
#include "inet/linklayer/ethernet/common/Ethernet.h"
// }}


namespace inet {
namespace physicallayer {

/**
 * Class generated from <tt>inet/physicallayer/wired/ethernet/EthernetSignal.msg:32</tt> by opp_msgtool.
 * <pre>
 * //
 * // Abstract base class for various Ethernet traffic types:
 * // EtherJam, EtherFilledIfg and EtherPhyFrame.
 * //
 * packet EthernetSignalBase extends Signal
 * {
 *     bool srcMacFullDuplex;  // meta-info, for detecting model misconfiguration
 *     double bitrate;  // meta-info, for detecting model misconfiguration
 * }
 * </pre>
 */
class INET_API EthernetSignalBase : public ::inet::physicallayer::Signal
{
  protected:
    bool srcMacFullDuplex = false;
    double bitrate = 0;

  private:
    void copy(const EthernetSignalBase& other);

  protected:
    bool operator==(const EthernetSignalBase&) = delete;

  public:
    EthernetSignalBase(const char *name=nullptr, short kind=0);
    EthernetSignalBase(const EthernetSignalBase& other);
    virtual ~EthernetSignalBase();
    EthernetSignalBase& operator=(const EthernetSignalBase& other);
    virtual EthernetSignalBase *dup() const override {return new EthernetSignalBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getSrcMacFullDuplex() const;
    virtual void setSrcMacFullDuplex(bool srcMacFullDuplex);

    virtual double getBitrate() const;
    virtual void setBitrate(double bitrate);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetSignalBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetSignalBase& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/wired/ethernet/EthernetSignal.msg:41</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents dataframe on the Ethernet.
 * //
 * packet EthernetSignal extends EthernetSignalBase
 * {
 * }
 * </pre>
 */
class INET_API EthernetSignal : public ::inet::physicallayer::EthernetSignalBase
{
  protected:

  private:
    void copy(const EthernetSignal& other);

  protected:
    bool operator==(const EthernetSignal&) = delete;

  public:
    EthernetSignal(const char *name=nullptr, short kind=0);
    EthernetSignal(const EthernetSignal& other);
    virtual ~EthernetSignal();
    EthernetSignal& operator=(const EthernetSignal& other);
    virtual EthernetSignal *dup() const override {return new EthernetSignal(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetSignal& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetSignal& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/wired/ethernet/EthernetSignal.msg:48</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents jam on the Ethernet.
 * //
 * packet EthernetJamSignal extends EthernetSignalBase
 * {
 *     srcMacFullDuplex = false;
 *     long abortedPkTreeID = 0;  // this field stores the packetTreeId of the aborted packet
 * }
 * </pre>
 */
class INET_API EthernetJamSignal : public ::inet::physicallayer::EthernetSignalBase
{
  protected:
    long abortedPkTreeID = 0;

  private:
    void copy(const EthernetJamSignal& other);

  protected:
    bool operator==(const EthernetJamSignal&) = delete;

  public:
    EthernetJamSignal(const char *name=nullptr, short kind=0);
    EthernetJamSignal(const EthernetJamSignal& other);
    virtual ~EthernetJamSignal();
    EthernetJamSignal& operator=(const EthernetJamSignal& other);
    virtual EthernetJamSignal *dup() const override {return new EthernetJamSignal(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual long getAbortedPkTreeID() const;
    virtual void setAbortedPkTreeID(long abortedPkTreeID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetJamSignal& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetJamSignal& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/physicallayer/wired/ethernet/EthernetSignal.msg:58</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents a filled inter-frame gap in burst mode.
 * // Also used for calculating IFG times.
 * //
 * packet EthernetFilledIfgSignal extends EthernetSignalBase
 * {
 *     srcMacFullDuplex = false;
 *     bitLength = b(INTERFRAME_GAP_BITS).get();
 * }
 * </pre>
 */
class INET_API EthernetFilledIfgSignal : public ::inet::physicallayer::EthernetSignalBase
{
  protected:

  private:
    void copy(const EthernetFilledIfgSignal& other);

  protected:
    bool operator==(const EthernetFilledIfgSignal&) = delete;

  public:
    EthernetFilledIfgSignal(const char *name=nullptr, short kind=0);
    EthernetFilledIfgSignal(const EthernetFilledIfgSignal& other);
    virtual ~EthernetFilledIfgSignal();
    EthernetFilledIfgSignal& operator=(const EthernetFilledIfgSignal& other);
    virtual EthernetFilledIfgSignal *dup() const override {return new EthernetFilledIfgSignal(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EthernetFilledIfgSignal& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EthernetFilledIfgSignal& obj) {obj.parsimUnpack(b);}


}  // namespace physicallayer
}  // namespace inet


namespace omnetpp {

template<> inline inet::physicallayer::EthernetSignalBase *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::EthernetSignalBase*>(ptr.get<cObject>()); }
template<> inline inet::physicallayer::EthernetSignal *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::EthernetSignal*>(ptr.get<cObject>()); }
template<> inline inet::physicallayer::EthernetJamSignal *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::EthernetJamSignal*>(ptr.get<cObject>()); }
template<> inline inet::physicallayer::EthernetFilledIfgSignal *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::physicallayer::EthernetFilledIfgSignal*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET__PHYSICALLAYER_ETHERNETSIGNAL_M_H


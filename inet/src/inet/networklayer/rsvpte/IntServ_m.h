//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/rsvpte/IntServ.msg.
//

#ifndef __INET_INTSERV_M_H
#define __INET_INTSERV_M_H

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

struct SessionObj;
struct RsvpHopObj;
struct SenderTemplateObj;
struct SenderTspecObj;
struct FlowSpecObj;
struct FilterSpecObj;
struct LabelRequestObj;
struct SenderDescriptor_t;
struct EroObj;
struct FlowDescriptor_t;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/networklayer/contract/ipv4/Ipv4Address_m.h" // import inet.networklayer.contract.ipv4.Ipv4Address


namespace inet {

// cplusplus {{
typedef std::vector<struct EroObj> EroVector;
typedef std::vector<struct FlowDescriptor_t> FlowDescriptorVector;
// }}

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:44 by opp_msgtool.
 */
struct INET_API SessionObj
{
    SessionObj();
    int Tunnel_Id = 0;
    int Extended_Tunnel_Id = 0;
    Ipv4Address DestAddress;
    int setupPri = 0;
    int holdingPri = 0;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const SessionObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, SessionObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SessionObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SessionObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:56 by opp_msgtool.
 */
struct INET_API RsvpHopObj
{
    RsvpHopObj();
    Ipv4Address Next_Hop_Address;
    Ipv4Address Logical_Interface_Handle;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const RsvpHopObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, RsvpHopObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RsvpHopObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RsvpHopObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:65 by opp_msgtool.
 */
struct INET_API SenderTemplateObj
{
    SenderTemplateObj();
    Ipv4Address SrcAddress;
    int Lsp_Id = -1;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const SenderTemplateObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, SenderTemplateObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SenderTemplateObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SenderTemplateObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:75 by opp_msgtool.
 */
struct INET_API SenderTspecObj
{
    SenderTspecObj();
    double req_bandwidth = 0;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const SenderTspecObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, SenderTspecObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SenderTspecObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SenderTspecObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:83 by opp_msgtool.
 */
struct INET_API FlowSpecObj : ::inet::SenderTspecObj
{
    FlowSpecObj();
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const FlowSpecObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, FlowSpecObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const FlowSpecObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, FlowSpecObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:90 by opp_msgtool.
 */
struct INET_API FilterSpecObj : ::inet::SenderTemplateObj
{
    FilterSpecObj();
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const FilterSpecObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, FilterSpecObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const FilterSpecObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, FilterSpecObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:97 by opp_msgtool.
 */
struct INET_API LabelRequestObj
{
    LabelRequestObj();
    int prot = 0;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const LabelRequestObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, LabelRequestObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LabelRequestObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LabelRequestObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:106 by opp_msgtool.
 */
struct INET_API SenderDescriptor_t
{
    SenderDescriptor_t();
    SenderTemplateObj Sender_Template_Object;
    SenderTspecObj Sender_Tspec_Object;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const SenderDescriptor_t& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, SenderDescriptor_t& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SenderDescriptor_t& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SenderDescriptor_t& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:115 by opp_msgtool.
 */
struct INET_API EroObj
{
    EroObj();
    bool L = false;
    Ipv4Address node;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const EroObj& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, EroObj& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EroObj& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EroObj& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/networklayer/rsvpte/IntServ.msg:124 by opp_msgtool.
 */
struct INET_API FlowDescriptor_t
{
    FlowDescriptor_t();
    FlowSpecObj Flowspec_Object;
    FilterSpecObj Filter_Spec_Object;
    Ipv4AddressVector RRO;
    int label = 0;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const FlowDescriptor_t& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, FlowDescriptor_t& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const FlowDescriptor_t& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, FlowDescriptor_t& obj) { __doUnpacking(b, obj); }


}  // namespace inet


namespace omnetpp {

inline any_ptr toAnyPtr(const inet::EroVector *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::EroVector *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::EroVector>(); }
inline any_ptr toAnyPtr(const inet::FlowDescriptorVector *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::FlowDescriptorVector *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::FlowDescriptorVector>(); }
inline any_ptr toAnyPtr(const inet::SessionObj *p) {return any_ptr(p);}
template<> inline inet::SessionObj *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::SessionObj>(); }
inline any_ptr toAnyPtr(const inet::RsvpHopObj *p) {return any_ptr(p);}
template<> inline inet::RsvpHopObj *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::RsvpHopObj>(); }
inline any_ptr toAnyPtr(const inet::SenderTemplateObj *p) {return any_ptr(p);}
template<> inline inet::SenderTemplateObj *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::SenderTemplateObj>(); }
inline any_ptr toAnyPtr(const inet::SenderTspecObj *p) {return any_ptr(p);}
template<> inline inet::SenderTspecObj *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::SenderTspecObj>(); }
template<> inline inet::FlowSpecObj *fromAnyPtr(any_ptr ptr) { return static_cast<inet::FlowSpecObj*>(ptr.get<inet::SenderTspecObj>()); }
template<> inline inet::FilterSpecObj *fromAnyPtr(any_ptr ptr) { return static_cast<inet::FilterSpecObj*>(ptr.get<inet::SenderTemplateObj>()); }
inline any_ptr toAnyPtr(const inet::LabelRequestObj *p) {return any_ptr(p);}
template<> inline inet::LabelRequestObj *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::LabelRequestObj>(); }
inline any_ptr toAnyPtr(const inet::SenderDescriptor_t *p) {return any_ptr(p);}
template<> inline inet::SenderDescriptor_t *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::SenderDescriptor_t>(); }
inline any_ptr toAnyPtr(const inet::EroObj *p) {return any_ptr(p);}
template<> inline inet::EroObj *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::EroObj>(); }
inline any_ptr toAnyPtr(const inet::FlowDescriptor_t *p) {return any_ptr(p);}
template<> inline inet::FlowDescriptor_t *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::FlowDescriptor_t>(); }

}  // namespace omnetpp

#endif // ifndef __INET_INTSERV_M_H


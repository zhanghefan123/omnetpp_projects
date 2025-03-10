//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/common/ProtocolTag.msg.
//

#ifndef __INET_PROTOCOLTAG_M_H
#define __INET_PROTOCOLTAG_M_H

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

class ProtocolTagBase;
class DispatchProtocolReq;
class DispatchProtocolInd;
class PacketProtocolTag;
class TransportProtocolReq;
class TransportProtocolInd;
class NetworkProtocolReq;
class NetworkProtocolInd;
class MacProtocolReq;
class MacProtocolInd;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Protocol_m.h" // import inet.common.Protocol

#include "inet/common/TagBase_m.h" // import inet.common.TagBase

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk


namespace inet {

// cplusplus {{
typedef Ptr<const Chunk> ChunkPtr;
// }}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:40</tt> by opp_msgtool.
 * <pre>
 * //
 * // This is an abstract base class that should not be directly added as a tag.
 * //
 * class ProtocolTagBase extends TagBase
 * {
 *     const Protocol *protocol \@toString("->str()") = nullptr; // specifies a protocol (internal class with an artificial identifier)
 * }
 * </pre>
 */
class INET_API ProtocolTagBase : public ::inet::TagBase
{
  protected:
    const Protocol * protocol = nullptr;

  private:
    void copy(const ProtocolTagBase& other);

  protected:
    bool operator==(const ProtocolTagBase&) = delete;

  public:
    ProtocolTagBase();
    ProtocolTagBase(const ProtocolTagBase& other);
    virtual ~ProtocolTagBase();
    ProtocolTagBase& operator=(const ProtocolTagBase& other);
    virtual ProtocolTagBase *dup() const override {return new ProtocolTagBase(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const Protocol * getProtocol() const;
    virtual void setProtocol(const Protocol * protocol);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ProtocolTagBase& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ProtocolTagBase& obj) {obj.parsimUnpack(b);}

/**
 * Enum generated from <tt>inet/common/ProtocolTag.msg:48</tt> by opp_msgtool.
 * <pre>
 * //
 * // OSI layered service primitives
 * //
 * enum ServicePrimitive
 * {
 *     SP_REQUEST = 1;
 *     SP_INDICATION = 2;
 *     SP_RESPONSE = 3;
 *     SP_CONFIRM = 4;
 * }
 * </pre>
 */
enum ServicePrimitive {
    SP_REQUEST = 1,
    SP_INDICATION = 2,
    SP_RESPONSE = 3,
    SP_CONFIRM = 4
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ServicePrimitive& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ServicePrimitive& e) { int n; b->unpack(n); e = static_cast<ServicePrimitive>(n); }

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:60</tt> by opp_msgtool.
 * <pre>
 * //
 * // This request determines the destination protocol of the message or packet
 * // when it's sent from one protocol module to another using the ~MessageDispatcher.
 * //
 * class DispatchProtocolReq extends ProtocolTagBase
 * {
 *     ServicePrimitive servicePrimitive;
 * }
 * </pre>
 */
class INET_API DispatchProtocolReq : public ::inet::ProtocolTagBase
{
  protected:
    ServicePrimitive servicePrimitive = static_cast<inet::ServicePrimitive>(-1);

  private:
    void copy(const DispatchProtocolReq& other);

  protected:
    bool operator==(const DispatchProtocolReq&) = delete;

  public:
    DispatchProtocolReq();
    DispatchProtocolReq(const DispatchProtocolReq& other);
    virtual ~DispatchProtocolReq();
    DispatchProtocolReq& operator=(const DispatchProtocolReq& other);
    virtual DispatchProtocolReq *dup() const override {return new DispatchProtocolReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual ServicePrimitive getServicePrimitive() const;
    virtual void setServicePrimitive(ServicePrimitive servicePrimitive);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DispatchProtocolReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DispatchProtocolReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:69</tt> by opp_msgtool.
 * <pre>
 * //
 * // This indication specifies the sending protocol of the message or packet
 * // when it's sent from one protocol module to another using the ~MessageDispatcher.
 * //
 * class DispatchProtocolInd extends ProtocolTagBase
 * {
 * }
 * </pre>
 */
class INET_API DispatchProtocolInd : public ::inet::ProtocolTagBase
{
  protected:

  private:
    void copy(const DispatchProtocolInd& other);

  protected:
    bool operator==(const DispatchProtocolInd&) = delete;

  public:
    DispatchProtocolInd();
    DispatchProtocolInd(const DispatchProtocolInd& other);
    virtual ~DispatchProtocolInd();
    DispatchProtocolInd& operator=(const DispatchProtocolInd& other);
    virtual DispatchProtocolInd *dup() const override {return new DispatchProtocolInd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DispatchProtocolInd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DispatchProtocolInd& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:126</tt> by opp_msgtool.
 * <pre>
 * //
 * // This tag specifies the protocol of the packet.
 * //
 * // Packet processing at the sender
 * // ===============================
 * //
 * // | ApplicationData |
 * //     whole packet has no protocol
 * //     data part has no protocol
 * //
 * // | UdpHeader ApplicationData |
 * //     whole packet has UDP protocol
 * //     data part has UDP protocol
 * //
 * // | Ipv4Header UdpHeader ApplicationData |
 * //     whole packet has IPv4 protocol
 * //     data part has IPv4 protocol
 * //
 * // EthernetMacHeader | Ipv4Header UdpHeader ApplicationData |
 * //     whole packet has incomplete Ethernet protocol
 * //     data part has IPv4 protocol
 * //
 * // EthernetMacHeader | Ipv4Header UdpHeader ApplicationData | EthernetPadding EthernetFcs
 * //     whole packet has Ethernet protocol
 * //     data part has IPv4 protocol
 * //
 * // | EthernetMacHeader Ipv4Header UdpHeader ApplicationData EthernetPadding EthernetFcs |
 * //     whole packet has Ethernet protocol
 * //     data part has Ethernet protocol
 * //
 * // Packet processing at the receiver
 * // =================================
 * //
 * // | EthernetMacHeader Ipv4Header UdpHeader ApplicationData EthernetPadding EthernetFcs |
 * //     whole packet has Ethernet protocol
 * //     data part has Ethernet protocol
 * //
 * // EthernetMacHeader Ipv4Header UdpHeader ApplicationData EthernetPadding | EthernetFcs
 * //     whole packet has Ethernet protocol
 * //     data part has no protocol
 * //
 * // EthernetMacHeader | Ipv4Header UdpHeader ApplicationData | EthernetPadding EthernetFcs
 * //     whole packet has Ethernet protocol
 * //     data part has IPv4 protocol
 * //
 * // EthernetMacHeader Ipv4Header | UdpHeader ApplicationData | EthernetPadding EthernetFcs
 * //     whole packet has Ethernet protocol
 * //     data part has UDP protocol
 * //
 * // EthernetMacHeader Ipv4Header UdpHeader | ApplicationData | EthernetPadding EthernetFcs
 * //     whole packet has Ethernet protocol
 * //     data part has no protocol
 * //
 * class PacketProtocolTag extends ProtocolTagBase
 * {
 *     b frontOffset = b(0); // extra offset relative to the packet data part front offset
 *     b backOffset = b(0); // extra offset relative to the packet data part back offset
 * }
 * </pre>
 */
class INET_API PacketProtocolTag : public ::inet::ProtocolTagBase
{
  protected:
    b frontOffset = b(0);
    b backOffset = b(0);

  private:
    void copy(const PacketProtocolTag& other);

  protected:
    bool operator==(const PacketProtocolTag&) = delete;

  public:
    PacketProtocolTag();
    PacketProtocolTag(const PacketProtocolTag& other);
    virtual ~PacketProtocolTag();
    PacketProtocolTag& operator=(const PacketProtocolTag& other);
    virtual PacketProtocolTag *dup() const override {return new PacketProtocolTag(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual b getFrontOffset() const;
    virtual void setFrontOffset(b frontOffset);

    virtual b getBackOffset() const;
    virtual void setBackOffset(b backOffset);


    void set(const Protocol *protocol, b frontOffset = b(0), b backOffset = b(0)) {
        this->protocol = protocol;
        this->frontOffset = frontOffset;
        this->backOffset = backOffset;
    }
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PacketProtocolTag& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PacketProtocolTag& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:144</tt> by opp_msgtool.
 * <pre>
 * //
 * // This request determines the transport protocol that should be used to send the packet.
 * // It may be present from the application to the transport protocol.
 * //
 * class TransportProtocolReq extends ProtocolTagBase
 * {
 * }
 * </pre>
 */
class INET_API TransportProtocolReq : public ::inet::ProtocolTagBase
{
  protected:

  private:
    void copy(const TransportProtocolReq& other);

  protected:
    bool operator==(const TransportProtocolReq&) = delete;

  public:
    TransportProtocolReq();
    TransportProtocolReq(const TransportProtocolReq& other);
    virtual ~TransportProtocolReq();
    TransportProtocolReq& operator=(const TransportProtocolReq& other);
    virtual TransportProtocolReq *dup() const override {return new TransportProtocolReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TransportProtocolReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TransportProtocolReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:153</tt> by opp_msgtool.
 * <pre>
 * //
 * // This indication specifies the transport protocol that was used to receive
 * // the packet. It may be present from the transport protocol to the application
 * // and from the transport protocol to the physical layer.
 * //
 * class TransportProtocolInd extends ProtocolTagBase
 * {
 *     ChunkPtr transportProtocolHeader = nullptr;
 * }
 * </pre>
 */
class INET_API TransportProtocolInd : public ::inet::ProtocolTagBase
{
  protected:
    ChunkPtr transportProtocolHeader = nullptr;

  private:
    void copy(const TransportProtocolInd& other);

  protected:
    bool operator==(const TransportProtocolInd&) = delete;

  public:
    TransportProtocolInd();
    TransportProtocolInd(const TransportProtocolInd& other);
    virtual ~TransportProtocolInd();
    TransportProtocolInd& operator=(const TransportProtocolInd& other);
    virtual TransportProtocolInd *dup() const override {return new TransportProtocolInd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const ChunkPtr& getTransportProtocolHeader() const;
    virtual ChunkPtr& getTransportProtocolHeaderForUpdate() { return const_cast<ChunkPtr&>(const_cast<TransportProtocolInd*>(this)->getTransportProtocolHeader());}
    virtual void setTransportProtocolHeader(const ChunkPtr& transportProtocolHeader);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TransportProtocolInd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TransportProtocolInd& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:163</tt> by opp_msgtool.
 * <pre>
 * //
 * // This request determines the network protocol that should be used to send the
 * // packet. It may be present from the application to the network protocol and
 * // from the network protocol to the physical layer.
 * //
 * class NetworkProtocolReq extends ProtocolTagBase
 * {
 * }
 * </pre>
 */
class INET_API NetworkProtocolReq : public ::inet::ProtocolTagBase
{
  protected:

  private:
    void copy(const NetworkProtocolReq& other);

  protected:
    bool operator==(const NetworkProtocolReq&) = delete;

  public:
    NetworkProtocolReq();
    NetworkProtocolReq(const NetworkProtocolReq& other);
    virtual ~NetworkProtocolReq();
    NetworkProtocolReq& operator=(const NetworkProtocolReq& other);
    virtual NetworkProtocolReq *dup() const override {return new NetworkProtocolReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NetworkProtocolReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NetworkProtocolReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:171</tt> by opp_msgtool.
 * <pre>
 * //
 * // This indication specifies the network protocol that was used to receive the
 * // packet. It may be present from the network protocol to the application.
 * //
 * class NetworkProtocolInd extends ProtocolTagBase
 * {
 *     ChunkPtr networkProtocolHeader = nullptr;
 * }
 * </pre>
 */
class INET_API NetworkProtocolInd : public ::inet::ProtocolTagBase
{
  protected:
    ChunkPtr networkProtocolHeader = nullptr;

  private:
    void copy(const NetworkProtocolInd& other);

  protected:
    bool operator==(const NetworkProtocolInd&) = delete;

  public:
    NetworkProtocolInd();
    NetworkProtocolInd(const NetworkProtocolInd& other);
    virtual ~NetworkProtocolInd();
    NetworkProtocolInd& operator=(const NetworkProtocolInd& other);
    virtual NetworkProtocolInd *dup() const override {return new NetworkProtocolInd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const ChunkPtr& getNetworkProtocolHeader() const;
    virtual ChunkPtr& getNetworkProtocolHeaderForUpdate() { return const_cast<ChunkPtr&>(const_cast<NetworkProtocolInd*>(this)->getNetworkProtocolHeader());}
    virtual void setNetworkProtocolHeader(const ChunkPtr& networkProtocolHeader);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const NetworkProtocolInd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, NetworkProtocolInd& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:181</tt> by opp_msgtool.
 * <pre>
 * //
 * // This request determines the mac protocol that should be used to send the
 * // packet. It may be present from the application to the mac protocol and from
 * // the mac protocol to the physical layer.
 * //
 * class MacProtocolReq extends ProtocolTagBase
 * {
 * }
 * </pre>
 */
class INET_API MacProtocolReq : public ::inet::ProtocolTagBase
{
  protected:

  private:
    void copy(const MacProtocolReq& other);

  protected:
    bool operator==(const MacProtocolReq&) = delete;

  public:
    MacProtocolReq();
    MacProtocolReq(const MacProtocolReq& other);
    virtual ~MacProtocolReq();
    MacProtocolReq& operator=(const MacProtocolReq& other);
    virtual MacProtocolReq *dup() const override {return new MacProtocolReq(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MacProtocolReq& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MacProtocolReq& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/common/ProtocolTag.msg:189</tt> by opp_msgtool.
 * <pre>
 * //
 * // This indication specifies the mac protocol that was used to receive the
 * // packet. It may be present from the mac protocol to the application.
 * //
 * class MacProtocolInd extends ProtocolTagBase
 * {
 *     ChunkPtr macProtocolHeader = nullptr;
 * }
 * </pre>
 */
class INET_API MacProtocolInd : public ::inet::ProtocolTagBase
{
  protected:
    ChunkPtr macProtocolHeader = nullptr;

  private:
    void copy(const MacProtocolInd& other);

  protected:
    bool operator==(const MacProtocolInd&) = delete;

  public:
    MacProtocolInd();
    MacProtocolInd(const MacProtocolInd& other);
    virtual ~MacProtocolInd();
    MacProtocolInd& operator=(const MacProtocolInd& other);
    virtual MacProtocolInd *dup() const override {return new MacProtocolInd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const ChunkPtr& getMacProtocolHeader() const;
    virtual ChunkPtr& getMacProtocolHeaderForUpdate() { return const_cast<ChunkPtr&>(const_cast<MacProtocolInd*>(this)->getMacProtocolHeader());}
    virtual void setMacProtocolHeader(const ChunkPtr& macProtocolHeader);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const MacProtocolInd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, MacProtocolInd& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

inline any_ptr toAnyPtr(const inet::ChunkPtr *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::ChunkPtr *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::ChunkPtr>(); }
template<> inline inet::ProtocolTagBase *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::ProtocolTagBase*>(ptr.get<cObject>()); }
template<> inline inet::DispatchProtocolReq *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::DispatchProtocolReq*>(ptr.get<cObject>()); }
template<> inline inet::DispatchProtocolInd *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::DispatchProtocolInd*>(ptr.get<cObject>()); }
template<> inline inet::PacketProtocolTag *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PacketProtocolTag*>(ptr.get<cObject>()); }
template<> inline inet::TransportProtocolReq *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::TransportProtocolReq*>(ptr.get<cObject>()); }
template<> inline inet::TransportProtocolInd *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::TransportProtocolInd*>(ptr.get<cObject>()); }
template<> inline inet::NetworkProtocolReq *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::NetworkProtocolReq*>(ptr.get<cObject>()); }
template<> inline inet::NetworkProtocolInd *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::NetworkProtocolInd*>(ptr.get<cObject>()); }
template<> inline inet::MacProtocolReq *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::MacProtocolReq*>(ptr.get<cObject>()); }
template<> inline inet::MacProtocolInd *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::MacProtocolInd*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_PROTOCOLTAG_M_H


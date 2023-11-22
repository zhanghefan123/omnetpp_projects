//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/routing/pim/PimPacket.msg.
//

#ifndef __INET_PIMPACKET_M_H
#define __INET_PIMPACKET_M_H

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

struct EncodedUnicastAddress;
struct EncodedGroupAddress;
struct EncodedSourceAddress;
class HelloOption;
class HoldtimeOption;
class LanPruneDelayOption;
class DrPriorityOption;
class GenerationIdOption;
class AddressListOption;
class PimPacket;
class PimHello;
class JoinPruneGroup;
class PimJoinPrune;
class PimAssert;
class PimGraft;
class PimStateRefresh;
class PimRegister;
class PimRegisterStop;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Units_m.h" // import inet.common.Units

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/networklayer/common/L3Address_m.h" // import inet.networklayer.common.L3Address

#include "inet/transportlayer/common/CrcMode_m.h" // import inet.transportlayer.common.CrcMode


namespace inet {

// cplusplus {{
const B PIM_HEADER_LENGTH = B(4);
const B ENCODED_UNICODE_ADDRESS_LENGTH = B(6); // Ipv4 only
const B ENCODED_GROUP_ADDRESS_LENGTH = B(8); // Ipv4 only
const B ENCODED_SOURCE_ADDRESS_LENGTH = B(8); // Ipv4 only
// }}

/**
 * Enum generated from <tt>inet/routing/pim/PimPacket.msg:38</tt> by opp_msgtool.
 * <pre>
 * enum PimPacketType
 * {
 *     Hello = 0;
 *     Register = 1;
 *     RegisterStop = 2;
 *     JoinPrune = 3;
 *     Bootstrap = 4;
 *     Assert = 5;
 *     Graft = 6;
 *     GraftAck = 7;
 *     CandidateRPAdvertisement = 8;
 *     StateRefresh = 9;    // in RFC 3973
 * }
 * </pre>
 */
enum PimPacketType {
    Hello = 0,
    Register = 1,
    RegisterStop = 2,
    JoinPrune = 3,
    Bootstrap = 4,
    Assert = 5,
    Graft = 6,
    GraftAck = 7,
    CandidateRPAdvertisement = 8,
    StateRefresh = 9
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimPacketType& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimPacketType& e) { int n; b->unpack(n); e = static_cast<PimPacketType>(n); }

/**
 * Enum generated from <tt>inet/routing/pim/PimPacket.msg:52</tt> by opp_msgtool.
 * <pre>
 * enum PimHelloOptionType
 * {
 *     Holdtime = 1;
 *     LANPruneDelay = 2;
 *     DRPriority = 19;
 *     GenerationID = 20;
 *     StateRefreshCapable = 21;
 *     AddressList = 24;
 * }
 * </pre>
 */
enum PimHelloOptionType {
    Holdtime = 1,
    LANPruneDelay = 2,
    DRPriority = 19,
    GenerationID = 20,
    StateRefreshCapable = 21,
    AddressList = 24
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimHelloOptionType& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimHelloOptionType& e) { int n; b->unpack(n); e = static_cast<PimHelloOptionType>(n); }

/**
 * Struct generated from inet/routing/pim/PimPacket.msg:62 by opp_msgtool.
 */
struct INET_API EncodedUnicastAddress
{
    EncodedUnicastAddress();
    L3Address unicastAddress;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const EncodedUnicastAddress& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, EncodedUnicastAddress& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EncodedUnicastAddress& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EncodedUnicastAddress& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/routing/pim/PimPacket.msg:67 by opp_msgtool.
 */
struct INET_API EncodedGroupAddress
{
    EncodedGroupAddress();
    bool B = false;
    short reserved = 0;
    bool Z = false;
    short maskLength = 32;
    L3Address groupAddress;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const EncodedGroupAddress& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, EncodedGroupAddress& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EncodedGroupAddress& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EncodedGroupAddress& obj) { __doUnpacking(b, obj); }

/**
 * Struct generated from inet/routing/pim/PimPacket.msg:76 by opp_msgtool.
 */
struct INET_API EncodedSourceAddress
{
    EncodedSourceAddress();
    short reserved = 0;
    bool S = false;
    bool W = false;
    bool R = false;
    short maskLength = 32;
    L3Address sourceAddress;
};

// helpers for local use
void INET_API __doPacking(omnetpp::cCommBuffer *b, const EncodedSourceAddress& a);
void INET_API __doUnpacking(omnetpp::cCommBuffer *b, EncodedSourceAddress& a);

inline void doParsimPacking(omnetpp::cCommBuffer *b, const EncodedSourceAddress& obj) { __doPacking(b, obj); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, EncodedSourceAddress& obj) { __doUnpacking(b, obj); }

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:86</tt> by opp_msgtool.
 * <pre>
 * class HelloOption extends cObject
 * {
 *     PimHelloOptionType type;
 * }
 * </pre>
 */
class INET_API HelloOption : public ::omnetpp::cObject
{
  protected:
    PimHelloOptionType type = static_cast<inet::PimHelloOptionType>(-1);

  private:
    void copy(const HelloOption& other);

  protected:
    bool operator==(const HelloOption&) = delete;

  public:
    HelloOption();
    HelloOption(const HelloOption& other);
    virtual ~HelloOption();
    HelloOption& operator=(const HelloOption& other);
    virtual HelloOption *dup() const override {return new HelloOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual PimHelloOptionType getType() const;
    virtual void setType(PimHelloOptionType type);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const HelloOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, HelloOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:91</tt> by opp_msgtool.
 * <pre>
 * class HoldtimeOption extends HelloOption
 * {
 *     type = Holdtime;
 *     uint16_t holdTime; // (in seconds)
 * }
 * </pre>
 */
class INET_API HoldtimeOption : public ::inet::HelloOption
{
  protected:
    uint16_t holdTime = 0;

  private:
    void copy(const HoldtimeOption& other);

  protected:
    bool operator==(const HoldtimeOption&) = delete;

  public:
    HoldtimeOption();
    HoldtimeOption(const HoldtimeOption& other);
    virtual ~HoldtimeOption();
    HoldtimeOption& operator=(const HoldtimeOption& other);
    virtual HoldtimeOption *dup() const override {return new HoldtimeOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint16_t getHoldTime() const;
    virtual void setHoldTime(uint16_t holdTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const HoldtimeOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, HoldtimeOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:97</tt> by opp_msgtool.
 * <pre>
 * class LanPruneDelayOption extends HelloOption
 * {
 *     type = LANPruneDelay;
 *     bool T = false;
 *     uint16_t propagationDelay;
 *     uint16_t overrideInterval;
 * }
 * </pre>
 */
class INET_API LanPruneDelayOption : public ::inet::HelloOption
{
  protected:
    bool T = false;
    uint16_t propagationDelay = 0;
    uint16_t overrideInterval = 0;

  private:
    void copy(const LanPruneDelayOption& other);

  protected:
    bool operator==(const LanPruneDelayOption&) = delete;

  public:
    LanPruneDelayOption();
    LanPruneDelayOption(const LanPruneDelayOption& other);
    virtual ~LanPruneDelayOption();
    LanPruneDelayOption& operator=(const LanPruneDelayOption& other);
    virtual LanPruneDelayOption *dup() const override {return new LanPruneDelayOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getT() const;
    virtual void setT(bool T);

    virtual uint16_t getPropagationDelay() const;
    virtual void setPropagationDelay(uint16_t propagationDelay);

    virtual uint16_t getOverrideInterval() const;
    virtual void setOverrideInterval(uint16_t overrideInterval);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const LanPruneDelayOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, LanPruneDelayOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:105</tt> by opp_msgtool.
 * <pre>
 * class DrPriorityOption extends HelloOption
 * {
 *     type = DRPriority;
 *     uint32_t priority;
 * }
 * </pre>
 */
class INET_API DrPriorityOption : public ::inet::HelloOption
{
  protected:
    uint32_t priority = 0;

  private:
    void copy(const DrPriorityOption& other);

  protected:
    bool operator==(const DrPriorityOption&) = delete;

  public:
    DrPriorityOption();
    DrPriorityOption(const DrPriorityOption& other);
    virtual ~DrPriorityOption();
    DrPriorityOption& operator=(const DrPriorityOption& other);
    virtual DrPriorityOption *dup() const override {return new DrPriorityOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint32_t getPriority() const;
    virtual void setPriority(uint32_t priority);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const DrPriorityOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, DrPriorityOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:111</tt> by opp_msgtool.
 * <pre>
 * class GenerationIdOption extends HelloOption
 * {
 *     type = GenerationID;
 *     uint32_t generationID;
 * }
 * </pre>
 */
class INET_API GenerationIdOption : public ::inet::HelloOption
{
  protected:
    uint32_t generationID = 0;

  private:
    void copy(const GenerationIdOption& other);

  protected:
    bool operator==(const GenerationIdOption&) = delete;

  public:
    GenerationIdOption();
    GenerationIdOption(const GenerationIdOption& other);
    virtual ~GenerationIdOption();
    GenerationIdOption& operator=(const GenerationIdOption& other);
    virtual GenerationIdOption *dup() const override {return new GenerationIdOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint32_t getGenerationID() const;
    virtual void setGenerationID(uint32_t generationID);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const GenerationIdOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, GenerationIdOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:117</tt> by opp_msgtool.
 * <pre>
 * class AddressListOption extends HelloOption
 * {
 *     EncodedUnicastAddress secondaryAddresses[];
 * }
 * </pre>
 */
class INET_API AddressListOption : public ::inet::HelloOption
{
  protected:
    EncodedUnicastAddress *secondaryAddresses = nullptr;
    size_t secondaryAddresses_arraysize = 0;

  private:
    void copy(const AddressListOption& other);

  protected:
    bool operator==(const AddressListOption&) = delete;

  public:
    AddressListOption();
    AddressListOption(const AddressListOption& other);
    virtual ~AddressListOption();
    AddressListOption& operator=(const AddressListOption& other);
    virtual AddressListOption *dup() const override {return new AddressListOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual void setSecondaryAddressesArraySize(size_t size);
    virtual size_t getSecondaryAddressesArraySize() const;
    virtual const EncodedUnicastAddress& getSecondaryAddresses(size_t k) const;
    virtual EncodedUnicastAddress& getSecondaryAddressesForUpdate(size_t k) { return const_cast<EncodedUnicastAddress&>(const_cast<AddressListOption*>(this)->getSecondaryAddresses(k));}
    virtual void setSecondaryAddresses(size_t k, const EncodedUnicastAddress& secondaryAddresses);
    virtual void insertSecondaryAddresses(size_t k, const EncodedUnicastAddress& secondaryAddresses);
    [[deprecated]] void insertSecondaryAddresses(const EncodedUnicastAddress& secondaryAddresses) {appendSecondaryAddresses(secondaryAddresses);}
    virtual void appendSecondaryAddresses(const EncodedUnicastAddress& secondaryAddresses);
    virtual void eraseSecondaryAddresses(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const AddressListOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, AddressListOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:124</tt> by opp_msgtool.
 * <pre>
 * ///////////////////////////////////////////////////////////////////////////////////////////////
 * // Header
 * class PimPacket extends FieldsChunk
 * {
 *     short version = 2;
 *     PimPacketType type;
 *     short reserved = 0;    // 8 bits
 *     uint16_t crc = 0;         // The checksum is a standard IP checksum, i.e., the 16-bit one's
 *                                     // complement of the one's complement sum of the entire PIM
 *                                     // message, excluding the "Multicast data packet" section of the
 *                                     // Register message.  For computing the checksum, the checksum
 *                                     // field is zeroed.  If the packet's length is not an integral
 *                                     // number of 16-bit words, the packet is padded with a trailing
 *                                     // byte of zero before performing the checksum.
 *                                     //
 *                                     // For IPv6, the checksum also includes the IPv6 "pseudo-header",
 *                                     // as specified in RFC 2460, Section 8.1 [5].  This "pseudo-header"
 *                                     // is prepended to the PIM header for the purposes of calculating
 *                                     // the checksum.  The "Upper-Layer Packet Length" in the pseudo-
 *                                     // header is set to the length of the PIM message, except in
 *                                     // Register messages where it is set to the length of the PIM
 *                                     // register header (8).  The Next Header value used in the pseudo-
 *                                     // header is 103.
 *     CrcMode crcMode = CRC_MODE_UNDEFINED;
 * }
 * </pre>
 */
class INET_API PimPacket : public ::inet::FieldsChunk
{
  protected:
    short version = 2;
    PimPacketType type = static_cast<inet::PimPacketType>(-1);
    short reserved = 0;
    uint16_t crc = 0;
    CrcMode crcMode = CRC_MODE_UNDEFINED;

  private:
    void copy(const PimPacket& other);

  protected:
    bool operator==(const PimPacket&) = delete;

  public:
    PimPacket();
    PimPacket(const PimPacket& other);
    virtual ~PimPacket();
    PimPacket& operator=(const PimPacket& other);
    virtual PimPacket *dup() const override {return new PimPacket(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual short getVersion() const;
    virtual void setVersion(short version);

    virtual PimPacketType getType() const;
    virtual void setType(PimPacketType type);

    virtual short getReserved() const;
    virtual void setReserved(short reserved);

    virtual uint16_t getCrc() const;
    virtual void setCrc(uint16_t crc);

    virtual CrcMode getCrcMode() const;
    virtual void setCrcMode(CrcMode crcMode);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimPacket& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:150</tt> by opp_msgtool.
 * <pre>
 * // Hello message
 * // DM, SM
 * class PimHello extends PimPacket
 * {
 *     type = Hello;
 *     HelloOption *options[] \@owned \@allowReplace;
 * }
 * </pre>
 */
class INET_API PimHello : public ::inet::PimPacket
{
  protected:
    HelloOption * *options = nullptr;
    size_t options_arraysize = 0;

  private:
    void copy(const PimHello& other);

  protected:
    bool operator==(const PimHello&) = delete;

  public:
    PimHello();
    PimHello(const PimHello& other);
    virtual ~PimHello();
    PimHello& operator=(const PimHello& other);
    virtual PimHello *dup() const override {return new PimHello(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual void setOptionsArraySize(size_t size);
    virtual size_t getOptionsArraySize() const;
    virtual const HelloOption * getOptions(size_t k) const;
    virtual HelloOption * getOptionsForUpdate(size_t k) { handleChange();return const_cast<HelloOption *>(const_cast<PimHello*>(this)->getOptions(k));}
    virtual void setOptions(size_t k, HelloOption * options);
    virtual HelloOption * removeOptions(size_t k);
    [[deprecated]] HelloOption * dropOptions(size_t k) {return removeOptions(k);}
    virtual void insertOptions(size_t k, HelloOption * options);
    [[deprecated]] void insertOptions(HelloOption * options) {appendOptions(options);}
    virtual void appendOptions(HelloOption * options);
    virtual void eraseOptions(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimHello& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimHello& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:158</tt> by opp_msgtool.
 * <pre>
 * // Record for Join/Prune message
 * // in structure it is not possible to use dynamic arrays, it is needed to use class
 * class JoinPruneGroup extends cObject
 * {
 *     EncodedGroupAddress groupAddress;
 *     EncodedSourceAddress joinedSourceAddress[];
 *     EncodedSourceAddress prunedSourceAddress[];
 * }
 * </pre>
 */
class INET_API JoinPruneGroup : public ::omnetpp::cObject
{
  protected:
    EncodedGroupAddress groupAddress;
    EncodedSourceAddress *joinedSourceAddress = nullptr;
    size_t joinedSourceAddress_arraysize = 0;
    EncodedSourceAddress *prunedSourceAddress = nullptr;
    size_t prunedSourceAddress_arraysize = 0;

  private:
    void copy(const JoinPruneGroup& other);

  protected:
    bool operator==(const JoinPruneGroup&) = delete;

  public:
    JoinPruneGroup();
    JoinPruneGroup(const JoinPruneGroup& other);
    virtual ~JoinPruneGroup();
    JoinPruneGroup& operator=(const JoinPruneGroup& other);
    virtual JoinPruneGroup *dup() const override {return new JoinPruneGroup(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const EncodedGroupAddress& getGroupAddress() const;
    virtual EncodedGroupAddress& getGroupAddressForUpdate() { return const_cast<EncodedGroupAddress&>(const_cast<JoinPruneGroup*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const EncodedGroupAddress& groupAddress);

    virtual void setJoinedSourceAddressArraySize(size_t size);
    virtual size_t getJoinedSourceAddressArraySize() const;
    virtual const EncodedSourceAddress& getJoinedSourceAddress(size_t k) const;
    virtual EncodedSourceAddress& getJoinedSourceAddressForUpdate(size_t k) { return const_cast<EncodedSourceAddress&>(const_cast<JoinPruneGroup*>(this)->getJoinedSourceAddress(k));}
    virtual void setJoinedSourceAddress(size_t k, const EncodedSourceAddress& joinedSourceAddress);
    virtual void insertJoinedSourceAddress(size_t k, const EncodedSourceAddress& joinedSourceAddress);
    [[deprecated]] void insertJoinedSourceAddress(const EncodedSourceAddress& joinedSourceAddress) {appendJoinedSourceAddress(joinedSourceAddress);}
    virtual void appendJoinedSourceAddress(const EncodedSourceAddress& joinedSourceAddress);
    virtual void eraseJoinedSourceAddress(size_t k);

    virtual void setPrunedSourceAddressArraySize(size_t size);
    virtual size_t getPrunedSourceAddressArraySize() const;
    virtual const EncodedSourceAddress& getPrunedSourceAddress(size_t k) const;
    virtual EncodedSourceAddress& getPrunedSourceAddressForUpdate(size_t k) { return const_cast<EncodedSourceAddress&>(const_cast<JoinPruneGroup*>(this)->getPrunedSourceAddress(k));}
    virtual void setPrunedSourceAddress(size_t k, const EncodedSourceAddress& prunedSourceAddress);
    virtual void insertPrunedSourceAddress(size_t k, const EncodedSourceAddress& prunedSourceAddress);
    [[deprecated]] void insertPrunedSourceAddress(const EncodedSourceAddress& prunedSourceAddress) {appendPrunedSourceAddress(prunedSourceAddress);}
    virtual void appendPrunedSourceAddress(const EncodedSourceAddress& prunedSourceAddress);
    virtual void erasePrunedSourceAddress(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const JoinPruneGroup& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, JoinPruneGroup& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:167</tt> by opp_msgtool.
 * <pre>
 * // Join/Prune message
 * // DM, SM
 * class PimJoinPrune extends PimPacket
 * {
 *     type = JoinPrune;
 *     EncodedUnicastAddress upstreamNeighborAddress;    //TODO replace to L3Address
 *     int reserved2 = 0;
 *     int holdTime;    // in seconds
 *     JoinPruneGroup joinPruneGroups[];
 * }
 * </pre>
 */
class INET_API PimJoinPrune : public ::inet::PimPacket
{
  protected:
    EncodedUnicastAddress upstreamNeighborAddress;
    int reserved2 = 0;
    int holdTime = 0;
    JoinPruneGroup *joinPruneGroups = nullptr;
    size_t joinPruneGroups_arraysize = 0;

  private:
    void copy(const PimJoinPrune& other);

  protected:
    bool operator==(const PimJoinPrune&) = delete;

  public:
    PimJoinPrune();
    PimJoinPrune(const PimJoinPrune& other);
    virtual ~PimJoinPrune();
    PimJoinPrune& operator=(const PimJoinPrune& other);
    virtual PimJoinPrune *dup() const override {return new PimJoinPrune(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const EncodedUnicastAddress& getUpstreamNeighborAddress() const;
    virtual EncodedUnicastAddress& getUpstreamNeighborAddressForUpdate() { handleChange();return const_cast<EncodedUnicastAddress&>(const_cast<PimJoinPrune*>(this)->getUpstreamNeighborAddress());}
    virtual void setUpstreamNeighborAddress(const EncodedUnicastAddress& upstreamNeighborAddress);

    virtual int getReserved2() const;
    virtual void setReserved2(int reserved2);

    virtual int getHoldTime() const;
    virtual void setHoldTime(int holdTime);

    virtual void setJoinPruneGroupsArraySize(size_t size);
    virtual size_t getJoinPruneGroupsArraySize() const;
    virtual const JoinPruneGroup& getJoinPruneGroups(size_t k) const;
    virtual JoinPruneGroup& getJoinPruneGroupsForUpdate(size_t k) { handleChange();return const_cast<JoinPruneGroup&>(const_cast<PimJoinPrune*>(this)->getJoinPruneGroups(k));}
    virtual void setJoinPruneGroups(size_t k, const JoinPruneGroup& joinPruneGroups);
    virtual void insertJoinPruneGroups(size_t k, const JoinPruneGroup& joinPruneGroups);
    [[deprecated]] void insertJoinPruneGroups(const JoinPruneGroup& joinPruneGroups) {appendJoinPruneGroups(joinPruneGroups);}
    virtual void appendJoinPruneGroups(const JoinPruneGroup& joinPruneGroups);
    virtual void eraseJoinPruneGroups(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimJoinPrune& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimJoinPrune& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:178</tt> by opp_msgtool.
 * <pre>
 * // Assert message
 * // DM, SM
 * class PimAssert extends PimPacket
 * {
 *     type = Assert;
 *     EncodedGroupAddress groupAddress;
 *     EncodedUnicastAddress sourceAddress;
 *     bool R;
 *     int metric;
 *     int metricPreference;
 * }
 * </pre>
 */
class INET_API PimAssert : public ::inet::PimPacket
{
  protected:
    EncodedGroupAddress groupAddress;
    EncodedUnicastAddress sourceAddress;
    bool R = false;
    int metric = 0;
    int metricPreference = 0;

  private:
    void copy(const PimAssert& other);

  protected:
    bool operator==(const PimAssert&) = delete;

  public:
    PimAssert();
    PimAssert(const PimAssert& other);
    virtual ~PimAssert();
    PimAssert& operator=(const PimAssert& other);
    virtual PimAssert *dup() const override {return new PimAssert(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const EncodedGroupAddress& getGroupAddress() const;
    virtual EncodedGroupAddress& getGroupAddressForUpdate() { handleChange();return const_cast<EncodedGroupAddress&>(const_cast<PimAssert*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const EncodedGroupAddress& groupAddress);

    virtual const EncodedUnicastAddress& getSourceAddress() const;
    virtual EncodedUnicastAddress& getSourceAddressForUpdate() { handleChange();return const_cast<EncodedUnicastAddress&>(const_cast<PimAssert*>(this)->getSourceAddress());}
    virtual void setSourceAddress(const EncodedUnicastAddress& sourceAddress);

    virtual bool getR() const;
    virtual void setR(bool R);

    virtual int getMetric() const;
    virtual void setMetric(int metric);

    virtual int getMetricPreference() const;
    virtual void setMetricPreference(int metricPreference);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimAssert& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimAssert& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:190</tt> by opp_msgtool.
 * <pre>
 * // Graft message, only message send by unicast
 * // DM
 * class PimGraft extends PimJoinPrune
 * {
 *     type = Graft;
 *     holdTime = 0;
 * }
 * 
 * // GraftAck message
 * // DM
 * // create a PimGraft, then set type = GraftAck
 * </pre>
 */
class INET_API PimGraft : public ::inet::PimJoinPrune
{
  protected:

  private:
    void copy(const PimGraft& other);

  protected:
    bool operator==(const PimGraft&) = delete;

  public:
    PimGraft();
    PimGraft(const PimGraft& other);
    virtual ~PimGraft();
    PimGraft& operator=(const PimGraft& other);
    virtual PimGraft *dup() const override {return new PimGraft(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimGraft& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimGraft& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:202</tt> by opp_msgtool.
 * <pre>
 * // State Refresh message
 * // DM
 * class PimStateRefresh extends PimPacket
 * {
 *     type = StateRefresh;
 *     EncodedGroupAddress groupAddress;
 *     EncodedUnicastAddress sourceAddress;
 *     EncodedUnicastAddress originatorAddress;
 *     bool R;
 *     int metricPreference;
 *     int metric;
 *     short maskLen;
 *     short ttl;
 *     bool P;
 *     bool N;
 *     bool O;
 *     short reserved2;
 *     short interval;
 * }
 * </pre>
 */
class INET_API PimStateRefresh : public ::inet::PimPacket
{
  protected:
    EncodedGroupAddress groupAddress;
    EncodedUnicastAddress sourceAddress;
    EncodedUnicastAddress originatorAddress;
    bool R = false;
    int metricPreference = 0;
    int metric = 0;
    short maskLen = 0;
    short ttl = 0;
    bool P = false;
    bool N = false;
    bool O = false;
    short reserved2 = 0;
    short interval = 0;

  private:
    void copy(const PimStateRefresh& other);

  protected:
    bool operator==(const PimStateRefresh&) = delete;

  public:
    PimStateRefresh();
    PimStateRefresh(const PimStateRefresh& other);
    virtual ~PimStateRefresh();
    PimStateRefresh& operator=(const PimStateRefresh& other);
    virtual PimStateRefresh *dup() const override {return new PimStateRefresh(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const EncodedGroupAddress& getGroupAddress() const;
    virtual EncodedGroupAddress& getGroupAddressForUpdate() { handleChange();return const_cast<EncodedGroupAddress&>(const_cast<PimStateRefresh*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const EncodedGroupAddress& groupAddress);

    virtual const EncodedUnicastAddress& getSourceAddress() const;
    virtual EncodedUnicastAddress& getSourceAddressForUpdate() { handleChange();return const_cast<EncodedUnicastAddress&>(const_cast<PimStateRefresh*>(this)->getSourceAddress());}
    virtual void setSourceAddress(const EncodedUnicastAddress& sourceAddress);

    virtual const EncodedUnicastAddress& getOriginatorAddress() const;
    virtual EncodedUnicastAddress& getOriginatorAddressForUpdate() { handleChange();return const_cast<EncodedUnicastAddress&>(const_cast<PimStateRefresh*>(this)->getOriginatorAddress());}
    virtual void setOriginatorAddress(const EncodedUnicastAddress& originatorAddress);

    virtual bool getR() const;
    virtual void setR(bool R);

    virtual int getMetricPreference() const;
    virtual void setMetricPreference(int metricPreference);

    virtual int getMetric() const;
    virtual void setMetric(int metric);

    virtual short getMaskLen() const;
    virtual void setMaskLen(short maskLen);

    virtual short getTtl() const;
    virtual void setTtl(short ttl);

    virtual bool getP() const;
    virtual void setP(bool P);

    virtual bool getN() const;
    virtual void setN(bool N);

    virtual bool getO() const;
    virtual void setO(bool O);

    virtual short getReserved2() const;
    virtual void setReserved2(short reserved2);

    virtual short getInterval() const;
    virtual void setInterval(short interval);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimStateRefresh& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimStateRefresh& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:221</tt> by opp_msgtool.
 * <pre>
 * // Register message
 * // SM
 * class PimRegister extends PimPacket
 * {
 *     type = Register;
 *     bool B;
 *     bool N;
 *     uint32_t reserved2;
 * }
 * </pre>
 */
class INET_API PimRegister : public ::inet::PimPacket
{
  protected:
    bool B = false;
    bool N = false;
    uint32_t reserved2 = 0;

  private:
    void copy(const PimRegister& other);

  protected:
    bool operator==(const PimRegister&) = delete;

  public:
    PimRegister();
    PimRegister(const PimRegister& other);
    virtual ~PimRegister();
    PimRegister& operator=(const PimRegister& other);
    virtual PimRegister *dup() const override {return new PimRegister(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getB() const;
    virtual void setB(bool B);

    virtual bool getN() const;
    virtual void setN(bool N);

    virtual uint32_t getReserved2() const;
    virtual void setReserved2(uint32_t reserved2);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimRegister& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimRegister& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/routing/pim/PimPacket.msg:231</tt> by opp_msgtool.
 * <pre>
 * // Register-Stop message
 * // SM
 * class PimRegisterStop extends PimPacket
 * {
 *     type = RegisterStop;
 *     EncodedGroupAddress groupAddress;
 *     EncodedUnicastAddress sourceAddress;
 * }
 * </pre>
 */
class INET_API PimRegisterStop : public ::inet::PimPacket
{
  protected:
    EncodedGroupAddress groupAddress;
    EncodedUnicastAddress sourceAddress;

  private:
    void copy(const PimRegisterStop& other);

  protected:
    bool operator==(const PimRegisterStop&) = delete;

  public:
    PimRegisterStop();
    PimRegisterStop(const PimRegisterStop& other);
    virtual ~PimRegisterStop();
    PimRegisterStop& operator=(const PimRegisterStop& other);
    virtual PimRegisterStop *dup() const override {return new PimRegisterStop(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const EncodedGroupAddress& getGroupAddress() const;
    virtual EncodedGroupAddress& getGroupAddressForUpdate() { handleChange();return const_cast<EncodedGroupAddress&>(const_cast<PimRegisterStop*>(this)->getGroupAddress());}
    virtual void setGroupAddress(const EncodedGroupAddress& groupAddress);

    virtual const EncodedUnicastAddress& getSourceAddress() const;
    virtual EncodedUnicastAddress& getSourceAddressForUpdate() { handleChange();return const_cast<EncodedUnicastAddress&>(const_cast<PimRegisterStop*>(this)->getSourceAddress());}
    virtual void setSourceAddress(const EncodedUnicastAddress& sourceAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const PimRegisterStop& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, PimRegisterStop& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

inline any_ptr toAnyPtr(const inet::EncodedUnicastAddress *p) {return any_ptr(p);}
template<> inline inet::EncodedUnicastAddress *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::EncodedUnicastAddress>(); }
inline any_ptr toAnyPtr(const inet::EncodedGroupAddress *p) {return any_ptr(p);}
template<> inline inet::EncodedGroupAddress *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::EncodedGroupAddress>(); }
inline any_ptr toAnyPtr(const inet::EncodedSourceAddress *p) {return any_ptr(p);}
template<> inline inet::EncodedSourceAddress *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::EncodedSourceAddress>(); }
template<> inline inet::HelloOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::HelloOption*>(ptr.get<cObject>()); }
template<> inline inet::HoldtimeOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::HoldtimeOption*>(ptr.get<cObject>()); }
template<> inline inet::LanPruneDelayOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::LanPruneDelayOption*>(ptr.get<cObject>()); }
template<> inline inet::DrPriorityOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::DrPriorityOption*>(ptr.get<cObject>()); }
template<> inline inet::GenerationIdOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::GenerationIdOption*>(ptr.get<cObject>()); }
template<> inline inet::AddressListOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::AddressListOption*>(ptr.get<cObject>()); }
template<> inline inet::PimPacket *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimPacket*>(ptr.get<cObject>()); }
template<> inline inet::PimHello *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimHello*>(ptr.get<cObject>()); }
template<> inline inet::JoinPruneGroup *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::JoinPruneGroup*>(ptr.get<cObject>()); }
template<> inline inet::PimJoinPrune *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimJoinPrune*>(ptr.get<cObject>()); }
template<> inline inet::PimAssert *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimAssert*>(ptr.get<cObject>()); }
template<> inline inet::PimGraft *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimGraft*>(ptr.get<cObject>()); }
template<> inline inet::PimStateRefresh *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimStateRefresh*>(ptr.get<cObject>()); }
template<> inline inet::PimRegister *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimRegister*>(ptr.get<cObject>()); }
template<> inline inet::PimRegisterStop *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::PimRegisterStop*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_PIMPACKET_M_H


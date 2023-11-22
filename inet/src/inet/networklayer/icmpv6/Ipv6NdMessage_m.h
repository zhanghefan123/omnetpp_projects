//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/networklayer/icmpv6/Ipv6NdMessage.msg.
//

#ifndef __INET_IPV6NDMESSAGE_M_H
#define __INET_IPV6NDMESSAGE_M_H

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

class Ipv6NdOption;
class Ipv6NdSourceTargetLinkLayerAddress;
class Ipv6NdSourceLinkLayerAddress;
class Ipv6NdTargetLinkLayerAddress;
class Ipv6NdPrefixInformation;
class Ipv6NdMtu;
class Mipv6NdAdvertisementInterval;
class Mipv6HaInformation;
class Ipv6NdOptions;
class Ipv6NdMessage;
class Ipv6RouterSolicitation;
class Ipv6RouterAdvertisement;
class Ipv6NeighbourSolicitation;
class Ipv6NeighbourAdvertisement;
class Ipv6Redirect;
class Ipv6NdControlInfo;

}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/linklayer/common/MacAddress_m.h" // import inet.linklayer.common.MacAddress

#include "inet/networklayer/icmpv6/Icmpv6Header_m.h" // import inet.networklayer.icmpv6.Icmpv6Header

#include "inet/networklayer/contract/ipv6/Ipv6Address_m.h" // import inet.networklayer.contract.ipv6.Ipv6Address


namespace inet {

// cplusplus {{
const B IPv6ND_LINK_LAYER_ADDRESS_OPTION_LENGTH = B(8);    // RFC 2461, Section 4.6.1. Source/Target Link-layer Address
const B IPv6ND_PREFIX_INFORMATION_OPTION_LENGTH = B(32);   // RFC 2461, Section 4.6.2. Prefix Information
const B IPv6ND_REDIRECTED_HEADER_OPTION_LENGTH = B(8);     // 8 + redirected packet, RFC 2461, Section 4.6.3. Redirected Header.
                                                           // The original packet truncated to ensure that the size of the redirect message does not exceed 1280 octets.
const B IPv6ND_MTU_OPTION_LENGTH = B(8);                   // RFC 2461, Section 4.6.4. MTU
// }}

/**
 * Enum generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:39</tt> by opp_msgtool.
 * <pre>
 * // TLB options (type, length, bytes), length must be divisible by eight, max value is 8*255
 * // Type codes:          // RFC 2461
 * enum Ipv6NdOptionTypes
 * {
 *     IPv6ND_SOURCE_LINK_LAYER_ADDR_OPTION = 1;
 *     IPv6ND_TARGET_LINK_LAYER_ADDR_OPTION = 2;
 *     IPv6ND_PREFIX_INFORMATION = 3;
 *     IPv6ND_REDIRECTED_HEADER = 4;
 *     IPv6ND_MTU = 5;
 *     IPv6ND_ADVERTISEMENT_INTERVAL = 7;    // RFC 3775 Section 7.3
 *     IPv6ND_HOME_AGENT_INFORMATION_OPTION = 8;    // RFC 3775 Section 7.4
 * }
 * </pre>
 */
enum Ipv6NdOptionTypes {
    IPv6ND_SOURCE_LINK_LAYER_ADDR_OPTION = 1,
    IPv6ND_TARGET_LINK_LAYER_ADDR_OPTION = 2,
    IPv6ND_PREFIX_INFORMATION = 3,
    IPv6ND_REDIRECTED_HEADER = 4,
    IPv6ND_MTU = 5,
    IPv6ND_ADVERTISEMENT_INTERVAL = 7,
    IPv6ND_HOME_AGENT_INFORMATION_OPTION = 8
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdOptionTypes& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdOptionTypes& e) { int n; b->unpack(n); e = static_cast<Ipv6NdOptionTypes>(n); }

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:50</tt> by opp_msgtool.
 * <pre>
 * class Ipv6NdOption extends cObject
 * {
 *     Ipv6NdOptionTypes type = static_cast<Ipv6NdOptionTypes>(0);    // 1 byte, 0 is invalid
 *     short optionLength = 0;    // The length of the option in units of 8 octets, 0 is invalid.    // 1 byte
 *     char paddingBytes[];    // padding bytes on end of option
 * }
 * </pre>
 */
class INET_API Ipv6NdOption : public ::omnetpp::cObject
{
  protected:
    Ipv6NdOptionTypes type = static_cast<Ipv6NdOptionTypes>(0);
    short optionLength = 0;
    char *paddingBytes = nullptr;
    size_t paddingBytes_arraysize = 0;

  private:
    void copy(const Ipv6NdOption& other);

  protected:
    bool operator==(const Ipv6NdOption&) = delete;

  public:
    Ipv6NdOption();
    Ipv6NdOption(const Ipv6NdOption& other);
    virtual ~Ipv6NdOption();
    Ipv6NdOption& operator=(const Ipv6NdOption& other);
    virtual Ipv6NdOption *dup() const override {return new Ipv6NdOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual Ipv6NdOptionTypes getType() const;
    virtual void setType(Ipv6NdOptionTypes type);

    virtual short getOptionLength() const;
    virtual void setOptionLength(short optionLength);

    virtual void setPaddingBytesArraySize(size_t size);
    virtual size_t getPaddingBytesArraySize() const;
    virtual char getPaddingBytes(size_t k) const;
    virtual void setPaddingBytes(size_t k, char paddingBytes);
    virtual void insertPaddingBytes(size_t k, char paddingBytes);
    [[deprecated]] void insertPaddingBytes(char paddingBytes) {appendPaddingBytes(paddingBytes);}
    virtual void appendPaddingBytes(char paddingBytes);
    virtual void erasePaddingBytes(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:57</tt> by opp_msgtool.
 * <pre>
 * class Ipv6NdSourceTargetLinkLayerAddress extends Ipv6NdOption
 * {
 *     optionLength = 1;    // 8 byte ( when using MacAddress)
 *     MacAddress linkLayerAddress;
 * }
 * </pre>
 */
class INET_API Ipv6NdSourceTargetLinkLayerAddress : public ::inet::Ipv6NdOption
{
  protected:
    MacAddress linkLayerAddress;

  private:
    void copy(const Ipv6NdSourceTargetLinkLayerAddress& other);

  protected:
    bool operator==(const Ipv6NdSourceTargetLinkLayerAddress&) = delete;

  public:
    Ipv6NdSourceTargetLinkLayerAddress();
    Ipv6NdSourceTargetLinkLayerAddress(const Ipv6NdSourceTargetLinkLayerAddress& other);
    virtual ~Ipv6NdSourceTargetLinkLayerAddress();
    Ipv6NdSourceTargetLinkLayerAddress& operator=(const Ipv6NdSourceTargetLinkLayerAddress& other);
    virtual Ipv6NdSourceTargetLinkLayerAddress *dup() const override {return new Ipv6NdSourceTargetLinkLayerAddress(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const MacAddress& getLinkLayerAddress() const;
    virtual MacAddress& getLinkLayerAddressForUpdate() { return const_cast<MacAddress&>(const_cast<Ipv6NdSourceTargetLinkLayerAddress*>(this)->getLinkLayerAddress());}
    virtual void setLinkLayerAddress(const MacAddress& linkLayerAddress);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdSourceTargetLinkLayerAddress& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdSourceTargetLinkLayerAddress& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:63</tt> by opp_msgtool.
 * <pre>
 * class Ipv6NdSourceLinkLayerAddress extends Ipv6NdSourceTargetLinkLayerAddress
 * {
 *     type = IPv6ND_SOURCE_LINK_LAYER_ADDR_OPTION;
 * }
 * </pre>
 */
class INET_API Ipv6NdSourceLinkLayerAddress : public ::inet::Ipv6NdSourceTargetLinkLayerAddress
{
  protected:

  private:
    void copy(const Ipv6NdSourceLinkLayerAddress& other);

  protected:
    bool operator==(const Ipv6NdSourceLinkLayerAddress&) = delete;

  public:
    Ipv6NdSourceLinkLayerAddress();
    Ipv6NdSourceLinkLayerAddress(const Ipv6NdSourceLinkLayerAddress& other);
    virtual ~Ipv6NdSourceLinkLayerAddress();
    Ipv6NdSourceLinkLayerAddress& operator=(const Ipv6NdSourceLinkLayerAddress& other);
    virtual Ipv6NdSourceLinkLayerAddress *dup() const override {return new Ipv6NdSourceLinkLayerAddress(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdSourceLinkLayerAddress& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdSourceLinkLayerAddress& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:68</tt> by opp_msgtool.
 * <pre>
 * class Ipv6NdTargetLinkLayerAddress extends Ipv6NdSourceTargetLinkLayerAddress
 * {
 *     type = IPv6ND_TARGET_LINK_LAYER_ADDR_OPTION;
 * }
 * </pre>
 */
class INET_API Ipv6NdTargetLinkLayerAddress : public ::inet::Ipv6NdSourceTargetLinkLayerAddress
{
  protected:

  private:
    void copy(const Ipv6NdTargetLinkLayerAddress& other);

  protected:
    bool operator==(const Ipv6NdTargetLinkLayerAddress&) = delete;

  public:
    Ipv6NdTargetLinkLayerAddress();
    Ipv6NdTargetLinkLayerAddress(const Ipv6NdTargetLinkLayerAddress& other);
    virtual ~Ipv6NdTargetLinkLayerAddress();
    Ipv6NdTargetLinkLayerAddress& operator=(const Ipv6NdTargetLinkLayerAddress& other);
    virtual Ipv6NdTargetLinkLayerAddress *dup() const override {return new Ipv6NdTargetLinkLayerAddress(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdTargetLinkLayerAddress& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdTargetLinkLayerAddress& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:78</tt> by opp_msgtool.
 * <pre>
 * //
 * // IPv6ND Prefix Information
 * // RFC 2461 / RFC 4861 Section 4.6.2
 * // RFC 3775 Section 7.2 (routerAddressFlag)
 * //
 * class Ipv6NdPrefixInformation extends Ipv6NdOption
 * {
 *     type = IPv6ND_PREFIX_INFORMATION;
 *     optionLength = 4;
 *     unsigned short prefixLength;    // 0..128
 *     bool onlinkFlag;        //L-bit
 *     bool autoAddressConfFlag;    //A-bit
 *     bool routerAddressFlag;        //R-bit: used in case of MIPv6 when the H-bit is set
 *     unsigned int reserved1 = 0;
 *     uint32_t validLifetime;    // seconds
 *     uint32_t preferredLifetime;    // seconds
 *     uint32_t reserved2 = 0;
 *     Ipv6Address prefix;
 * }
 * </pre>
 */
class INET_API Ipv6NdPrefixInformation : public ::inet::Ipv6NdOption
{
  protected:
    unsigned short prefixLength = 0;
    bool onlinkFlag = false;
    bool autoAddressConfFlag = false;
    bool routerAddressFlag = false;
    unsigned int reserved1 = 0;
    uint32_t validLifetime = 0;
    uint32_t preferredLifetime = 0;
    uint32_t reserved2 = 0;
    Ipv6Address prefix;

  private:
    void copy(const Ipv6NdPrefixInformation& other);

  protected:
    bool operator==(const Ipv6NdPrefixInformation&) = delete;

  public:
    Ipv6NdPrefixInformation();
    Ipv6NdPrefixInformation(const Ipv6NdPrefixInformation& other);
    virtual ~Ipv6NdPrefixInformation();
    Ipv6NdPrefixInformation& operator=(const Ipv6NdPrefixInformation& other);
    virtual Ipv6NdPrefixInformation *dup() const override {return new Ipv6NdPrefixInformation(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual unsigned short getPrefixLength() const;
    virtual void setPrefixLength(unsigned short prefixLength);

    virtual bool getOnlinkFlag() const;
    virtual void setOnlinkFlag(bool onlinkFlag);

    virtual bool getAutoAddressConfFlag() const;
    virtual void setAutoAddressConfFlag(bool autoAddressConfFlag);

    virtual bool getRouterAddressFlag() const;
    virtual void setRouterAddressFlag(bool routerAddressFlag);

    virtual unsigned int getReserved1() const;
    virtual void setReserved1(unsigned int reserved1);

    virtual uint32_t getValidLifetime() const;
    virtual void setValidLifetime(uint32_t validLifetime);

    virtual uint32_t getPreferredLifetime() const;
    virtual void setPreferredLifetime(uint32_t preferredLifetime);

    virtual uint32_t getReserved2() const;
    virtual void setReserved2(uint32_t reserved2);

    virtual const Ipv6Address& getPrefix() const;
    virtual Ipv6Address& getPrefixForUpdate() { return const_cast<Ipv6Address&>(const_cast<Ipv6NdPrefixInformation*>(this)->getPrefix());}
    virtual void setPrefix(const Ipv6Address& prefix);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdPrefixInformation& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdPrefixInformation& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:93</tt> by opp_msgtool.
 * <pre>
 * class Ipv6NdMtu extends Ipv6NdOption
 * {
 *     type = IPv6ND_MTU;
 *     optionLength = 1;
 *     uint16_t reserved;
 *     uint32_t mtu;
 * }
 * </pre>
 */
class INET_API Ipv6NdMtu : public ::inet::Ipv6NdOption
{
  protected:
    uint16_t reserved = 0;
    uint32_t mtu = 0;

  private:
    void copy(const Ipv6NdMtu& other);

  protected:
    bool operator==(const Ipv6NdMtu&) = delete;

  public:
    Ipv6NdMtu();
    Ipv6NdMtu(const Ipv6NdMtu& other);
    virtual ~Ipv6NdMtu();
    Ipv6NdMtu& operator=(const Ipv6NdMtu& other);
    virtual Ipv6NdMtu *dup() const override {return new Ipv6NdMtu(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint16_t getReserved() const;
    virtual void setReserved(uint16_t reserved);

    virtual uint32_t getMtu() const;
    virtual void setMtu(uint32_t mtu);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdMtu& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdMtu& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:104</tt> by opp_msgtool.
 * <pre>
 * // MIPv6 New Advertisement Interval Option
 * // RFC 3775 Section 7.3
 * //
 * class Mipv6NdAdvertisementInterval extends Ipv6NdOption
 * {
 *     type = IPv6ND_ADVERTISEMENT_INTERVAL;
 *     optionLength = 1;
 *     uint16_t reserved;
 *     uint32_t advertisementInterval;    // milliseconds
 * }
 * </pre>
 */
class INET_API Mipv6NdAdvertisementInterval : public ::inet::Ipv6NdOption
{
  protected:
    uint16_t reserved = 0;
    uint32_t advertisementInterval = 0;

  private:
    void copy(const Mipv6NdAdvertisementInterval& other);

  protected:
    bool operator==(const Mipv6NdAdvertisementInterval&) = delete;

  public:
    Mipv6NdAdvertisementInterval();
    Mipv6NdAdvertisementInterval(const Mipv6NdAdvertisementInterval& other);
    virtual ~Mipv6NdAdvertisementInterval();
    Mipv6NdAdvertisementInterval& operator=(const Mipv6NdAdvertisementInterval& other);
    virtual Mipv6NdAdvertisementInterval *dup() const override {return new Mipv6NdAdvertisementInterval(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint16_t getReserved() const;
    virtual void setReserved(uint16_t reserved);

    virtual uint32_t getAdvertisementInterval() const;
    virtual void setAdvertisementInterval(uint32_t advertisementInterval);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Mipv6NdAdvertisementInterval& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Mipv6NdAdvertisementInterval& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:114</tt> by opp_msgtool.
 * <pre>
 * //MIPv6 Home Agent Information Option
 * //RFC 3775 Section 7.4
 * class Mipv6HaInformation extends Ipv6NdOption
 * {
 *     type = IPv6ND_HOME_AGENT_INFORMATION_OPTION;
 *     optionLength = 1;
 *     uint16_t reserved;
 *     uint16_t homeAgentPreference;
 *     uint16_t homeAgentLifetime;    // seconds
 * }
 * </pre>
 */
class INET_API Mipv6HaInformation : public ::inet::Ipv6NdOption
{
  protected:
    uint16_t reserved = 0;
    uint16_t homeAgentPreference = 0;
    uint16_t homeAgentLifetime = 0;

  private:
    void copy(const Mipv6HaInformation& other);

  protected:
    bool operator==(const Mipv6HaInformation&) = delete;

  public:
    Mipv6HaInformation();
    Mipv6HaInformation(const Mipv6HaInformation& other);
    virtual ~Mipv6HaInformation();
    Mipv6HaInformation& operator=(const Mipv6HaInformation& other);
    virtual Mipv6HaInformation *dup() const override {return new Mipv6HaInformation(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint16_t getReserved() const;
    virtual void setReserved(uint16_t reserved);

    virtual uint16_t getHomeAgentPreference() const;
    virtual void setHomeAgentPreference(uint16_t homeAgentPreference);

    virtual uint16_t getHomeAgentLifetime() const;
    virtual void setHomeAgentLifetime(uint16_t homeAgentLifetime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Mipv6HaInformation& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Mipv6HaInformation& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:122</tt> by opp_msgtool.
 * <pre>
 * class Ipv6NdOptions extends cObject
 * {
 *     // TLV Options:
 *     Ipv6NdOption *option[] \@owned;  // on end of message
 * }
 * </pre>
 */
class INET_API Ipv6NdOptions : public ::omnetpp::cObject
{
  protected:
    Ipv6NdOption * *option = nullptr;
    size_t option_arraysize = 0;

  private:
    void copy(const Ipv6NdOptions& other);

  protected:
    bool operator==(const Ipv6NdOptions&) = delete;

  public:
    Ipv6NdOptions();
    Ipv6NdOptions(const Ipv6NdOptions& other);
    virtual ~Ipv6NdOptions();
    Ipv6NdOptions& operator=(const Ipv6NdOptions& other);
    virtual Ipv6NdOptions *dup() const override {return new Ipv6NdOptions(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual void setOptionArraySize(size_t size);
    virtual size_t getOptionArraySize() const;
    virtual const Ipv6NdOption * getOption(size_t k) const;
    virtual Ipv6NdOption * getOptionForUpdate(size_t k) { return const_cast<Ipv6NdOption *>(const_cast<Ipv6NdOptions*>(this)->getOption(k));}
    virtual void setOption(size_t k, Ipv6NdOption * option);
    virtual Ipv6NdOption * removeOption(size_t k);
    [[deprecated]] Ipv6NdOption * dropOption(size_t k) {return removeOption(k);}
    virtual void insertOption(size_t k, Ipv6NdOption * option);
    [[deprecated]] void insertOption(Ipv6NdOption * option) {appendOption(option);}
    virtual void appendOption(Ipv6NdOption * option);
    virtual void eraseOption(size_t k);


    virtual const Ipv6NdOption *findOption(Ipv6NdOptionTypes t) const;
    virtual Ipv6NdOption *findOptionForUpdate(Ipv6NdOptionTypes t);
    virtual void insertUniqueOption(size_t k, Ipv6NdOption * option);
    virtual void insertUniqueOption(Ipv6NdOption * option) { insertUniqueOption(option_arraysize, option); }
#if (OMNETPP_BUILDNUM < 1530)
  public:
    void appendOption(Ipv6NdOption *option) { insertOption(option); }
#endif
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdOptions& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdOptions& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:150</tt> by opp_msgtool.
 * <pre>
 * //
 * // Neighbour Discovery for Ipv6.
 * // RFC 2461
 * //
 * // ICMP fields inherited from ~Icmpv6Header:
 * //    - Type
 * //
 * // ICMP fields not implemented:
 * //    - Checksum
 * //    - Reserved
 * //
 * class Ipv6NdMessage extends Icmpv6Header
 * {
 *     int code = 0;
 * }
 * </pre>
 */
class INET_API Ipv6NdMessage : public ::inet::Icmpv6Header
{
  protected:
    int code = 0;

  private:
    void copy(const Ipv6NdMessage& other);

  protected:
    bool operator==(const Ipv6NdMessage&) = delete;

  public:
    Ipv6NdMessage();
    Ipv6NdMessage(const Ipv6NdMessage& other);
    virtual ~Ipv6NdMessage();
    Ipv6NdMessage& operator=(const Ipv6NdMessage& other);
    virtual Ipv6NdMessage *dup() const override {return new Ipv6NdMessage(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getCode() const;
    virtual void setCode(int code);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdMessage& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdMessage& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:159</tt> by opp_msgtool.
 * <pre>
 * //
 * // Router Solicitation Message Format
 * // RFC 4861 Section 4.1
 * //
 * class Ipv6RouterSolicitation extends Ipv6NdMessage
 * {
 *     chunkLength = B(8);    // without options
 *     type = ICMPv6_ROUTER_SOL;
 *     //Additional ICMP fields
 *     uint32_t reserved = 0;
 *     Ipv6NdOptions options;
 * }
 * </pre>
 */
class INET_API Ipv6RouterSolicitation : public ::inet::Ipv6NdMessage
{
  protected:
    uint32_t reserved = 0;
    Ipv6NdOptions options;

  private:
    void copy(const Ipv6RouterSolicitation& other);

  protected:
    bool operator==(const Ipv6RouterSolicitation&) = delete;

  public:
    Ipv6RouterSolicitation();
    Ipv6RouterSolicitation(const Ipv6RouterSolicitation& other);
    virtual ~Ipv6RouterSolicitation();
    Ipv6RouterSolicitation& operator=(const Ipv6RouterSolicitation& other);
    virtual Ipv6RouterSolicitation *dup() const override {return new Ipv6RouterSolicitation(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint32_t getReserved() const;
    virtual void setReserved(uint32_t reserved);

    virtual const Ipv6NdOptions& getOptions() const;
    virtual Ipv6NdOptions& getOptionsForUpdate() { handleChange();return const_cast<Ipv6NdOptions&>(const_cast<Ipv6RouterSolicitation*>(this)->getOptions());}
    virtual void setOptions(const Ipv6NdOptions& options);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6RouterSolicitation& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6RouterSolicitation& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:173</tt> by opp_msgtool.
 * <pre>
 * //
 * // Router Advertisement Message Format
 * // RFC 2461 Section 4.2
 * // RFC 3775 Section 7.1, RFC 5175 Section 3. (homeAgentFlag)
 * //
 * class Ipv6RouterAdvertisement extends Ipv6NdMessage
 * {
 *     chunkLength = B(16);    // without options
 *     type = ICMPv6_ROUTER_AD;
 *     //Additional ICMP fields
 *     unsigned short curHopLimit;
 * 
 *     bool managedAddrConfFlag;    //M-bit
 *     bool otherStatefulConfFlag;    //O-bit
 *     bool homeAgentFlag = false;        //H-bit
 *     uint8_t reserved = 0;
 * 
 *     unsigned short routerLifetime;  // [s] 0 indicates router is not a default router
 *     unsigned int reachableTime;     // [ms]
 *     unsigned int retransTimer;      // [ms]
 *     Ipv6NdOptions options;
 * }
 * </pre>
 */
class INET_API Ipv6RouterAdvertisement : public ::inet::Ipv6NdMessage
{
  protected:
    unsigned short curHopLimit = 0;
    bool managedAddrConfFlag = false;
    bool otherStatefulConfFlag = false;
    bool homeAgentFlag = false;
    uint8_t reserved = 0;
    unsigned short routerLifetime = 0;
    unsigned int reachableTime = 0;
    unsigned int retransTimer = 0;
    Ipv6NdOptions options;

  private:
    void copy(const Ipv6RouterAdvertisement& other);

  protected:
    bool operator==(const Ipv6RouterAdvertisement&) = delete;

  public:
    Ipv6RouterAdvertisement();
    Ipv6RouterAdvertisement(const Ipv6RouterAdvertisement& other);
    virtual ~Ipv6RouterAdvertisement();
    Ipv6RouterAdvertisement& operator=(const Ipv6RouterAdvertisement& other);
    virtual Ipv6RouterAdvertisement *dup() const override {return new Ipv6RouterAdvertisement(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual unsigned short getCurHopLimit() const;
    virtual void setCurHopLimit(unsigned short curHopLimit);

    virtual bool getManagedAddrConfFlag() const;
    virtual void setManagedAddrConfFlag(bool managedAddrConfFlag);

    virtual bool getOtherStatefulConfFlag() const;
    virtual void setOtherStatefulConfFlag(bool otherStatefulConfFlag);

    virtual bool getHomeAgentFlag() const;
    virtual void setHomeAgentFlag(bool homeAgentFlag);

    virtual uint8_t getReserved() const;
    virtual void setReserved(uint8_t reserved);

    virtual unsigned short getRouterLifetime() const;
    virtual void setRouterLifetime(unsigned short routerLifetime);

    virtual unsigned int getReachableTime() const;
    virtual void setReachableTime(unsigned int reachableTime);

    virtual unsigned int getRetransTimer() const;
    virtual void setRetransTimer(unsigned int retransTimer);

    virtual const Ipv6NdOptions& getOptions() const;
    virtual Ipv6NdOptions& getOptionsForUpdate() { handleChange();return const_cast<Ipv6NdOptions&>(const_cast<Ipv6RouterAdvertisement*>(this)->getOptions());}
    virtual void setOptions(const Ipv6NdOptions& options);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6RouterAdvertisement& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6RouterAdvertisement& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:195</tt> by opp_msgtool.
 * <pre>
 * //
 * // Neighbour Solicitation Message Format
 * // RFC 4861 Section 4.3
 * //
 * class Ipv6NeighbourSolicitation extends Ipv6NdMessage
 * {
 *     chunkLength = B(24);    // without options
 *     type = ICMPv6_NEIGHBOUR_SOL;
 *     //Additional ICMP fields
 *     uint32_t reserved = 0;
 *     Ipv6Address targetAddress;// MUST NOT be a multicast address.
 *     Ipv6NdOptions options;
 * }
 * </pre>
 */
class INET_API Ipv6NeighbourSolicitation : public ::inet::Ipv6NdMessage
{
  protected:
    uint32_t reserved = 0;
    Ipv6Address targetAddress;
    Ipv6NdOptions options;

  private:
    void copy(const Ipv6NeighbourSolicitation& other);

  protected:
    bool operator==(const Ipv6NeighbourSolicitation&) = delete;

  public:
    Ipv6NeighbourSolicitation();
    Ipv6NeighbourSolicitation(const Ipv6NeighbourSolicitation& other);
    virtual ~Ipv6NeighbourSolicitation();
    Ipv6NeighbourSolicitation& operator=(const Ipv6NeighbourSolicitation& other);
    virtual Ipv6NeighbourSolicitation *dup() const override {return new Ipv6NeighbourSolicitation(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint32_t getReserved() const;
    virtual void setReserved(uint32_t reserved);

    virtual const Ipv6Address& getTargetAddress() const;
    virtual Ipv6Address& getTargetAddressForUpdate() { handleChange();return const_cast<Ipv6Address&>(const_cast<Ipv6NeighbourSolicitation*>(this)->getTargetAddress());}
    virtual void setTargetAddress(const Ipv6Address& targetAddress);

    virtual const Ipv6NdOptions& getOptions() const;
    virtual Ipv6NdOptions& getOptionsForUpdate() { handleChange();return const_cast<Ipv6NdOptions&>(const_cast<Ipv6NeighbourSolicitation*>(this)->getOptions());}
    virtual void setOptions(const Ipv6NdOptions& options);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NeighbourSolicitation& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NeighbourSolicitation& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:209</tt> by opp_msgtool.
 * <pre>
 * //
 * // Neighbour Advertisement Message Format
 * // RFC 2461 Section 4.4
 * //
 * class Ipv6NeighbourAdvertisement extends Ipv6NdMessage
 * {
 *     chunkLength = B(24);    // without options
 *     type = ICMPv6_NEIGHBOUR_AD;
 *     //Additional ICMP fields
 *     bool routerFlag;    //R-flag
 *     bool solicitedFlag;    //S-flag
 *     bool overrideFlag;    //O-flag
 *     uint32_t reserved = 0;
 *     Ipv6Address targetAddress;// MUST NOT be a multicast address.
 *     Ipv6NdOptions options;
 * }
 * </pre>
 */
class INET_API Ipv6NeighbourAdvertisement : public ::inet::Ipv6NdMessage
{
  protected:
    bool routerFlag = false;
    bool solicitedFlag = false;
    bool overrideFlag = false;
    uint32_t reserved = 0;
    Ipv6Address targetAddress;
    Ipv6NdOptions options;

  private:
    void copy(const Ipv6NeighbourAdvertisement& other);

  protected:
    bool operator==(const Ipv6NeighbourAdvertisement&) = delete;

  public:
    Ipv6NeighbourAdvertisement();
    Ipv6NeighbourAdvertisement(const Ipv6NeighbourAdvertisement& other);
    virtual ~Ipv6NeighbourAdvertisement();
    Ipv6NeighbourAdvertisement& operator=(const Ipv6NeighbourAdvertisement& other);
    virtual Ipv6NeighbourAdvertisement *dup() const override {return new Ipv6NeighbourAdvertisement(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual bool getRouterFlag() const;
    virtual void setRouterFlag(bool routerFlag);

    virtual bool getSolicitedFlag() const;
    virtual void setSolicitedFlag(bool solicitedFlag);

    virtual bool getOverrideFlag() const;
    virtual void setOverrideFlag(bool overrideFlag);

    virtual uint32_t getReserved() const;
    virtual void setReserved(uint32_t reserved);

    virtual const Ipv6Address& getTargetAddress() const;
    virtual Ipv6Address& getTargetAddressForUpdate() { handleChange();return const_cast<Ipv6Address&>(const_cast<Ipv6NeighbourAdvertisement*>(this)->getTargetAddress());}
    virtual void setTargetAddress(const Ipv6Address& targetAddress);

    virtual const Ipv6NdOptions& getOptions() const;
    virtual Ipv6NdOptions& getOptionsForUpdate() { handleChange();return const_cast<Ipv6NdOptions&>(const_cast<Ipv6NeighbourAdvertisement*>(this)->getOptions());}
    virtual void setOptions(const Ipv6NdOptions& options);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NeighbourAdvertisement& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NeighbourAdvertisement& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:226</tt> by opp_msgtool.
 * <pre>
 * //
 * // Redirect Message Format
 * // RFC 2461 Section 4.5
 * //
 * class Ipv6Redirect extends Ipv6NdMessage
 * {
 *     chunkLength = B(40);    // without options
 *     type = ICMPv6_REDIRECT;
 *     //Additional ICMP fields
 *     Ipv6Address targetAddress;
 *     Ipv6Address destinationAddress;
 *     Ipv6NdOptions options;
 * }
 * </pre>
 */
class INET_API Ipv6Redirect : public ::inet::Ipv6NdMessage
{
  protected:
    Ipv6Address targetAddress;
    Ipv6Address destinationAddress;
    Ipv6NdOptions options;

  private:
    void copy(const Ipv6Redirect& other);

  protected:
    bool operator==(const Ipv6Redirect&) = delete;

  public:
    Ipv6Redirect();
    Ipv6Redirect(const Ipv6Redirect& other);
    virtual ~Ipv6Redirect();
    Ipv6Redirect& operator=(const Ipv6Redirect& other);
    virtual Ipv6Redirect *dup() const override {return new Ipv6Redirect(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const Ipv6Address& getTargetAddress() const;
    virtual Ipv6Address& getTargetAddressForUpdate() { handleChange();return const_cast<Ipv6Address&>(const_cast<Ipv6Redirect*>(this)->getTargetAddress());}
    virtual void setTargetAddress(const Ipv6Address& targetAddress);

    virtual const Ipv6Address& getDestinationAddress() const;
    virtual Ipv6Address& getDestinationAddressForUpdate() { handleChange();return const_cast<Ipv6Address&>(const_cast<Ipv6Redirect*>(this)->getDestinationAddress());}
    virtual void setDestinationAddress(const Ipv6Address& destinationAddress);

    virtual const Ipv6NdOptions& getOptions() const;
    virtual Ipv6NdOptions& getOptionsForUpdate() { handleChange();return const_cast<Ipv6NdOptions&>(const_cast<Ipv6Redirect*>(this)->getOptions());}
    virtual void setOptions(const Ipv6NdOptions& options);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6Redirect& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6Redirect& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/networklayer/icmpv6/Ipv6NdMessage.msg:236</tt> by opp_msgtool.
 * <pre>
 * class Ipv6NdControlInfo extends cObject
 * {
 *     Ipv6Address nextHop;   // next hop address
 *     int interfaceId = -1; // interface on which the datagram should be sent
 *     bool fromHL = false;    // packet came from higher layer
 * }
 * </pre>
 */
class INET_API Ipv6NdControlInfo : public ::omnetpp::cObject
{
  protected:
    Ipv6Address nextHop;
    int interfaceId = -1;
    bool fromHL = false;

  private:
    void copy(const Ipv6NdControlInfo& other);

  protected:
    bool operator==(const Ipv6NdControlInfo&) = delete;

  public:
    Ipv6NdControlInfo();
    Ipv6NdControlInfo(const Ipv6NdControlInfo& other);
    virtual ~Ipv6NdControlInfo();
    Ipv6NdControlInfo& operator=(const Ipv6NdControlInfo& other);
    virtual Ipv6NdControlInfo *dup() const override {return new Ipv6NdControlInfo(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual const Ipv6Address& getNextHop() const;
    virtual Ipv6Address& getNextHopForUpdate() { return const_cast<Ipv6Address&>(const_cast<Ipv6NdControlInfo*>(this)->getNextHop());}
    virtual void setNextHop(const Ipv6Address& nextHop);

    virtual int getInterfaceId() const;
    virtual void setInterfaceId(int interfaceId);

    virtual bool getFromHL() const;
    virtual void setFromHL(bool fromHL);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Ipv6NdControlInfo& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Ipv6NdControlInfo& obj) {obj.parsimUnpack(b);}


}  // namespace inet


namespace omnetpp {

template<> inline inet::Ipv6NdOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdOption*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdSourceTargetLinkLayerAddress *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdSourceTargetLinkLayerAddress*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdSourceLinkLayerAddress *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdSourceLinkLayerAddress*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdTargetLinkLayerAddress *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdTargetLinkLayerAddress*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdPrefixInformation *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdPrefixInformation*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdMtu *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdMtu*>(ptr.get<cObject>()); }
template<> inline inet::Mipv6NdAdvertisementInterval *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Mipv6NdAdvertisementInterval*>(ptr.get<cObject>()); }
template<> inline inet::Mipv6HaInformation *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Mipv6HaInformation*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdOptions *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdOptions*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdMessage *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdMessage*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6RouterSolicitation *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6RouterSolicitation*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6RouterAdvertisement *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6RouterAdvertisement*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NeighbourSolicitation *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NeighbourSolicitation*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NeighbourAdvertisement *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NeighbourAdvertisement*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6Redirect *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6Redirect*>(ptr.get<cObject>()); }
template<> inline inet::Ipv6NdControlInfo *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::Ipv6NdControlInfo*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET_IPV6NDMESSAGE_M_H

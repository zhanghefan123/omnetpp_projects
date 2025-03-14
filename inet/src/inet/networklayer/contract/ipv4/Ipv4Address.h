//
// Copyright (C) 2001  Vincent Oberle (vincent@oberle.com)
// Institute of Telematics, University of Karlsruhe, Germany.
// University Comillas, Madrid, Spain.
// Copyright (C) 2004 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2.1
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//

//
// Author: Vincent Oberle, Jan-March 2001
// Cleanup and rewrite: Andras Varga, 2004
//

#ifndef __INET_IPV4ADDRESS_H
#define __INET_IPV4ADDRESS_H

#include <iostream>
#include <string>

#include "inet/common/INETDefs.h"

namespace inet {

/**
 * TCP/UDP port numbers
 */
const short PORT_UNDEF = 0;
const short PORT_MAX = 0x7fff;

/**
 * Ipv4 address.
 */
class INET_API Ipv4Address
{
  protected:
    // Address is encoded in a single uint32_t in host byte order (e.g. "10.0.0.1" is 0x0A000001)
    uint32_t addr;

  protected:
    // Parses Ipv4 address into the given bytes, and returns true if syntax was OK.
    static bool parseIPAddress(const char *text, unsigned char tobytes[]);
    // Throws error if length is outside 0..32
    static void _checkNetmaskLength(int length);
    // Returns a netmask with the given length (Implementation note: MSVC refuses to shift by 32 bits!)
    static uint32_t _makeNetmask(int length) { return length >= 32 ? 0xffffffffu : ~(0xffffffffu >> length); }

  public:
    /**
     * Ipv4 address category
     *
     * RFC 5735               Special Use Ipv4 Addresses           January 2010
     * 4.  Summary Table
     * Address Block       Present Use                Reference
     * ------------------------------------------------------------------
     * 0.0.0.0/8           "This" Network             RFC 1122, Section 3.2.1.3
     * 10.0.0.0/8          Private-Use Networks       RFC 1918
     * 127.0.0.0/8         Loopback                   RFC 1122, Section 3.2.1.3
     * 169.254.0.0/16      Link Local                 RFC 3927
     * 172.16.0.0/12       Private-Use Networks       RFC 1918
     * 192.0.0.0/24        IETF Protocol Assignments  RFC 5736
     * 192.0.2.0/24        TEST-NET-1                 RFC 5737
     * 192.88.99.0/24      6to4 Relay Anycast         RFC 3068
     * 192.168.0.0/16      Private-Use Networks       RFC 1918
     * 198.18.0.0/15       Network Interconnect
     *                     Device Benchmark Testing   RFC 2544
     * 198.51.100.0/24     TEST-NET-2                 RFC 5737
     * 203.0.113.0/24      TEST-NET-3                 RFC 5737
     * 224.0.0.0/4         Multicast                  RFC 3171
     * 240.0.0.0/4         Reserved for Future Use    RFC 1112, Section 4
     * 255.255.255.255/32  Limited Broadcast          RFC 919, Section 7; RFC 922, Section 7
     */
    enum AddressCategory {
        UNSPECIFIED, // 0.0.0.0
        THIS_NETWORK, // 0.0.0.0/8
        LOOPBACK, // 127.0.0.0/8
        MULTICAST, // 224.0.0.0/4
        BROADCAST, // 255.255.255.255/32
        IETF, // 192.0.0.0/24
        TEST_NET, // 192.0.2.0/24, 198.51.100.0/24, 203.0.113.0/24
        IPv6_TO_IPv4_RELAY, // 192.88.99.0/24
        BENCHMARK, // 198.18.0.0/15
        RESERVED, // 240.0.0.0/4
        LINKLOCAL, // 169.254.0.0/16
        PRIVATE_NETWORK, // 10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16
        GLOBAL
    };

    /** @name Predefined addresses */
    //@{
    static const Ipv4Address UNSPECIFIED_ADDRESS; ///< 0.0.0.0
    static const Ipv4Address LOOPBACK_ADDRESS; ///< 127.0.0.1
    static const Ipv4Address LOOPBACK_NETMASK; ///< 255.0.0.0
    static const Ipv4Address ALLONES_ADDRESS; ///< 255.255.255.255

    static const Ipv4Address ALL_HOSTS_MCAST; ///< 224.0.0.1 All hosts on a subnet
    static const Ipv4Address ALL_ROUTERS_MCAST; ///< 224.0.0.2 All routers on a subnet
    static const Ipv4Address ALL_DVMRP_ROUTERS_MCAST; ///< 224.0.0.4 All DVMRP routers
    static const Ipv4Address ALL_OSPF_ROUTERS_MCAST; ///< 224.0.0.5 All OSPF routers (DR Others)
    static const Ipv4Address ALL_OSPF_DESIGNATED_ROUTERS_MCAST; ///< 224.0.0.6 All OSPF Designated Routers
    static const Ipv4Address ALL_IGMPV3_ROUTERS_MCAST; ///< 224.0.0.22 All IGMPv3 routers
    static const Ipv4Address LL_MANET_ROUTERS; ///< 224.0.0.109 Manet all designated routers
    static const Ipv4Address ALL_RIP_ROUTERS_MCAST;

    static const Ipv4Address DTN_NEIGHBOR_DETECTION_MCAST;// zhf add code for dtn
    //@}

    /** name Constructors, destructor */
    //@{

    /**
     * Default constructor, initializes to 0.0.0.0.
     */
    Ipv4Address() { addr = 0; }

    /**
     * Ipv4 address as int
     */
    explicit Ipv4Address(uint32_t ip) { addr = ip; }

    /**
     * Ipv4 address bytes: "i0.i1.i2.i3" format
     */
    Ipv4Address(int i0, int i1, int i2, int i3) { set(i0, i1, i2, i3); }

    /**
     * Ipv4 address given as text: "192.66.86.1"
     */
    explicit Ipv4Address(const char *text) { set(text); }

    /**
     * Copy constructor
     */
    Ipv4Address(const Ipv4Address& obj) { addr = obj.addr; }

    ~Ipv4Address() {}
    //@}

    /** name Setting the address */
    //@{
    /**
     * Ipv4 address as uint32_t in host byte order (e.g. "10.0.0.1" is 0x0A000001)
     */
    void set(uint32_t ip) { addr = ip; }

    /**
     * Ipv4 address bytes: "i0.i1.i2.i3" format
     */
    void set(int i0, int i1, int i2, int i3);

    /**
     * Ipv4 address given as text: "192.66.86.1"
     */
    void set(const char *t);
    //@}

    /**
     * Assignment
     */
    Ipv4Address& operator=(const Ipv4Address& obj) { addr = obj.addr; return *this; }

    /**
     * True if all four address bytes are zero. The null value is customarily
     * used to represent a missing, unspecified or invalid address in the
     * simulation models.
     */
    bool isUnspecified() const { return addr == 0; }

    /**
     * Returns true if the two addresses are equal
     */
    bool equals(const Ipv4Address& toCmp) const { return addr == toCmp.addr; }

    /**
     * Returns binary AND of the two addresses
     */
    Ipv4Address doAnd(const Ipv4Address& ip) const { return Ipv4Address(addr & ip.addr); }

    /**
     * Returns the string representation of the address (e.g. "152.66.86.92")
     * @param printUnspec: show 0.0.0.0 as "<unspec>" if true
     */
    std::string str(bool printUnspec = true) const;

    /**
     * Returns the address as an uint32_t in host byte order (e.g. "10.0.0.1" is 0x0A000001).
     */
    uint32_t getInt() const { return addr; }

    /**
     * Returns the corresponding part of the address specified by the index
     * ("[0].[1].[2].[3]")
     */
    int getDByte(int i) const { return (addr >> (3 - i) * 8) & 0xFF; }

    /**
     * Returns the network class of the address: char 'A', 'B', 'C', 'D', 'E',
     * or '?' (returned when the address begins with at least five 1 bits.)
     */
    char getIPClass() const;

    /**
     * Get the Ipv4 address category.
     */
    AddressCategory getAddressCategory() const;

    /**
     * Returns true if this address is the limited broadcast address,
     * i.e. 255.255.255.255.
     */
    bool isLimitedBroadcastAddress() const { return addr == 0xFFFFFFFF; }

    /**
     * Returns true if this address is in the multicast address range,
     * 224.0.0.0 thru 239.255.255.255, that is, it's a class D address.
     */
    bool isMulticast() const { return (addr & 0xF0000000) == 0xE0000000; }

    /**
     * Returns true if this address is unicast address.
     */
    bool isUnicast() const { return !isMulticast() && !isLimitedBroadcastAddress(); }

    /**
     * Returns true if this address is in the range 224.0.0.0 to 224.0.0.255.
     * These addresses are reserved for local purposes meaning, that routers should
     * not forward these datagrams since the applications that use these addresses
     * do not need the datagrams to go further than one hop.
     */
    bool isLinkLocalMulticast() const { return (addr & 0xFFFFFF00) == 0xE0000000; }

    /**
     * Returns an address with the network part of the address (the bits
     * of the hosts part are to 0). For D and E class addresses,
     * it returns a null address.
     */
    Ipv4Address getNetwork() const;

    /**
     * Returns an address with the network mask corresponding to the
     * address class. For D and E class addresses, it returns a null address.
     */
    Ipv4Address getNetworkMask() const;

    /**
     * Indicates if the address is from the same network
     */
    bool isNetwork(const Ipv4Address& toCmp) const;

    /**
     * Compares the first numbits bits of the two addresses.
     */
    bool prefixMatches(const Ipv4Address& to_cmp, int numbits) const;

    /**
     * Indicates how many bits from the to_cmp address, starting counting
     * from the left, matches the address.
     * E.g. if the address is 130.206.72.237, and to_cmp 130.206.72.0,
     * 24 will be returned.
     *
     * Typical usage for comparing Ipv4 prefixes.
     */
    int getNumMatchingPrefixBits(const Ipv4Address& to_cmp) const;

    /**
     * Counts 1 bits in a netmask. E.g. for 255.255.254.0, it will return 23.
     */
    int getNetmaskLength() const;

    /**
     * Get the first prefixLength bits of the address, with the rest set to zero.
     */
    Ipv4Address getPrefix(int prefixLength) const { return doAnd(makeNetmask(prefixLength)); }

    /**
     * Returns true if the address is a valid netmask, i.e. ones are contiguous
     * and shifted fully to the left in the binary representation.
     */
    bool isValidNetmask() const { return addr == _makeNetmask(getNetmaskLength()); }

    /**
     * Test if the masked addresses (ie the mask is applied to addr1 and
     * addr2) are equal.
     */
    static bool maskedAddrAreEqual(const Ipv4Address& addr1,
            const Ipv4Address& addr2,
            const Ipv4Address& netmask);

    /**
     * Returns the broadcast address for the given netmask
     */
    Ipv4Address makeBroadcastAddress(Ipv4Address netmask) const;

    /**
     * Returns equals(addr).
     */
    bool operator==(const Ipv4Address& addr1) const { return equals(addr1); }

    /**
     * Returns !equals(addr).
     */
    bool operator!=(const Ipv4Address& addr1) const { return !equals(addr1); }

    /**
     * Compares two Ipv4 addresses.
     */
    bool operator<(const Ipv4Address& addr1) const { return getInt() < addr1.getInt(); }
    bool operator<=(const Ipv4Address& addr1) const { return getInt() <= addr1.getInt(); }
    bool operator>(const Ipv4Address& addr1) const { return getInt() > addr1.getInt(); }
    bool operator>=(const Ipv4Address& addr1) const { return getInt() >= addr1.getInt(); }

    /**
     * Returns true if the format of the string corresponds to an Ipv4 address
     * with the dotted notation ("192.66.86.1"), and false otherwise.
     *
     * This function can be used to verify an Ipv4 address string before assigning
     * it to an Ipv4Address object (both its ctor and set() function raises an
     * error if the string has invalid format.)
     */
    static bool isWellFormed(const char *text);

    /**
     * Creates and returns a netmask with the given length. For example,
     * for length=23 it will return 255.255.254.0.
     */
    static Ipv4Address makeNetmask(int length) { _checkNetmaskLength(length); return Ipv4Address(_makeNetmask(length)); }
};

inline std::ostream& operator<<(std::ostream& os, const Ipv4Address& ip)
{
    return os << ip.str();
}

inline void doParsimPacking(cCommBuffer *buf, const Ipv4Address& addr)
{
    buf->pack(addr.getInt());
}

inline void doParsimUnpacking(cCommBuffer *buf, Ipv4Address& addr)
{
    int32_t d;
    buf->unpack(d);
    addr.set(d);
}

} // namespace inet

#endif


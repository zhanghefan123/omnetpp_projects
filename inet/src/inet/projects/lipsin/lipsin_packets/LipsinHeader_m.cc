//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/projects/lipsin/lipsin_packets/LipsinHeader.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "LipsinHeader_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

Register_Class(LipsinHeader)

LipsinHeader::LipsinHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(LIPSIN_HEADER_LENGTH);

}

LipsinHeader::LipsinHeader(const LipsinHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

LipsinHeader::~LipsinHeader()
{
    delete [] this->destinationList;
}

LipsinHeader& LipsinHeader::operator=(const LipsinHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void LipsinHeader::copy(const LipsinHeader& other)
{
    this->packetType = other.packetType;
    this->neighborSatelliteId = other.neighborSatelliteId;
    this->uuid = other.uuid;
    this->nonce = other.nonce;
    this->realLidsBf = other.realLidsBf;
    this->virtualLidsBf = other.virtualLidsBf;
    this->pathHeader = other.pathHeader;
    this->source = other.source;
    this->intermediateNode = other.intermediateNode;
    delete [] this->destinationList;
    this->destinationList = (other.destinationList_arraysize==0) ? nullptr : new int[other.destinationList_arraysize];
    destinationList_arraysize = other.destinationList_arraysize;
    for (size_t i = 0; i < destinationList_arraysize; i++) {
        this->destinationList[i] = other.destinationList[i];
    }
    this->packetCreatedTime = other.packetCreatedTime;
    this->propagationDelay = other.propagationDelay;
    this->transmissionDelay = other.transmissionDelay;
}

void LipsinHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->packetType);
    doParsimPacking(b,this->neighborSatelliteId);
    doParsimPacking(b,this->uuid);
    doParsimPacking(b,this->nonce);
    doParsimPacking(b,this->realLidsBf);
    doParsimPacking(b,this->virtualLidsBf);
    doParsimPacking(b,this->pathHeader);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->intermediateNode);
    b->pack(destinationList_arraysize);
    doParsimArrayPacking(b,this->destinationList,destinationList_arraysize);
    doParsimPacking(b,this->packetCreatedTime);
    doParsimPacking(b,this->propagationDelay);
    doParsimPacking(b,this->transmissionDelay);
}

void LipsinHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->packetType);
    doParsimUnpacking(b,this->neighborSatelliteId);
    doParsimUnpacking(b,this->uuid);
    doParsimUnpacking(b,this->nonce);
    doParsimUnpacking(b,this->realLidsBf);
    doParsimUnpacking(b,this->virtualLidsBf);
    doParsimUnpacking(b,this->pathHeader);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->intermediateNode);
    delete [] this->destinationList;
    b->unpack(destinationList_arraysize);
    if (destinationList_arraysize == 0) {
        this->destinationList = nullptr;
    } else {
        this->destinationList = new int[destinationList_arraysize];
        doParsimArrayUnpacking(b,this->destinationList,destinationList_arraysize);
    }
    doParsimUnpacking(b,this->packetCreatedTime);
    doParsimUnpacking(b,this->propagationDelay);
    doParsimUnpacking(b,this->transmissionDelay);
}

int LipsinHeader::getPacketType() const
{
    return this->packetType;
}

void LipsinHeader::setPacketType(int packetType)
{
    handleChange();
    this->packetType = packetType;
}

int LipsinHeader::getNeighborSatelliteId() const
{
    return this->neighborSatelliteId;
}

void LipsinHeader::setNeighborSatelliteId(int neighborSatelliteId)
{
    handleChange();
    this->neighborSatelliteId = neighborSatelliteId;
}

const char * LipsinHeader::getUuid() const
{
    return this->uuid.c_str();
}

void LipsinHeader::setUuid(const char * uuid)
{
    handleChange();
    this->uuid = uuid;
}

uint64_t LipsinHeader::getNonce() const
{
    return this->nonce;
}

void LipsinHeader::setNonce(uint64_t nonce)
{
    handleChange();
    this->nonce = nonce;
}

const BloomFilter * LipsinHeader::getRealLidsBf() const
{
    return this->realLidsBf;
}

void LipsinHeader::setRealLidsBf(BloomFilter * realLidsBf)
{
    handleChange();
    this->realLidsBf = realLidsBf;
}

const BloomFilter * LipsinHeader::getVirtualLidsBf() const
{
    return this->virtualLidsBf;
}

void LipsinHeader::setVirtualLidsBf(BloomFilter * virtualLidsBf)
{
    handleChange();
    this->virtualLidsBf = virtualLidsBf;
}

const PathHeader * LipsinHeader::getPathHeader() const
{
    return this->pathHeader;
}

void LipsinHeader::setPathHeader(PathHeader * pathHeader)
{
    handleChange();
    this->pathHeader = pathHeader;
}

const char * LipsinHeader::getSource() const
{
    return this->source.c_str();
}

void LipsinHeader::setSource(const char * source)
{
    handleChange();
    this->source = source;
}

int LipsinHeader::getIntermediateNode() const
{
    return this->intermediateNode;
}

void LipsinHeader::setIntermediateNode(int intermediateNode)
{
    handleChange();
    this->intermediateNode = intermediateNode;
}

size_t LipsinHeader::getDestinationListArraySize() const
{
    return destinationList_arraysize;
}

int LipsinHeader::getDestinationList(size_t k) const
{
    if (k >= destinationList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinationList_arraysize, (unsigned long)k);
    return this->destinationList[k];
}

void LipsinHeader::setDestinationListArraySize(size_t newSize)
{
    handleChange();
    int *destinationList2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = destinationList_arraysize < newSize ? destinationList_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        destinationList2[i] = this->destinationList[i];
    for (size_t i = minSize; i < newSize; i++)
        destinationList2[i] = 0;
    delete [] this->destinationList;
    this->destinationList = destinationList2;
    destinationList_arraysize = newSize;
}

void LipsinHeader::setDestinationList(size_t k, int destinationList)
{
    if (k >= destinationList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinationList_arraysize, (unsigned long)k);
    handleChange();
    this->destinationList[k] = destinationList;
}

void LipsinHeader::insertDestinationList(size_t k, int destinationList)
{
    if (k > destinationList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinationList_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = destinationList_arraysize + 1;
    int *destinationList2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        destinationList2[i] = this->destinationList[i];
    destinationList2[k] = destinationList;
    for (i = k + 1; i < newSize; i++)
        destinationList2[i] = this->destinationList[i-1];
    delete [] this->destinationList;
    this->destinationList = destinationList2;
    destinationList_arraysize = newSize;
}

void LipsinHeader::appendDestinationList(int destinationList)
{
    insertDestinationList(destinationList_arraysize, destinationList);
}

void LipsinHeader::eraseDestinationList(size_t k)
{
    if (k >= destinationList_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)destinationList_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = destinationList_arraysize - 1;
    int *destinationList2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        destinationList2[i] = this->destinationList[i];
    for (i = k; i < newSize; i++)
        destinationList2[i] = this->destinationList[i+1];
    delete [] this->destinationList;
    this->destinationList = destinationList2;
    destinationList_arraysize = newSize;
}

double LipsinHeader::getPacketCreatedTime() const
{
    return this->packetCreatedTime;
}

void LipsinHeader::setPacketCreatedTime(double packetCreatedTime)
{
    handleChange();
    this->packetCreatedTime = packetCreatedTime;
}

double LipsinHeader::getPropagationDelay() const
{
    return this->propagationDelay;
}

void LipsinHeader::setPropagationDelay(double propagationDelay)
{
    handleChange();
    this->propagationDelay = propagationDelay;
}

double LipsinHeader::getTransmissionDelay() const
{
    return this->transmissionDelay;
}

void LipsinHeader::setTransmissionDelay(double transmissionDelay)
{
    handleChange();
    this->transmissionDelay = transmissionDelay;
}

class LipsinHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_packetType,
        FIELD_neighborSatelliteId,
        FIELD_uuid,
        FIELD_nonce,
        FIELD_realLidsBf,
        FIELD_virtualLidsBf,
        FIELD_pathHeader,
        FIELD_source,
        FIELD_intermediateNode,
        FIELD_destinationList,
        FIELD_packetCreatedTime,
        FIELD_propagationDelay,
        FIELD_transmissionDelay,
    };
  public:
    LipsinHeaderDescriptor();
    virtual ~LipsinHeaderDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LipsinHeaderDescriptor)

LipsinHeaderDescriptor::LipsinHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::LipsinHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

LipsinHeaderDescriptor::~LipsinHeaderDescriptor()
{
    delete[] propertyNames;
}

bool LipsinHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LipsinHeader *>(obj)!=nullptr;
}

const char **LipsinHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LipsinHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LipsinHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 13+base->getFieldCount() : 13;
}

unsigned int LipsinHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_packetType
        FD_ISEDITABLE,    // FIELD_neighborSatelliteId
        FD_ISEDITABLE,    // FIELD_uuid
        FD_ISEDITABLE,    // FIELD_nonce
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISREPLACEABLE,    // FIELD_realLidsBf
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISREPLACEABLE,    // FIELD_virtualLidsBf
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISREPLACEABLE,    // FIELD_pathHeader
        FD_ISEDITABLE,    // FIELD_source
        FD_ISEDITABLE,    // FIELD_intermediateNode
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_destinationList
        FD_ISEDITABLE,    // FIELD_packetCreatedTime
        FD_ISEDITABLE,    // FIELD_propagationDelay
        FD_ISEDITABLE,    // FIELD_transmissionDelay
    };
    return (field >= 0 && field < 13) ? fieldTypeFlags[field] : 0;
}

const char *LipsinHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "packetType",
        "neighborSatelliteId",
        "uuid",
        "nonce",
        "realLidsBf",
        "virtualLidsBf",
        "pathHeader",
        "source",
        "intermediateNode",
        "destinationList",
        "packetCreatedTime",
        "propagationDelay",
        "transmissionDelay",
    };
    return (field >= 0 && field < 13) ? fieldNames[field] : nullptr;
}

int LipsinHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "packetType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "neighborSatelliteId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "uuid") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "nonce") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "realLidsBf") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "virtualLidsBf") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "pathHeader") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "source") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "intermediateNode") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "destinationList") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "packetCreatedTime") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "propagationDelay") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "transmissionDelay") == 0) return baseIndex + 12;
    return base ? base->findField(fieldName) : -1;
}

const char *LipsinHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_packetType
        "int",    // FIELD_neighborSatelliteId
        "string",    // FIELD_uuid
        "uint64_t",    // FIELD_nonce
        "inet::BloomFilter",    // FIELD_realLidsBf
        "inet::BloomFilter",    // FIELD_virtualLidsBf
        "inet::PathHeader",    // FIELD_pathHeader
        "string",    // FIELD_source
        "int",    // FIELD_intermediateNode
        "int",    // FIELD_destinationList
        "double",    // FIELD_packetCreatedTime
        "double",    // FIELD_propagationDelay
        "double",    // FIELD_transmissionDelay
    };
    return (field >= 0 && field < 13) ? fieldTypeStrings[field] : nullptr;
}

const char **LipsinHeaderDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LipsinHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LipsinHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_destinationList: return pp->getDestinationListArraySize();
        default: return 0;
    }
}

void LipsinHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_destinationList: pp->setDestinationListArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LipsinHeader'", field);
    }
}

const char *LipsinHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_realLidsBf: { const BloomFilter * value = pp->getRealLidsBf(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_virtualLidsBf: { const BloomFilter * value = pp->getVirtualLidsBf(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_pathHeader: { const PathHeader * value = pp->getPathHeader(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string LipsinHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: return long2string(pp->getPacketType());
        case FIELD_neighborSatelliteId: return long2string(pp->getNeighborSatelliteId());
        case FIELD_uuid: return oppstring2string(pp->getUuid());
        case FIELD_nonce: return uint642string(pp->getNonce());
        case FIELD_realLidsBf: return "";
        case FIELD_virtualLidsBf: return "";
        case FIELD_pathHeader: return "";
        case FIELD_source: return oppstring2string(pp->getSource());
        case FIELD_intermediateNode: return long2string(pp->getIntermediateNode());
        case FIELD_destinationList: return long2string(pp->getDestinationList(i));
        case FIELD_packetCreatedTime: return double2string(pp->getPacketCreatedTime());
        case FIELD_propagationDelay: return double2string(pp->getPropagationDelay());
        case FIELD_transmissionDelay: return double2string(pp->getTransmissionDelay());
        default: return "";
    }
}

void LipsinHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: pp->setPacketType(string2long(value)); break;
        case FIELD_neighborSatelliteId: pp->setNeighborSatelliteId(string2long(value)); break;
        case FIELD_uuid: pp->setUuid((value)); break;
        case FIELD_nonce: pp->setNonce(string2uint64(value)); break;
        case FIELD_source: pp->setSource((value)); break;
        case FIELD_intermediateNode: pp->setIntermediateNode(string2long(value)); break;
        case FIELD_destinationList: pp->setDestinationList(i,string2long(value)); break;
        case FIELD_packetCreatedTime: pp->setPacketCreatedTime(string2double(value)); break;
        case FIELD_propagationDelay: pp->setPropagationDelay(string2double(value)); break;
        case FIELD_transmissionDelay: pp->setTransmissionDelay(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LipsinHeader'", field);
    }
}

omnetpp::cValue LipsinHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: return pp->getPacketType();
        case FIELD_neighborSatelliteId: return pp->getNeighborSatelliteId();
        case FIELD_uuid: return pp->getUuid();
        case FIELD_nonce: return (omnetpp::intval_t)(pp->getNonce());
        case FIELD_realLidsBf: return omnetpp::toAnyPtr(pp->getRealLidsBf()); break;
        case FIELD_virtualLidsBf: return omnetpp::toAnyPtr(pp->getVirtualLidsBf()); break;
        case FIELD_pathHeader: return omnetpp::toAnyPtr(pp->getPathHeader()); break;
        case FIELD_source: return pp->getSource();
        case FIELD_intermediateNode: return pp->getIntermediateNode();
        case FIELD_destinationList: return pp->getDestinationList(i);
        case FIELD_packetCreatedTime: return pp->getPacketCreatedTime();
        case FIELD_propagationDelay: return pp->getPropagationDelay();
        case FIELD_transmissionDelay: return pp->getTransmissionDelay();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LipsinHeader' as cValue -- field index out of range?", field);
    }
}

void LipsinHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_packetType: pp->setPacketType(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_neighborSatelliteId: pp->setNeighborSatelliteId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_uuid: pp->setUuid(value.stringValue()); break;
        case FIELD_nonce: pp->setNonce(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_realLidsBf: pp->setRealLidsBf(omnetpp::fromAnyPtr<BloomFilter>(value.pointerValue())); break;
        case FIELD_virtualLidsBf: pp->setVirtualLidsBf(omnetpp::fromAnyPtr<BloomFilter>(value.pointerValue())); break;
        case FIELD_pathHeader: pp->setPathHeader(omnetpp::fromAnyPtr<PathHeader>(value.pointerValue())); break;
        case FIELD_source: pp->setSource(value.stringValue()); break;
        case FIELD_intermediateNode: pp->setIntermediateNode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destinationList: pp->setDestinationList(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_packetCreatedTime: pp->setPacketCreatedTime(value.doubleValue()); break;
        case FIELD_propagationDelay: pp->setPropagationDelay(value.doubleValue()); break;
        case FIELD_transmissionDelay: pp->setTransmissionDelay(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LipsinHeader'", field);
    }
}

const char *LipsinHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_realLidsBf: return omnetpp::opp_typename(typeid(BloomFilter));
        case FIELD_virtualLidsBf: return omnetpp::opp_typename(typeid(BloomFilter));
        case FIELD_pathHeader: return omnetpp::opp_typename(typeid(PathHeader));
        default: return nullptr;
    };
}

omnetpp::any_ptr LipsinHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_realLidsBf: return omnetpp::toAnyPtr(pp->getRealLidsBf()); break;
        case FIELD_virtualLidsBf: return omnetpp::toAnyPtr(pp->getVirtualLidsBf()); break;
        case FIELD_pathHeader: return omnetpp::toAnyPtr(pp->getPathHeader()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LipsinHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LipsinHeader *pp = omnetpp::fromAnyPtr<LipsinHeader>(object); (void)pp;
    switch (field) {
        case FIELD_realLidsBf: pp->setRealLidsBf(omnetpp::fromAnyPtr<BloomFilter>(ptr)); break;
        case FIELD_virtualLidsBf: pp->setVirtualLidsBf(omnetpp::fromAnyPtr<BloomFilter>(ptr)); break;
        case FIELD_pathHeader: pp->setPathHeader(omnetpp::fromAnyPtr<PathHeader>(ptr)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LipsinHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp


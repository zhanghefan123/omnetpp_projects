//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/projects/sr/sr_packet/SRHeader.msg.
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
#include "SRHeader_m.h"

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

Register_Class(SRHeader)

SRHeader::SRHeader() : ::inet::FieldsChunk()
{
    this->setChunkLength(SR_HEADER_LENGTH);

}

SRHeader::SRHeader(const SRHeader& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

SRHeader::~SRHeader()
{
    delete [] this->sids;
}

SRHeader& SRHeader::operator=(const SRHeader& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void SRHeader::copy(const SRHeader& other)
{
    this->source_node_id = other.source_node_id;
    this->destination_node_id = other.destination_node_id;
    this->sid_index = other.sid_index;
    delete [] this->sids;
    this->sids = (other.sids_arraysize==0) ? nullptr : new int[other.sids_arraysize];
    sids_arraysize = other.sids_arraysize;
    for (size_t i = 0; i < sids_arraysize; i++) {
        this->sids[i] = other.sids[i];
    }
    this->packet_created_time = other.packet_created_time;
}

void SRHeader::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->source_node_id);
    doParsimPacking(b,this->destination_node_id);
    doParsimPacking(b,this->sid_index);
    b->pack(sids_arraysize);
    doParsimArrayPacking(b,this->sids,sids_arraysize);
    doParsimPacking(b,this->packet_created_time);
}

void SRHeader::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->source_node_id);
    doParsimUnpacking(b,this->destination_node_id);
    doParsimUnpacking(b,this->sid_index);
    delete [] this->sids;
    b->unpack(sids_arraysize);
    if (sids_arraysize == 0) {
        this->sids = nullptr;
    } else {
        this->sids = new int[sids_arraysize];
        doParsimArrayUnpacking(b,this->sids,sids_arraysize);
    }
    doParsimUnpacking(b,this->packet_created_time);
}

int SRHeader::getSource_node_id() const
{
    return this->source_node_id;
}

void SRHeader::setSource_node_id(int source_node_id)
{
    handleChange();
    this->source_node_id = source_node_id;
}

int SRHeader::getDestination_node_id() const
{
    return this->destination_node_id;
}

void SRHeader::setDestination_node_id(int destination_node_id)
{
    handleChange();
    this->destination_node_id = destination_node_id;
}

int SRHeader::getSid_index() const
{
    return this->sid_index;
}

void SRHeader::setSid_index(int sid_index)
{
    handleChange();
    this->sid_index = sid_index;
}

size_t SRHeader::getSidsArraySize() const
{
    return sids_arraysize;
}

int SRHeader::getSids(size_t k) const
{
    if (k >= sids_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sids_arraysize, (unsigned long)k);
    return this->sids[k];
}

void SRHeader::setSidsArraySize(size_t newSize)
{
    handleChange();
    int *sids2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = sids_arraysize < newSize ? sids_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        sids2[i] = this->sids[i];
    for (size_t i = minSize; i < newSize; i++)
        sids2[i] = 0;
    delete [] this->sids;
    this->sids = sids2;
    sids_arraysize = newSize;
}

void SRHeader::setSids(size_t k, int sids)
{
    if (k >= sids_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sids_arraysize, (unsigned long)k);
    handleChange();
    this->sids[k] = sids;
}

void SRHeader::insertSids(size_t k, int sids)
{
    if (k > sids_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sids_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = sids_arraysize + 1;
    int *sids2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sids2[i] = this->sids[i];
    sids2[k] = sids;
    for (i = k + 1; i < newSize; i++)
        sids2[i] = this->sids[i-1];
    delete [] this->sids;
    this->sids = sids2;
    sids_arraysize = newSize;
}

void SRHeader::appendSids(int sids)
{
    insertSids(sids_arraysize, sids);
}

void SRHeader::eraseSids(size_t k)
{
    if (k >= sids_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)sids_arraysize, (unsigned long)k);
    handleChange();
    size_t newSize = sids_arraysize - 1;
    int *sids2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        sids2[i] = this->sids[i];
    for (i = k; i < newSize; i++)
        sids2[i] = this->sids[i+1];
    delete [] this->sids;
    this->sids = sids2;
    sids_arraysize = newSize;
}

double SRHeader::getPacket_created_time() const
{
    return this->packet_created_time;
}

void SRHeader::setPacket_created_time(double packet_created_time)
{
    handleChange();
    this->packet_created_time = packet_created_time;
}

class SRHeaderDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_source_node_id,
        FIELD_destination_node_id,
        FIELD_sid_index,
        FIELD_sids,
        FIELD_packet_created_time,
    };
  public:
    SRHeaderDescriptor();
    virtual ~SRHeaderDescriptor();

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

Register_ClassDescriptor(SRHeaderDescriptor)

SRHeaderDescriptor::SRHeaderDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::SRHeader)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

SRHeaderDescriptor::~SRHeaderDescriptor()
{
    delete[] propertyNames;
}

bool SRHeaderDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SRHeader *>(obj)!=nullptr;
}

const char **SRHeaderDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SRHeaderDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SRHeaderDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int SRHeaderDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_source_node_id
        FD_ISEDITABLE,    // FIELD_destination_node_id
        FD_ISEDITABLE,    // FIELD_sid_index
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_sids
        FD_ISEDITABLE,    // FIELD_packet_created_time
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *SRHeaderDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "source_node_id",
        "destination_node_id",
        "sid_index",
        "sids",
        "packet_created_time",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int SRHeaderDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "source_node_id") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "destination_node_id") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sid_index") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sids") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "packet_created_time") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *SRHeaderDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_source_node_id
        "int",    // FIELD_destination_node_id
        "int",    // FIELD_sid_index
        "int",    // FIELD_sids
        "double",    // FIELD_packet_created_time
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **SRHeaderDescriptor::getFieldPropertyNames(int field) const
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

const char *SRHeaderDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int SRHeaderDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sids: return pp->getSidsArraySize();
        default: return 0;
    }
}

void SRHeaderDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        case FIELD_sids: pp->setSidsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SRHeader'", field);
    }
}

const char *SRHeaderDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SRHeaderDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        case FIELD_source_node_id: return long2string(pp->getSource_node_id());
        case FIELD_destination_node_id: return long2string(pp->getDestination_node_id());
        case FIELD_sid_index: return long2string(pp->getSid_index());
        case FIELD_sids: return long2string(pp->getSids(i));
        case FIELD_packet_created_time: return double2string(pp->getPacket_created_time());
        default: return "";
    }
}

void SRHeaderDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        case FIELD_source_node_id: pp->setSource_node_id(string2long(value)); break;
        case FIELD_destination_node_id: pp->setDestination_node_id(string2long(value)); break;
        case FIELD_sid_index: pp->setSid_index(string2long(value)); break;
        case FIELD_sids: pp->setSids(i,string2long(value)); break;
        case FIELD_packet_created_time: pp->setPacket_created_time(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SRHeader'", field);
    }
}

omnetpp::cValue SRHeaderDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        case FIELD_source_node_id: return pp->getSource_node_id();
        case FIELD_destination_node_id: return pp->getDestination_node_id();
        case FIELD_sid_index: return pp->getSid_index();
        case FIELD_sids: return pp->getSids(i);
        case FIELD_packet_created_time: return pp->getPacket_created_time();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SRHeader' as cValue -- field index out of range?", field);
    }
}

void SRHeaderDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        case FIELD_source_node_id: pp->setSource_node_id(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_destination_node_id: pp->setDestination_node_id(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sid_index: pp->setSid_index(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sids: pp->setSids(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_packet_created_time: pp->setPacket_created_time(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SRHeader'", field);
    }
}

const char *SRHeaderDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SRHeaderDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SRHeaderDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SRHeader *pp = omnetpp::fromAnyPtr<SRHeader>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SRHeader'", field);
    }
}

}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp


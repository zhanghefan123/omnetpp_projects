//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp/TcpConnection.msg.
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
#include "TcpConnection_m.h"

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
namespace tcp {

class TcpSackRexmitQueueDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TcpSackRexmitQueueDescriptor();
    virtual ~TcpSackRexmitQueueDescriptor();

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

Register_ClassDescriptor(TcpSackRexmitQueueDescriptor)

TcpSackRexmitQueueDescriptor::TcpSackRexmitQueueDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpSackRexmitQueue)), "")
{
    propertyNames = nullptr;
}

TcpSackRexmitQueueDescriptor::~TcpSackRexmitQueueDescriptor()
{
    delete[] propertyNames;
}

bool TcpSackRexmitQueueDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpSackRexmitQueue *>(obj)!=nullptr;
}

const char **TcpSackRexmitQueueDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpSackRexmitQueueDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpSackRexmitQueueDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TcpSackRexmitQueueDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TcpSackRexmitQueueDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TcpSackRexmitQueueDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TcpSackRexmitQueueDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TcpSackRexmitQueueDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpSackRexmitQueueDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpSackRexmitQueueDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpSackRexmitQueueDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpSackRexmitQueue'", field);
    }
}

const char *TcpSackRexmitQueueDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpSackRexmitQueueDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TcpSackRexmitQueueDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSackRexmitQueue'", field);
    }
}

omnetpp::cValue TcpSackRexmitQueueDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpSackRexmitQueue' as cValue -- field index out of range?", field);
    }
}

void TcpSackRexmitQueueDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSackRexmitQueue'", field);
    }
}

const char *TcpSackRexmitQueueDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TcpSackRexmitQueueDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpSackRexmitQueueDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSackRexmitQueue *pp = omnetpp::fromAnyPtr<TcpSackRexmitQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSackRexmitQueue'", field);
    }
}

class TcpAlgorithmDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    TcpAlgorithmDescriptor();
    virtual ~TcpAlgorithmDescriptor();

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

Register_ClassDescriptor(TcpAlgorithmDescriptor)

TcpAlgorithmDescriptor::TcpAlgorithmDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpAlgorithm)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TcpAlgorithmDescriptor::~TcpAlgorithmDescriptor()
{
    delete[] propertyNames;
}

bool TcpAlgorithmDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpAlgorithm *>(obj)!=nullptr;
}

const char **TcpAlgorithmDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpAlgorithmDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpAlgorithmDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int TcpAlgorithmDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *TcpAlgorithmDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int TcpAlgorithmDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *TcpAlgorithmDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **TcpAlgorithmDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpAlgorithmDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpAlgorithmDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpAlgorithmDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpAlgorithm'", field);
    }
}

const char *TcpAlgorithmDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpAlgorithmDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void TcpAlgorithmDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAlgorithm'", field);
    }
}

omnetpp::cValue TcpAlgorithmDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpAlgorithm' as cValue -- field index out of range?", field);
    }
}

void TcpAlgorithmDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAlgorithm'", field);
    }
}

const char *TcpAlgorithmDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr TcpAlgorithmDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpAlgorithmDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpAlgorithm *pp = omnetpp::fromAnyPtr<TcpAlgorithm>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpAlgorithm'", field);
    }
}

class TcpStateVariablesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_active,
        FIELD_fork,
        FIELD_snd_mss,
        FIELD_snd_una,
        FIELD_snd_nxt,
        FIELD_snd_max,
        FIELD_snd_wnd,
        FIELD_snd_up,
        FIELD_snd_wl1,
        FIELD_snd_wl2,
        FIELD_iss,
        FIELD_rcv_nxt,
        FIELD_rcv_wnd,
        FIELD_rcv_up,
        FIELD_irs,
        FIELD_rcv_adv,
        FIELD_syn_rexmit_count,
        FIELD_syn_rexmit_timeout,
        FIELD_fin_ack_rcvd,
        FIELD_send_fin,
        FIELD_snd_fin_seq,
        FIELD_fin_rcvd,
        FIELD_rcv_fin_seq,
        FIELD_nagle_enabled,
        FIELD_delayed_acks_enabled,
        FIELD_limited_transmit_enabled,
        FIELD_increased_IW_enabled,
        FIELD_full_sized_segment_counter,
        FIELD_ack_now,
        FIELD_afterRto,
        FIELD_ws_support,
        FIELD_ws_enabled,
        FIELD_ws_manual_scale,
        FIELD_snd_ws,
        FIELD_rcv_ws,
        FIELD_rcv_wnd_scale,
        FIELD_snd_wnd_scale,
        FIELD_ts_support,
        FIELD_ts_enabled,
        FIELD_snd_initial_ts,
        FIELD_rcv_initial_ts,
        FIELD_ts_recent,
        FIELD_last_ack_sent,
        FIELD_time_last_data_sent,
        FIELD_sack_support,
        FIELD_sack_enabled,
        FIELD_snd_sack_perm,
        FIELD_rcv_sack_perm,
        FIELD_start_seqno,
        FIELD_end_seqno,
        FIELD_snd_sack,
        FIELD_snd_dsack,
        FIELD_highRxt,
        FIELD_pipe,
        FIELD_recoveryPoint,
        FIELD_sackedBytes,
        FIELD_sackedBytes_old,
        FIELD_lossRecovery,
        FIELD_sendQueueLimit,
        FIELD_queueUpdate,
        FIELD_dupacks,
        FIELD_snd_sacks,
        FIELD_rcv_sacks,
        FIELD_rcv_oooseg,
        FIELD_rcv_naseg,
        FIELD_maxRcvBuffer,
        FIELD_usedRcvBuffer,
        FIELD_freeRcvBuffer,
        FIELD_tcpRcvQueueDrops,
    };
  public:
    TcpStateVariablesDescriptor();
    virtual ~TcpStateVariablesDescriptor();

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

Register_ClassDescriptor(TcpStateVariablesDescriptor)

TcpStateVariablesDescriptor::TcpStateVariablesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpStateVariables)), "")
{
    propertyNames = nullptr;
}

TcpStateVariablesDescriptor::~TcpStateVariablesDescriptor()
{
    delete[] propertyNames;
}

bool TcpStateVariablesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpStateVariables *>(obj)!=nullptr;
}

const char **TcpStateVariablesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpStateVariablesDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpStateVariablesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 69+base->getFieldCount() : 69;
}

unsigned int TcpStateVariablesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_active
        0,    // FIELD_fork
        0,    // FIELD_snd_mss
        0,    // FIELD_snd_una
        0,    // FIELD_snd_nxt
        0,    // FIELD_snd_max
        0,    // FIELD_snd_wnd
        0,    // FIELD_snd_up
        0,    // FIELD_snd_wl1
        0,    // FIELD_snd_wl2
        0,    // FIELD_iss
        0,    // FIELD_rcv_nxt
        0,    // FIELD_rcv_wnd
        0,    // FIELD_rcv_up
        0,    // FIELD_irs
        0,    // FIELD_rcv_adv
        0,    // FIELD_syn_rexmit_count
        0,    // FIELD_syn_rexmit_timeout
        0,    // FIELD_fin_ack_rcvd
        0,    // FIELD_send_fin
        0,    // FIELD_snd_fin_seq
        0,    // FIELD_fin_rcvd
        0,    // FIELD_rcv_fin_seq
        0,    // FIELD_nagle_enabled
        0,    // FIELD_delayed_acks_enabled
        0,    // FIELD_limited_transmit_enabled
        0,    // FIELD_increased_IW_enabled
        0,    // FIELD_full_sized_segment_counter
        0,    // FIELD_ack_now
        0,    // FIELD_afterRto
        0,    // FIELD_ws_support
        0,    // FIELD_ws_enabled
        0,    // FIELD_ws_manual_scale
        0,    // FIELD_snd_ws
        0,    // FIELD_rcv_ws
        0,    // FIELD_rcv_wnd_scale
        0,    // FIELD_snd_wnd_scale
        0,    // FIELD_ts_support
        0,    // FIELD_ts_enabled
        0,    // FIELD_snd_initial_ts
        0,    // FIELD_rcv_initial_ts
        0,    // FIELD_ts_recent
        0,    // FIELD_last_ack_sent
        0,    // FIELD_time_last_data_sent
        0,    // FIELD_sack_support
        0,    // FIELD_sack_enabled
        0,    // FIELD_snd_sack_perm
        0,    // FIELD_rcv_sack_perm
        0,    // FIELD_start_seqno
        0,    // FIELD_end_seqno
        0,    // FIELD_snd_sack
        0,    // FIELD_snd_dsack
        0,    // FIELD_highRxt
        0,    // FIELD_pipe
        0,    // FIELD_recoveryPoint
        0,    // FIELD_sackedBytes
        0,    // FIELD_sackedBytes_old
        0,    // FIELD_lossRecovery
        0,    // FIELD_sendQueueLimit
        0,    // FIELD_queueUpdate
        0,    // FIELD_dupacks
        0,    // FIELD_snd_sacks
        0,    // FIELD_rcv_sacks
        0,    // FIELD_rcv_oooseg
        0,    // FIELD_rcv_naseg
        0,    // FIELD_maxRcvBuffer
        0,    // FIELD_usedRcvBuffer
        0,    // FIELD_freeRcvBuffer
        0,    // FIELD_tcpRcvQueueDrops
    };
    return (field >= 0 && field < 69) ? fieldTypeFlags[field] : 0;
}

const char *TcpStateVariablesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "active",
        "fork",
        "snd_mss",
        "snd_una",
        "snd_nxt",
        "snd_max",
        "snd_wnd",
        "snd_up",
        "snd_wl1",
        "snd_wl2",
        "iss",
        "rcv_nxt",
        "rcv_wnd",
        "rcv_up",
        "irs",
        "rcv_adv",
        "syn_rexmit_count",
        "syn_rexmit_timeout",
        "fin_ack_rcvd",
        "send_fin",
        "snd_fin_seq",
        "fin_rcvd",
        "rcv_fin_seq",
        "nagle_enabled",
        "delayed_acks_enabled",
        "limited_transmit_enabled",
        "increased_IW_enabled",
        "full_sized_segment_counter",
        "ack_now",
        "afterRto",
        "ws_support",
        "ws_enabled",
        "ws_manual_scale",
        "snd_ws",
        "rcv_ws",
        "rcv_wnd_scale",
        "snd_wnd_scale",
        "ts_support",
        "ts_enabled",
        "snd_initial_ts",
        "rcv_initial_ts",
        "ts_recent",
        "last_ack_sent",
        "time_last_data_sent",
        "sack_support",
        "sack_enabled",
        "snd_sack_perm",
        "rcv_sack_perm",
        "start_seqno",
        "end_seqno",
        "snd_sack",
        "snd_dsack",
        "highRxt",
        "pipe",
        "recoveryPoint",
        "sackedBytes",
        "sackedBytes_old",
        "lossRecovery",
        "sendQueueLimit",
        "queueUpdate",
        "dupacks",
        "snd_sacks",
        "rcv_sacks",
        "rcv_oooseg",
        "rcv_naseg",
        "maxRcvBuffer",
        "usedRcvBuffer",
        "freeRcvBuffer",
        "tcpRcvQueueDrops",
    };
    return (field >= 0 && field < 69) ? fieldNames[field] : nullptr;
}

int TcpStateVariablesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "active") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "fork") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "snd_mss") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "snd_una") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "snd_nxt") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "snd_max") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "snd_wnd") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "snd_up") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "snd_wl1") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "snd_wl2") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "iss") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "rcv_nxt") == 0) return baseIndex + 11;
    if (strcmp(fieldName, "rcv_wnd") == 0) return baseIndex + 12;
    if (strcmp(fieldName, "rcv_up") == 0) return baseIndex + 13;
    if (strcmp(fieldName, "irs") == 0) return baseIndex + 14;
    if (strcmp(fieldName, "rcv_adv") == 0) return baseIndex + 15;
    if (strcmp(fieldName, "syn_rexmit_count") == 0) return baseIndex + 16;
    if (strcmp(fieldName, "syn_rexmit_timeout") == 0) return baseIndex + 17;
    if (strcmp(fieldName, "fin_ack_rcvd") == 0) return baseIndex + 18;
    if (strcmp(fieldName, "send_fin") == 0) return baseIndex + 19;
    if (strcmp(fieldName, "snd_fin_seq") == 0) return baseIndex + 20;
    if (strcmp(fieldName, "fin_rcvd") == 0) return baseIndex + 21;
    if (strcmp(fieldName, "rcv_fin_seq") == 0) return baseIndex + 22;
    if (strcmp(fieldName, "nagle_enabled") == 0) return baseIndex + 23;
    if (strcmp(fieldName, "delayed_acks_enabled") == 0) return baseIndex + 24;
    if (strcmp(fieldName, "limited_transmit_enabled") == 0) return baseIndex + 25;
    if (strcmp(fieldName, "increased_IW_enabled") == 0) return baseIndex + 26;
    if (strcmp(fieldName, "full_sized_segment_counter") == 0) return baseIndex + 27;
    if (strcmp(fieldName, "ack_now") == 0) return baseIndex + 28;
    if (strcmp(fieldName, "afterRto") == 0) return baseIndex + 29;
    if (strcmp(fieldName, "ws_support") == 0) return baseIndex + 30;
    if (strcmp(fieldName, "ws_enabled") == 0) return baseIndex + 31;
    if (strcmp(fieldName, "ws_manual_scale") == 0) return baseIndex + 32;
    if (strcmp(fieldName, "snd_ws") == 0) return baseIndex + 33;
    if (strcmp(fieldName, "rcv_ws") == 0) return baseIndex + 34;
    if (strcmp(fieldName, "rcv_wnd_scale") == 0) return baseIndex + 35;
    if (strcmp(fieldName, "snd_wnd_scale") == 0) return baseIndex + 36;
    if (strcmp(fieldName, "ts_support") == 0) return baseIndex + 37;
    if (strcmp(fieldName, "ts_enabled") == 0) return baseIndex + 38;
    if (strcmp(fieldName, "snd_initial_ts") == 0) return baseIndex + 39;
    if (strcmp(fieldName, "rcv_initial_ts") == 0) return baseIndex + 40;
    if (strcmp(fieldName, "ts_recent") == 0) return baseIndex + 41;
    if (strcmp(fieldName, "last_ack_sent") == 0) return baseIndex + 42;
    if (strcmp(fieldName, "time_last_data_sent") == 0) return baseIndex + 43;
    if (strcmp(fieldName, "sack_support") == 0) return baseIndex + 44;
    if (strcmp(fieldName, "sack_enabled") == 0) return baseIndex + 45;
    if (strcmp(fieldName, "snd_sack_perm") == 0) return baseIndex + 46;
    if (strcmp(fieldName, "rcv_sack_perm") == 0) return baseIndex + 47;
    if (strcmp(fieldName, "start_seqno") == 0) return baseIndex + 48;
    if (strcmp(fieldName, "end_seqno") == 0) return baseIndex + 49;
    if (strcmp(fieldName, "snd_sack") == 0) return baseIndex + 50;
    if (strcmp(fieldName, "snd_dsack") == 0) return baseIndex + 51;
    if (strcmp(fieldName, "highRxt") == 0) return baseIndex + 52;
    if (strcmp(fieldName, "pipe") == 0) return baseIndex + 53;
    if (strcmp(fieldName, "recoveryPoint") == 0) return baseIndex + 54;
    if (strcmp(fieldName, "sackedBytes") == 0) return baseIndex + 55;
    if (strcmp(fieldName, "sackedBytes_old") == 0) return baseIndex + 56;
    if (strcmp(fieldName, "lossRecovery") == 0) return baseIndex + 57;
    if (strcmp(fieldName, "sendQueueLimit") == 0) return baseIndex + 58;
    if (strcmp(fieldName, "queueUpdate") == 0) return baseIndex + 59;
    if (strcmp(fieldName, "dupacks") == 0) return baseIndex + 60;
    if (strcmp(fieldName, "snd_sacks") == 0) return baseIndex + 61;
    if (strcmp(fieldName, "rcv_sacks") == 0) return baseIndex + 62;
    if (strcmp(fieldName, "rcv_oooseg") == 0) return baseIndex + 63;
    if (strcmp(fieldName, "rcv_naseg") == 0) return baseIndex + 64;
    if (strcmp(fieldName, "maxRcvBuffer") == 0) return baseIndex + 65;
    if (strcmp(fieldName, "usedRcvBuffer") == 0) return baseIndex + 66;
    if (strcmp(fieldName, "freeRcvBuffer") == 0) return baseIndex + 67;
    if (strcmp(fieldName, "tcpRcvQueueDrops") == 0) return baseIndex + 68;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpStateVariablesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_active
        "bool",    // FIELD_fork
        "uint32_t",    // FIELD_snd_mss
        "uint32_t",    // FIELD_snd_una
        "uint32_t",    // FIELD_snd_nxt
        "uint32_t",    // FIELD_snd_max
        "uint32_t",    // FIELD_snd_wnd
        "uint32_t",    // FIELD_snd_up
        "uint32_t",    // FIELD_snd_wl1
        "uint32_t",    // FIELD_snd_wl2
        "uint32_t",    // FIELD_iss
        "uint32_t",    // FIELD_rcv_nxt
        "uint32_t",    // FIELD_rcv_wnd
        "uint32_t",    // FIELD_rcv_up
        "uint32_t",    // FIELD_irs
        "uint32_t",    // FIELD_rcv_adv
        "int",    // FIELD_syn_rexmit_count
        "omnetpp::simtime_t",    // FIELD_syn_rexmit_timeout
        "bool",    // FIELD_fin_ack_rcvd
        "bool",    // FIELD_send_fin
        "uint32_t",    // FIELD_snd_fin_seq
        "bool",    // FIELD_fin_rcvd
        "uint32_t",    // FIELD_rcv_fin_seq
        "bool",    // FIELD_nagle_enabled
        "bool",    // FIELD_delayed_acks_enabled
        "bool",    // FIELD_limited_transmit_enabled
        "bool",    // FIELD_increased_IW_enabled
        "uint32_t",    // FIELD_full_sized_segment_counter
        "bool",    // FIELD_ack_now
        "bool",    // FIELD_afterRto
        "bool",    // FIELD_ws_support
        "bool",    // FIELD_ws_enabled
        "int",    // FIELD_ws_manual_scale
        "bool",    // FIELD_snd_ws
        "bool",    // FIELD_rcv_ws
        "unsigned int",    // FIELD_rcv_wnd_scale
        "unsigned int",    // FIELD_snd_wnd_scale
        "bool",    // FIELD_ts_support
        "bool",    // FIELD_ts_enabled
        "bool",    // FIELD_snd_initial_ts
        "bool",    // FIELD_rcv_initial_ts
        "uint32_t",    // FIELD_ts_recent
        "uint32_t",    // FIELD_last_ack_sent
        "omnetpp::simtime_t",    // FIELD_time_last_data_sent
        "bool",    // FIELD_sack_support
        "bool",    // FIELD_sack_enabled
        "bool",    // FIELD_snd_sack_perm
        "bool",    // FIELD_rcv_sack_perm
        "uint32_t",    // FIELD_start_seqno
        "uint32_t",    // FIELD_end_seqno
        "bool",    // FIELD_snd_sack
        "bool",    // FIELD_snd_dsack
        "uint32_t",    // FIELD_highRxt
        "uint32_t",    // FIELD_pipe
        "uint32_t",    // FIELD_recoveryPoint
        "uint32_t",    // FIELD_sackedBytes
        "uint32_t",    // FIELD_sackedBytes_old
        "bool",    // FIELD_lossRecovery
        "uint32_t",    // FIELD_sendQueueLimit
        "bool",    // FIELD_queueUpdate
        "uint32_t",    // FIELD_dupacks
        "uint32_t",    // FIELD_snd_sacks
        "uint32_t",    // FIELD_rcv_sacks
        "uint32_t",    // FIELD_rcv_oooseg
        "uint32_t",    // FIELD_rcv_naseg
        "uint32_t",    // FIELD_maxRcvBuffer
        "uint32_t",    // FIELD_usedRcvBuffer
        "uint32_t",    // FIELD_freeRcvBuffer
        "uint32_t",    // FIELD_tcpRcvQueueDrops
    };
    return (field >= 0 && field < 69) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpStateVariablesDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpStateVariablesDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpStateVariablesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpStateVariablesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpStateVariables'", field);
    }
}

const char *TcpStateVariablesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpStateVariablesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_active: return bool2string(pp->active);
        case FIELD_fork: return bool2string(pp->fork);
        case FIELD_snd_mss: return ulong2string(pp->snd_mss);
        case FIELD_snd_una: return ulong2string(pp->snd_una);
        case FIELD_snd_nxt: return ulong2string(pp->snd_nxt);
        case FIELD_snd_max: return ulong2string(pp->snd_max);
        case FIELD_snd_wnd: return ulong2string(pp->snd_wnd);
        case FIELD_snd_up: return ulong2string(pp->snd_up);
        case FIELD_snd_wl1: return ulong2string(pp->snd_wl1);
        case FIELD_snd_wl2: return ulong2string(pp->snd_wl2);
        case FIELD_iss: return ulong2string(pp->iss);
        case FIELD_rcv_nxt: return ulong2string(pp->rcv_nxt);
        case FIELD_rcv_wnd: return ulong2string(pp->rcv_wnd);
        case FIELD_rcv_up: return ulong2string(pp->rcv_up);
        case FIELD_irs: return ulong2string(pp->irs);
        case FIELD_rcv_adv: return ulong2string(pp->rcv_adv);
        case FIELD_syn_rexmit_count: return long2string(pp->syn_rexmit_count);
        case FIELD_syn_rexmit_timeout: return simtime2string(pp->syn_rexmit_timeout);
        case FIELD_fin_ack_rcvd: return bool2string(pp->fin_ack_rcvd);
        case FIELD_send_fin: return bool2string(pp->send_fin);
        case FIELD_snd_fin_seq: return ulong2string(pp->snd_fin_seq);
        case FIELD_fin_rcvd: return bool2string(pp->fin_rcvd);
        case FIELD_rcv_fin_seq: return ulong2string(pp->rcv_fin_seq);
        case FIELD_nagle_enabled: return bool2string(pp->nagle_enabled);
        case FIELD_delayed_acks_enabled: return bool2string(pp->delayed_acks_enabled);
        case FIELD_limited_transmit_enabled: return bool2string(pp->limited_transmit_enabled);
        case FIELD_increased_IW_enabled: return bool2string(pp->increased_IW_enabled);
        case FIELD_full_sized_segment_counter: return ulong2string(pp->full_sized_segment_counter);
        case FIELD_ack_now: return bool2string(pp->ack_now);
        case FIELD_afterRto: return bool2string(pp->afterRto);
        case FIELD_ws_support: return bool2string(pp->ws_support);
        case FIELD_ws_enabled: return bool2string(pp->ws_enabled);
        case FIELD_ws_manual_scale: return long2string(pp->ws_manual_scale);
        case FIELD_snd_ws: return bool2string(pp->snd_ws);
        case FIELD_rcv_ws: return bool2string(pp->rcv_ws);
        case FIELD_rcv_wnd_scale: return ulong2string(pp->rcv_wnd_scale);
        case FIELD_snd_wnd_scale: return ulong2string(pp->snd_wnd_scale);
        case FIELD_ts_support: return bool2string(pp->ts_support);
        case FIELD_ts_enabled: return bool2string(pp->ts_enabled);
        case FIELD_snd_initial_ts: return bool2string(pp->snd_initial_ts);
        case FIELD_rcv_initial_ts: return bool2string(pp->rcv_initial_ts);
        case FIELD_ts_recent: return ulong2string(pp->ts_recent);
        case FIELD_last_ack_sent: return ulong2string(pp->last_ack_sent);
        case FIELD_time_last_data_sent: return simtime2string(pp->time_last_data_sent);
        case FIELD_sack_support: return bool2string(pp->sack_support);
        case FIELD_sack_enabled: return bool2string(pp->sack_enabled);
        case FIELD_snd_sack_perm: return bool2string(pp->snd_sack_perm);
        case FIELD_rcv_sack_perm: return bool2string(pp->rcv_sack_perm);
        case FIELD_start_seqno: return ulong2string(pp->start_seqno);
        case FIELD_end_seqno: return ulong2string(pp->end_seqno);
        case FIELD_snd_sack: return bool2string(pp->snd_sack);
        case FIELD_snd_dsack: return bool2string(pp->snd_dsack);
        case FIELD_highRxt: return ulong2string(pp->highRxt);
        case FIELD_pipe: return ulong2string(pp->pipe);
        case FIELD_recoveryPoint: return ulong2string(pp->recoveryPoint);
        case FIELD_sackedBytes: return ulong2string(pp->sackedBytes);
        case FIELD_sackedBytes_old: return ulong2string(pp->sackedBytes_old);
        case FIELD_lossRecovery: return bool2string(pp->lossRecovery);
        case FIELD_sendQueueLimit: return ulong2string(pp->sendQueueLimit);
        case FIELD_queueUpdate: return bool2string(pp->queueUpdate);
        case FIELD_dupacks: return ulong2string(pp->dupacks);
        case FIELD_snd_sacks: return ulong2string(pp->snd_sacks);
        case FIELD_rcv_sacks: return ulong2string(pp->rcv_sacks);
        case FIELD_rcv_oooseg: return ulong2string(pp->rcv_oooseg);
        case FIELD_rcv_naseg: return ulong2string(pp->rcv_naseg);
        case FIELD_maxRcvBuffer: return ulong2string(pp->maxRcvBuffer);
        case FIELD_usedRcvBuffer: return ulong2string(pp->usedRcvBuffer);
        case FIELD_freeRcvBuffer: return ulong2string(pp->freeRcvBuffer);
        case FIELD_tcpRcvQueueDrops: return ulong2string(pp->tcpRcvQueueDrops);
        default: return "";
    }
}

void TcpStateVariablesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStateVariables'", field);
    }
}

omnetpp::cValue TcpStateVariablesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        case FIELD_active: return pp->active;
        case FIELD_fork: return pp->fork;
        case FIELD_snd_mss: return (omnetpp::intval_t)(pp->snd_mss);
        case FIELD_snd_una: return (omnetpp::intval_t)(pp->snd_una);
        case FIELD_snd_nxt: return (omnetpp::intval_t)(pp->snd_nxt);
        case FIELD_snd_max: return (omnetpp::intval_t)(pp->snd_max);
        case FIELD_snd_wnd: return (omnetpp::intval_t)(pp->snd_wnd);
        case FIELD_snd_up: return (omnetpp::intval_t)(pp->snd_up);
        case FIELD_snd_wl1: return (omnetpp::intval_t)(pp->snd_wl1);
        case FIELD_snd_wl2: return (omnetpp::intval_t)(pp->snd_wl2);
        case FIELD_iss: return (omnetpp::intval_t)(pp->iss);
        case FIELD_rcv_nxt: return (omnetpp::intval_t)(pp->rcv_nxt);
        case FIELD_rcv_wnd: return (omnetpp::intval_t)(pp->rcv_wnd);
        case FIELD_rcv_up: return (omnetpp::intval_t)(pp->rcv_up);
        case FIELD_irs: return (omnetpp::intval_t)(pp->irs);
        case FIELD_rcv_adv: return (omnetpp::intval_t)(pp->rcv_adv);
        case FIELD_syn_rexmit_count: return pp->syn_rexmit_count;
        case FIELD_syn_rexmit_timeout: return pp->syn_rexmit_timeout.dbl();
        case FIELD_fin_ack_rcvd: return pp->fin_ack_rcvd;
        case FIELD_send_fin: return pp->send_fin;
        case FIELD_snd_fin_seq: return (omnetpp::intval_t)(pp->snd_fin_seq);
        case FIELD_fin_rcvd: return pp->fin_rcvd;
        case FIELD_rcv_fin_seq: return (omnetpp::intval_t)(pp->rcv_fin_seq);
        case FIELD_nagle_enabled: return pp->nagle_enabled;
        case FIELD_delayed_acks_enabled: return pp->delayed_acks_enabled;
        case FIELD_limited_transmit_enabled: return pp->limited_transmit_enabled;
        case FIELD_increased_IW_enabled: return pp->increased_IW_enabled;
        case FIELD_full_sized_segment_counter: return (omnetpp::intval_t)(pp->full_sized_segment_counter);
        case FIELD_ack_now: return pp->ack_now;
        case FIELD_afterRto: return pp->afterRto;
        case FIELD_ws_support: return pp->ws_support;
        case FIELD_ws_enabled: return pp->ws_enabled;
        case FIELD_ws_manual_scale: return pp->ws_manual_scale;
        case FIELD_snd_ws: return pp->snd_ws;
        case FIELD_rcv_ws: return pp->rcv_ws;
        case FIELD_rcv_wnd_scale: return (omnetpp::intval_t)(pp->rcv_wnd_scale);
        case FIELD_snd_wnd_scale: return (omnetpp::intval_t)(pp->snd_wnd_scale);
        case FIELD_ts_support: return pp->ts_support;
        case FIELD_ts_enabled: return pp->ts_enabled;
        case FIELD_snd_initial_ts: return pp->snd_initial_ts;
        case FIELD_rcv_initial_ts: return pp->rcv_initial_ts;
        case FIELD_ts_recent: return (omnetpp::intval_t)(pp->ts_recent);
        case FIELD_last_ack_sent: return (omnetpp::intval_t)(pp->last_ack_sent);
        case FIELD_time_last_data_sent: return pp->time_last_data_sent.dbl();
        case FIELD_sack_support: return pp->sack_support;
        case FIELD_sack_enabled: return pp->sack_enabled;
        case FIELD_snd_sack_perm: return pp->snd_sack_perm;
        case FIELD_rcv_sack_perm: return pp->rcv_sack_perm;
        case FIELD_start_seqno: return (omnetpp::intval_t)(pp->start_seqno);
        case FIELD_end_seqno: return (omnetpp::intval_t)(pp->end_seqno);
        case FIELD_snd_sack: return pp->snd_sack;
        case FIELD_snd_dsack: return pp->snd_dsack;
        case FIELD_highRxt: return (omnetpp::intval_t)(pp->highRxt);
        case FIELD_pipe: return (omnetpp::intval_t)(pp->pipe);
        case FIELD_recoveryPoint: return (omnetpp::intval_t)(pp->recoveryPoint);
        case FIELD_sackedBytes: return (omnetpp::intval_t)(pp->sackedBytes);
        case FIELD_sackedBytes_old: return (omnetpp::intval_t)(pp->sackedBytes_old);
        case FIELD_lossRecovery: return pp->lossRecovery;
        case FIELD_sendQueueLimit: return (omnetpp::intval_t)(pp->sendQueueLimit);
        case FIELD_queueUpdate: return pp->queueUpdate;
        case FIELD_dupacks: return (omnetpp::intval_t)(pp->dupacks);
        case FIELD_snd_sacks: return (omnetpp::intval_t)(pp->snd_sacks);
        case FIELD_rcv_sacks: return (omnetpp::intval_t)(pp->rcv_sacks);
        case FIELD_rcv_oooseg: return (omnetpp::intval_t)(pp->rcv_oooseg);
        case FIELD_rcv_naseg: return (omnetpp::intval_t)(pp->rcv_naseg);
        case FIELD_maxRcvBuffer: return (omnetpp::intval_t)(pp->maxRcvBuffer);
        case FIELD_usedRcvBuffer: return (omnetpp::intval_t)(pp->usedRcvBuffer);
        case FIELD_freeRcvBuffer: return (omnetpp::intval_t)(pp->freeRcvBuffer);
        case FIELD_tcpRcvQueueDrops: return (omnetpp::intval_t)(pp->tcpRcvQueueDrops);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpStateVariables' as cValue -- field index out of range?", field);
    }
}

void TcpStateVariablesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStateVariables'", field);
    }
}

const char *TcpStateVariablesDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr TcpStateVariablesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpStateVariablesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpStateVariables *pp = omnetpp::fromAnyPtr<TcpStateVariables>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpStateVariables'", field);
    }
}

class TcpSendQueueDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dataBuffer,
    };
  public:
    TcpSendQueueDescriptor();
    virtual ~TcpSendQueueDescriptor();

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

Register_ClassDescriptor(TcpSendQueueDescriptor)

TcpSendQueueDescriptor::TcpSendQueueDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpSendQueue)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TcpSendQueueDescriptor::~TcpSendQueueDescriptor()
{
    delete[] propertyNames;
}

bool TcpSendQueueDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpSendQueue *>(obj)!=nullptr;
}

const char **TcpSendQueueDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpSendQueueDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpSendQueueDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpSendQueueDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_dataBuffer
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpSendQueueDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dataBuffer",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpSendQueueDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dataBuffer") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpSendQueueDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ChunkQueue",    // FIELD_dataBuffer
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpSendQueueDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpSendQueueDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpSendQueueDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpSendQueueDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpSendQueue'", field);
    }
}

const char *TcpSendQueueDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpSendQueueDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        case FIELD_dataBuffer: return pp->getDataBuffer().str();
        default: return "";
    }
}

void TcpSendQueueDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSendQueue'", field);
    }
}

omnetpp::cValue TcpSendQueueDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        case FIELD_dataBuffer: return omnetpp::toAnyPtr(&pp->getDataBuffer()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpSendQueue' as cValue -- field index out of range?", field);
    }
}

void TcpSendQueueDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSendQueue'", field);
    }
}

const char *TcpSendQueueDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_dataBuffer: return omnetpp::opp_typename(typeid(::inet::ChunkQueue));
        default: return nullptr;
    };
}

omnetpp::any_ptr TcpSendQueueDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        case FIELD_dataBuffer: return omnetpp::toAnyPtr(&pp->getDataBuffer()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpSendQueueDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpSendQueue *pp = omnetpp::fromAnyPtr<TcpSendQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpSendQueue'", field);
    }
}

class TcpReceiveQueueDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_reorderBuffer,
    };
  public:
    TcpReceiveQueueDescriptor();
    virtual ~TcpReceiveQueueDescriptor();

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

Register_ClassDescriptor(TcpReceiveQueueDescriptor)

TcpReceiveQueueDescriptor::TcpReceiveQueueDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpReceiveQueue)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TcpReceiveQueueDescriptor::~TcpReceiveQueueDescriptor()
{
    delete[] propertyNames;
}

bool TcpReceiveQueueDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpReceiveQueue *>(obj)!=nullptr;
}

const char **TcpReceiveQueueDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpReceiveQueueDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpReceiveQueueDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int TcpReceiveQueueDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND | FD_ISCOBJECT,    // FIELD_reorderBuffer
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *TcpReceiveQueueDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "reorderBuffer",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int TcpReceiveQueueDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "reorderBuffer") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpReceiveQueueDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "inet::ReorderBuffer",    // FIELD_reorderBuffer
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpReceiveQueueDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpReceiveQueueDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpReceiveQueueDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpReceiveQueueDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpReceiveQueue'", field);
    }
}

const char *TcpReceiveQueueDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TcpReceiveQueueDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        case FIELD_reorderBuffer: return pp->getReorderBuffer().str();
        default: return "";
    }
}

void TcpReceiveQueueDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpReceiveQueue'", field);
    }
}

omnetpp::cValue TcpReceiveQueueDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        case FIELD_reorderBuffer: return omnetpp::toAnyPtr(&pp->getReorderBuffer()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpReceiveQueue' as cValue -- field index out of range?", field);
    }
}

void TcpReceiveQueueDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpReceiveQueue'", field);
    }
}

const char *TcpReceiveQueueDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_reorderBuffer: return omnetpp::opp_typename(typeid(::inet::ReorderBuffer));
        default: return nullptr;
    };
}

omnetpp::any_ptr TcpReceiveQueueDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        case FIELD_reorderBuffer: return omnetpp::toAnyPtr(&pp->getReorderBuffer()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpReceiveQueueDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpReceiveQueue *pp = omnetpp::fromAnyPtr<TcpReceiveQueue>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpReceiveQueue'", field);
    }
}

class TcpConnectionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_socketId,
        FIELD_listeningSocketId,
        FIELD_localAddr,
        FIELD_remoteAddr,
        FIELD_localPort,
        FIELD_remotePort,
        FIELD_state,
        FIELD_sendQueue,
        FIELD_receiveQueue,
        FIELD_rexmitQueue,
        FIELD_tcpAlgorithm,
        FIELD_fsmState,
    };
  public:
    TcpConnectionDescriptor();
    virtual ~TcpConnectionDescriptor();

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

Register_ClassDescriptor(TcpConnectionDescriptor)

TcpConnectionDescriptor::TcpConnectionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::tcp::TcpConnection)), "omnetpp::cObject")
{
    propertyNames = nullptr;
}

TcpConnectionDescriptor::~TcpConnectionDescriptor()
{
    delete[] propertyNames;
}

bool TcpConnectionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TcpConnection *>(obj)!=nullptr;
}

const char **TcpConnectionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass", "descriptor",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TcpConnectionDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    if (!strcmp(propertyName, "descriptor")) return "readonly";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TcpConnectionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 12+base->getFieldCount() : 12;
}

unsigned int TcpConnectionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        0,    // FIELD_socketId
        0,    // FIELD_listeningSocketId
        0,    // FIELD_localAddr
        0,    // FIELD_remoteAddr
        0,    // FIELD_localPort
        0,    // FIELD_remotePort
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_state
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_sendQueue
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_receiveQueue
        FD_ISCOMPOUND | FD_ISPOINTER,    // FIELD_rexmitQueue
        FD_ISCOMPOUND | FD_ISPOINTER | FD_ISCOBJECT,    // FIELD_tcpAlgorithm
        0,    // FIELD_fsmState
    };
    return (field >= 0 && field < 12) ? fieldTypeFlags[field] : 0;
}

const char *TcpConnectionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "socketId",
        "listeningSocketId",
        "localAddr",
        "remoteAddr",
        "localPort",
        "remotePort",
        "state",
        "sendQueue",
        "receiveQueue",
        "rexmitQueue",
        "tcpAlgorithm",
        "fsmState",
    };
    return (field >= 0 && field < 12) ? fieldNames[field] : nullptr;
}

int TcpConnectionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "socketId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "listeningSocketId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "localAddr") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "remoteAddr") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "localPort") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "remotePort") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "state") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "sendQueue") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "receiveQueue") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "rexmitQueue") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "tcpAlgorithm") == 0) return baseIndex + 10;
    if (strcmp(fieldName, "fsmState") == 0) return baseIndex + 11;
    return base ? base->findField(fieldName) : -1;
}

const char *TcpConnectionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_socketId
        "int",    // FIELD_listeningSocketId
        "inet::L3Address",    // FIELD_localAddr
        "inet::L3Address",    // FIELD_remoteAddr
        "int",    // FIELD_localPort
        "int",    // FIELD_remotePort
        "inet::tcp::TcpStateVariables",    // FIELD_state
        "inet::tcp::TcpSendQueue",    // FIELD_sendQueue
        "inet::tcp::TcpReceiveQueue",    // FIELD_receiveQueue
        "inet::tcp::TcpSackRexmitQueue",    // FIELD_rexmitQueue
        "inet::tcp::TcpAlgorithm",    // FIELD_tcpAlgorithm
        "int",    // FIELD_fsmState
    };
    return (field >= 0 && field < 12) ? fieldTypeStrings[field] : nullptr;
}

const char **TcpConnectionDescriptor::getFieldPropertyNames(int field) const
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

const char *TcpConnectionDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int TcpConnectionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TcpConnectionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TcpConnection'", field);
    }
}

const char *TcpConnectionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        case FIELD_state: { const TcpStateVariables * value = pp->getState(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_sendQueue: { const TcpSendQueue * value = pp->getSendQueue(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_receiveQueue: { const TcpReceiveQueue * value = pp->getReceiveQueue(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_rexmitQueue: { const TcpSackRexmitQueue * value = pp->getRexmitQueue(); return omnetpp::opp_typename(typeid(*value)); }
        case FIELD_tcpAlgorithm: { const TcpAlgorithm * value = pp->getTcpAlgorithm(); return omnetpp::opp_typename(typeid(*value)); }
        default: return nullptr;
    }
}

std::string TcpConnectionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        case FIELD_socketId: return long2string(pp->getSocketId());
        case FIELD_listeningSocketId: return long2string(pp->getListeningSocketId());
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return long2string(pp->getLocalPort());
        case FIELD_remotePort: return long2string(pp->getRemotePort());
        case FIELD_state: return "";
        case FIELD_sendQueue: { auto obj = pp->getSendQueue(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_receiveQueue: { auto obj = pp->getReceiveQueue(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_rexmitQueue: return "";
        case FIELD_tcpAlgorithm: { auto obj = pp->getTcpAlgorithm(); return obj == nullptr ? "" : obj->str(); }
        case FIELD_fsmState: return long2string(pp->getFsmState());
        default: return "";
    }
}

void TcpConnectionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpConnection'", field);
    }
}

omnetpp::cValue TcpConnectionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        case FIELD_socketId: return pp->getSocketId();
        case FIELD_listeningSocketId: return pp->getListeningSocketId();
        case FIELD_localAddr: return pp->getLocalAddr().str();
        case FIELD_remoteAddr: return pp->getRemoteAddr().str();
        case FIELD_localPort: return pp->getLocalPort();
        case FIELD_remotePort: return pp->getRemotePort();
        case FIELD_state: return omnetpp::toAnyPtr(pp->getState()); break;
        case FIELD_sendQueue: return omnetpp::toAnyPtr(pp->getSendQueue()); break;
        case FIELD_receiveQueue: return omnetpp::toAnyPtr(pp->getReceiveQueue()); break;
        case FIELD_rexmitQueue: return omnetpp::toAnyPtr(pp->getRexmitQueue()); break;
        case FIELD_tcpAlgorithm: return omnetpp::toAnyPtr(pp->getTcpAlgorithm()); break;
        case FIELD_fsmState: return pp->getFsmState();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TcpConnection' as cValue -- field index out of range?", field);
    }
}

void TcpConnectionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpConnection'", field);
    }
}

const char *TcpConnectionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_state: return omnetpp::opp_typename(typeid(TcpStateVariables));
        case FIELD_sendQueue: return omnetpp::opp_typename(typeid(TcpSendQueue));
        case FIELD_receiveQueue: return omnetpp::opp_typename(typeid(TcpReceiveQueue));
        case FIELD_rexmitQueue: return omnetpp::opp_typename(typeid(TcpSackRexmitQueue));
        case FIELD_tcpAlgorithm: return omnetpp::opp_typename(typeid(TcpAlgorithm));
        default: return nullptr;
    };
}

omnetpp::any_ptr TcpConnectionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        case FIELD_localAddr: return omnetpp::toAnyPtr(&pp->getLocalAddr()); break;
        case FIELD_remoteAddr: return omnetpp::toAnyPtr(&pp->getRemoteAddr()); break;
        case FIELD_state: return omnetpp::toAnyPtr(pp->getState()); break;
        case FIELD_sendQueue: return omnetpp::toAnyPtr(pp->getSendQueue()); break;
        case FIELD_receiveQueue: return omnetpp::toAnyPtr(pp->getReceiveQueue()); break;
        case FIELD_rexmitQueue: return omnetpp::toAnyPtr(pp->getRexmitQueue()); break;
        case FIELD_tcpAlgorithm: return omnetpp::toAnyPtr(pp->getTcpAlgorithm()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TcpConnectionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TcpConnection *pp = omnetpp::fromAnyPtr<TcpConnection>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TcpConnection'", field);
    }
}

}  // namespace tcp
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp


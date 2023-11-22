//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/applications/httptools/common/HttpEventMessages.msg.
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
#include "HttpEventMessages_m.h"

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
namespace httptools {

Register_Class(HttpServerStatusUpdateMsg)

HttpServerStatusUpdateMsg::HttpServerStatusUpdateMsg(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

HttpServerStatusUpdateMsg::HttpServerStatusUpdateMsg(const HttpServerStatusUpdateMsg& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

HttpServerStatusUpdateMsg::~HttpServerStatusUpdateMsg()
{
}

HttpServerStatusUpdateMsg& HttpServerStatusUpdateMsg::operator=(const HttpServerStatusUpdateMsg& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void HttpServerStatusUpdateMsg::copy(const HttpServerStatusUpdateMsg& other)
{
    this->www = other.www;
    this->setTime = other.setTime;
    this->eventKind = other.eventKind;
    this->pvalue = other.pvalue;
    this->pamortize = other.pamortize;
}

void HttpServerStatusUpdateMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->www);
    doParsimPacking(b,this->setTime);
    doParsimPacking(b,this->eventKind);
    doParsimPacking(b,this->pvalue);
    doParsimPacking(b,this->pamortize);
}

void HttpServerStatusUpdateMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->www);
    doParsimUnpacking(b,this->setTime);
    doParsimUnpacking(b,this->eventKind);
    doParsimUnpacking(b,this->pvalue);
    doParsimUnpacking(b,this->pamortize);
}

const char * HttpServerStatusUpdateMsg::getWww() const
{
    return this->www.c_str();
}

void HttpServerStatusUpdateMsg::setWww(const char * www)
{
    this->www = www;
}

::omnetpp::simtime_t HttpServerStatusUpdateMsg::getSetTime() const
{
    return this->setTime;
}

void HttpServerStatusUpdateMsg::setSetTime(::omnetpp::simtime_t setTime)
{
    this->setTime = setTime;
}

int HttpServerStatusUpdateMsg::getEventKind() const
{
    return this->eventKind;
}

void HttpServerStatusUpdateMsg::setEventKind(int eventKind)
{
    this->eventKind = eventKind;
}

double HttpServerStatusUpdateMsg::getPvalue() const
{
    return this->pvalue;
}

void HttpServerStatusUpdateMsg::setPvalue(double pvalue)
{
    this->pvalue = pvalue;
}

double HttpServerStatusUpdateMsg::getPamortize() const
{
    return this->pamortize;
}

void HttpServerStatusUpdateMsg::setPamortize(double pamortize)
{
    this->pamortize = pamortize;
}

class HttpServerStatusUpdateMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_www,
        FIELD_setTime,
        FIELD_eventKind,
        FIELD_pvalue,
        FIELD_pamortize,
    };
  public:
    HttpServerStatusUpdateMsgDescriptor();
    virtual ~HttpServerStatusUpdateMsgDescriptor();

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

Register_ClassDescriptor(HttpServerStatusUpdateMsgDescriptor)

HttpServerStatusUpdateMsgDescriptor::HttpServerStatusUpdateMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::httptools::HttpServerStatusUpdateMsg)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

HttpServerStatusUpdateMsgDescriptor::~HttpServerStatusUpdateMsgDescriptor()
{
    delete[] propertyNames;
}

bool HttpServerStatusUpdateMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HttpServerStatusUpdateMsg *>(obj)!=nullptr;
}

const char **HttpServerStatusUpdateMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HttpServerStatusUpdateMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HttpServerStatusUpdateMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int HttpServerStatusUpdateMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_www
        FD_ISEDITABLE,    // FIELD_setTime
        FD_ISEDITABLE,    // FIELD_eventKind
        FD_ISEDITABLE,    // FIELD_pvalue
        FD_ISEDITABLE,    // FIELD_pamortize
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *HttpServerStatusUpdateMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "www",
        "setTime",
        "eventKind",
        "pvalue",
        "pamortize",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int HttpServerStatusUpdateMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "www") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "setTime") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "eventKind") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "pvalue") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "pamortize") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *HttpServerStatusUpdateMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_www
        "omnetpp::simtime_t",    // FIELD_setTime
        "int",    // FIELD_eventKind
        "double",    // FIELD_pvalue
        "double",    // FIELD_pamortize
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **HttpServerStatusUpdateMsgDescriptor::getFieldPropertyNames(int field) const
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

const char *HttpServerStatusUpdateMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HttpServerStatusUpdateMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HttpServerStatusUpdateMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HttpServerStatusUpdateMsg'", field);
    }
}

const char *HttpServerStatusUpdateMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HttpServerStatusUpdateMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_www: return oppstring2string(pp->getWww());
        case FIELD_setTime: return simtime2string(pp->getSetTime());
        case FIELD_eventKind: return long2string(pp->getEventKind());
        case FIELD_pvalue: return double2string(pp->getPvalue());
        case FIELD_pamortize: return double2string(pp->getPamortize());
        default: return "";
    }
}

void HttpServerStatusUpdateMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_www: pp->setWww((value)); break;
        case FIELD_setTime: pp->setSetTime(string2simtime(value)); break;
        case FIELD_eventKind: pp->setEventKind(string2long(value)); break;
        case FIELD_pvalue: pp->setPvalue(string2double(value)); break;
        case FIELD_pamortize: pp->setPamortize(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpServerStatusUpdateMsg'", field);
    }
}

omnetpp::cValue HttpServerStatusUpdateMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_www: return pp->getWww();
        case FIELD_setTime: return pp->getSetTime().dbl();
        case FIELD_eventKind: return pp->getEventKind();
        case FIELD_pvalue: return pp->getPvalue();
        case FIELD_pamortize: return pp->getPamortize();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HttpServerStatusUpdateMsg' as cValue -- field index out of range?", field);
    }
}

void HttpServerStatusUpdateMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_www: pp->setWww(value.stringValue()); break;
        case FIELD_setTime: pp->setSetTime(value.doubleValue()); break;
        case FIELD_eventKind: pp->setEventKind(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_pvalue: pp->setPvalue(value.doubleValue()); break;
        case FIELD_pamortize: pp->setPamortize(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpServerStatusUpdateMsg'", field);
    }
}

const char *HttpServerStatusUpdateMsgDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HttpServerStatusUpdateMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HttpServerStatusUpdateMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpServerStatusUpdateMsg *pp = omnetpp::fromAnyPtr<HttpServerStatusUpdateMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpServerStatusUpdateMsg'", field);
    }
}

}  // namespace httptools
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp


//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/applications/httptools/common/HttpMessages.msg.
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
#include "HttpMessages_m.h"

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

Register_Class(HttpBaseMessage)

HttpBaseMessage::HttpBaseMessage() : ::inet::FieldsChunk()
{
}

HttpBaseMessage::HttpBaseMessage(const HttpBaseMessage& other) : ::inet::FieldsChunk(other)
{
    copy(other);
}

HttpBaseMessage::~HttpBaseMessage()
{
}

HttpBaseMessage& HttpBaseMessage::operator=(const HttpBaseMessage& other)
{
    if (this == &other) return *this;
    ::inet::FieldsChunk::operator=(other);
    copy(other);
    return *this;
}

void HttpBaseMessage::copy(const HttpBaseMessage& other)
{
    this->targetUrl = other.targetUrl;
    this->originatorUrl = other.originatorUrl;
    this->protocol = other.protocol;
    this->keepAlive = other.keepAlive;
    this->serial = other.serial;
    this->heading = other.heading;
    this->payload = other.payload;
}

void HttpBaseMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::FieldsChunk::parsimPack(b);
    doParsimPacking(b,this->targetUrl);
    doParsimPacking(b,this->originatorUrl);
    doParsimPacking(b,this->protocol);
    doParsimPacking(b,this->keepAlive);
    doParsimPacking(b,this->serial);
    doParsimPacking(b,this->heading);
    doParsimPacking(b,this->payload);
}

void HttpBaseMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::FieldsChunk::parsimUnpack(b);
    doParsimUnpacking(b,this->targetUrl);
    doParsimUnpacking(b,this->originatorUrl);
    doParsimUnpacking(b,this->protocol);
    doParsimUnpacking(b,this->keepAlive);
    doParsimUnpacking(b,this->serial);
    doParsimUnpacking(b,this->heading);
    doParsimUnpacking(b,this->payload);
}

const char * HttpBaseMessage::getTargetUrl() const
{
    return this->targetUrl.c_str();
}

void HttpBaseMessage::setTargetUrl(const char * targetUrl)
{
    handleChange();
    this->targetUrl = targetUrl;
}

const char * HttpBaseMessage::getOriginatorUrl() const
{
    return this->originatorUrl.c_str();
}

void HttpBaseMessage::setOriginatorUrl(const char * originatorUrl)
{
    handleChange();
    this->originatorUrl = originatorUrl;
}

int HttpBaseMessage::getProtocol() const
{
    return this->protocol;
}

void HttpBaseMessage::setProtocol(int protocol)
{
    handleChange();
    this->protocol = protocol;
}

bool HttpBaseMessage::getKeepAlive() const
{
    return this->keepAlive;
}

void HttpBaseMessage::setKeepAlive(bool keepAlive)
{
    handleChange();
    this->keepAlive = keepAlive;
}

int HttpBaseMessage::getSerial() const
{
    return this->serial;
}

void HttpBaseMessage::setSerial(int serial)
{
    handleChange();
    this->serial = serial;
}

const char * HttpBaseMessage::getHeading() const
{
    return this->heading.c_str();
}

void HttpBaseMessage::setHeading(const char * heading)
{
    handleChange();
    this->heading = heading;
}

const char * HttpBaseMessage::getPayload() const
{
    return this->payload.c_str();
}

void HttpBaseMessage::setPayload(const char * payload)
{
    handleChange();
    this->payload = payload;
}

class HttpBaseMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_targetUrl,
        FIELD_originatorUrl,
        FIELD_protocol,
        FIELD_keepAlive,
        FIELD_serial,
        FIELD_heading,
        FIELD_payload,
    };
  public:
    HttpBaseMessageDescriptor();
    virtual ~HttpBaseMessageDescriptor();

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

Register_ClassDescriptor(HttpBaseMessageDescriptor)

HttpBaseMessageDescriptor::HttpBaseMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::httptools::HttpBaseMessage)), "inet::FieldsChunk")
{
    propertyNames = nullptr;
}

HttpBaseMessageDescriptor::~HttpBaseMessageDescriptor()
{
    delete[] propertyNames;
}

bool HttpBaseMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HttpBaseMessage *>(obj)!=nullptr;
}

const char **HttpBaseMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HttpBaseMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HttpBaseMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int HttpBaseMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_targetUrl
        FD_ISEDITABLE,    // FIELD_originatorUrl
        FD_ISEDITABLE,    // FIELD_protocol
        FD_ISEDITABLE,    // FIELD_keepAlive
        FD_ISEDITABLE,    // FIELD_serial
        FD_ISEDITABLE,    // FIELD_heading
        FD_ISEDITABLE,    // FIELD_payload
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *HttpBaseMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "targetUrl",
        "originatorUrl",
        "protocol",
        "keepAlive",
        "serial",
        "heading",
        "payload",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int HttpBaseMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "targetUrl") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "originatorUrl") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "protocol") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "keepAlive") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "serial") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "heading") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "payload") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *HttpBaseMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_targetUrl
        "string",    // FIELD_originatorUrl
        "int",    // FIELD_protocol
        "bool",    // FIELD_keepAlive
        "int",    // FIELD_serial
        "string",    // FIELD_heading
        "string",    // FIELD_payload
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **HttpBaseMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *HttpBaseMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HttpBaseMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HttpBaseMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HttpBaseMessage'", field);
    }
}

const char *HttpBaseMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HttpBaseMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        case FIELD_targetUrl: return oppstring2string(pp->getTargetUrl());
        case FIELD_originatorUrl: return oppstring2string(pp->getOriginatorUrl());
        case FIELD_protocol: return long2string(pp->getProtocol());
        case FIELD_keepAlive: return bool2string(pp->getKeepAlive());
        case FIELD_serial: return long2string(pp->getSerial());
        case FIELD_heading: return oppstring2string(pp->getHeading());
        case FIELD_payload: return oppstring2string(pp->getPayload());
        default: return "";
    }
}

void HttpBaseMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        case FIELD_targetUrl: pp->setTargetUrl((value)); break;
        case FIELD_originatorUrl: pp->setOriginatorUrl((value)); break;
        case FIELD_protocol: pp->setProtocol(string2long(value)); break;
        case FIELD_keepAlive: pp->setKeepAlive(string2bool(value)); break;
        case FIELD_serial: pp->setSerial(string2long(value)); break;
        case FIELD_heading: pp->setHeading((value)); break;
        case FIELD_payload: pp->setPayload((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpBaseMessage'", field);
    }
}

omnetpp::cValue HttpBaseMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        case FIELD_targetUrl: return pp->getTargetUrl();
        case FIELD_originatorUrl: return pp->getOriginatorUrl();
        case FIELD_protocol: return pp->getProtocol();
        case FIELD_keepAlive: return pp->getKeepAlive();
        case FIELD_serial: return pp->getSerial();
        case FIELD_heading: return pp->getHeading();
        case FIELD_payload: return pp->getPayload();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HttpBaseMessage' as cValue -- field index out of range?", field);
    }
}

void HttpBaseMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        case FIELD_targetUrl: pp->setTargetUrl(value.stringValue()); break;
        case FIELD_originatorUrl: pp->setOriginatorUrl(value.stringValue()); break;
        case FIELD_protocol: pp->setProtocol(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_keepAlive: pp->setKeepAlive(value.boolValue()); break;
        case FIELD_serial: pp->setSerial(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_heading: pp->setHeading(value.stringValue()); break;
        case FIELD_payload: pp->setPayload(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpBaseMessage'", field);
    }
}

const char *HttpBaseMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HttpBaseMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HttpBaseMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpBaseMessage *pp = omnetpp::fromAnyPtr<HttpBaseMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpBaseMessage'", field);
    }
}

Register_Class(HttpRequestMessage)

HttpRequestMessage::HttpRequestMessage() : ::inet::httptools::HttpBaseMessage()
{
}

HttpRequestMessage::HttpRequestMessage(const HttpRequestMessage& other) : ::inet::httptools::HttpBaseMessage(other)
{
    copy(other);
}

HttpRequestMessage::~HttpRequestMessage()
{
}

HttpRequestMessage& HttpRequestMessage::operator=(const HttpRequestMessage& other)
{
    if (this == &other) return *this;
    ::inet::httptools::HttpBaseMessage::operator=(other);
    copy(other);
    return *this;
}

void HttpRequestMessage::copy(const HttpRequestMessage& other)
{
    this->badRequest = other.badRequest;
}

void HttpRequestMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::httptools::HttpBaseMessage::parsimPack(b);
    doParsimPacking(b,this->badRequest);
}

void HttpRequestMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::httptools::HttpBaseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->badRequest);
}

bool HttpRequestMessage::getBadRequest() const
{
    return this->badRequest;
}

void HttpRequestMessage::setBadRequest(bool badRequest)
{
    handleChange();
    this->badRequest = badRequest;
}

class HttpRequestMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_badRequest,
    };
  public:
    HttpRequestMessageDescriptor();
    virtual ~HttpRequestMessageDescriptor();

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

Register_ClassDescriptor(HttpRequestMessageDescriptor)

HttpRequestMessageDescriptor::HttpRequestMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::httptools::HttpRequestMessage)), "inet::httptools::HttpBaseMessage")
{
    propertyNames = nullptr;
}

HttpRequestMessageDescriptor::~HttpRequestMessageDescriptor()
{
    delete[] propertyNames;
}

bool HttpRequestMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HttpRequestMessage *>(obj)!=nullptr;
}

const char **HttpRequestMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HttpRequestMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HttpRequestMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int HttpRequestMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_badRequest
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *HttpRequestMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "badRequest",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int HttpRequestMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "badRequest") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *HttpRequestMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_badRequest
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **HttpRequestMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *HttpRequestMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int HttpRequestMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HttpRequestMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HttpRequestMessage'", field);
    }
}

const char *HttpRequestMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HttpRequestMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        case FIELD_badRequest: return bool2string(pp->getBadRequest());
        default: return "";
    }
}

void HttpRequestMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        case FIELD_badRequest: pp->setBadRequest(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpRequestMessage'", field);
    }
}

omnetpp::cValue HttpRequestMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        case FIELD_badRequest: return pp->getBadRequest();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HttpRequestMessage' as cValue -- field index out of range?", field);
    }
}

void HttpRequestMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        case FIELD_badRequest: pp->setBadRequest(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpRequestMessage'", field);
    }
}

const char *HttpRequestMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HttpRequestMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HttpRequestMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpRequestMessage *pp = omnetpp::fromAnyPtr<HttpRequestMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpRequestMessage'", field);
    }
}

Register_Enum(inet::httptools::HttpContentType, (inet::httptools::HttpContentType::CT_UNKNOWN, inet::httptools::HttpContentType::CT_HTML, inet::httptools::HttpContentType::CT_IMAGE, inet::httptools::HttpContentType::CT_TEXT));

Register_Class(HttpReplyMessage)

HttpReplyMessage::HttpReplyMessage() : ::inet::httptools::HttpBaseMessage()
{
}

HttpReplyMessage::HttpReplyMessage(const HttpReplyMessage& other) : ::inet::httptools::HttpBaseMessage(other)
{
    copy(other);
}

HttpReplyMessage::~HttpReplyMessage()
{
}

HttpReplyMessage& HttpReplyMessage::operator=(const HttpReplyMessage& other)
{
    if (this == &other) return *this;
    ::inet::httptools::HttpBaseMessage::operator=(other);
    copy(other);
    return *this;
}

void HttpReplyMessage::copy(const HttpReplyMessage& other)
{
    this->result = other.result;
    this->contentType = other.contentType;
}

void HttpReplyMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::httptools::HttpBaseMessage::parsimPack(b);
    doParsimPacking(b,this->result);
    doParsimPacking(b,this->contentType);
}

void HttpReplyMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::httptools::HttpBaseMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->result);
    doParsimUnpacking(b,this->contentType);
}

int HttpReplyMessage::getResult() const
{
    return this->result;
}

void HttpReplyMessage::setResult(int result)
{
    handleChange();
    this->result = result;
}

HttpContentType HttpReplyMessage::getContentType() const
{
    return this->contentType;
}

void HttpReplyMessage::setContentType(HttpContentType contentType)
{
    handleChange();
    this->contentType = contentType;
}

class HttpReplyMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_result,
        FIELD_contentType,
    };
  public:
    HttpReplyMessageDescriptor();
    virtual ~HttpReplyMessageDescriptor();

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

Register_ClassDescriptor(HttpReplyMessageDescriptor)

HttpReplyMessageDescriptor::HttpReplyMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(inet::httptools::HttpReplyMessage)), "inet::httptools::HttpBaseMessage")
{
    propertyNames = nullptr;
}

HttpReplyMessageDescriptor::~HttpReplyMessageDescriptor()
{
    delete[] propertyNames;
}

bool HttpReplyMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HttpReplyMessage *>(obj)!=nullptr;
}

const char **HttpReplyMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HttpReplyMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HttpReplyMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int HttpReplyMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_result
        0,    // FIELD_contentType
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *HttpReplyMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "result",
        "contentType",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int HttpReplyMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "result") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "contentType") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *HttpReplyMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_result
        "inet::httptools::HttpContentType",    // FIELD_contentType
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **HttpReplyMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_contentType: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *HttpReplyMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_contentType:
            if (!strcmp(propertyName, "enum")) return "inet::httptools::HttpContentType";
            return nullptr;
        default: return nullptr;
    }
}

int HttpReplyMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HttpReplyMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HttpReplyMessage'", field);
    }
}

const char *HttpReplyMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HttpReplyMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_result: return long2string(pp->getResult());
        case FIELD_contentType: return enum2string(pp->getContentType(), "inet::httptools::HttpContentType");
        default: return "";
    }
}

void HttpReplyMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_result: pp->setResult(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpReplyMessage'", field);
    }
}

omnetpp::cValue HttpReplyMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_result: return pp->getResult();
        case FIELD_contentType: return static_cast<int>(pp->getContentType());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HttpReplyMessage' as cValue -- field index out of range?", field);
    }
}

void HttpReplyMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        case FIELD_result: pp->setResult(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpReplyMessage'", field);
    }
}

const char *HttpReplyMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr HttpReplyMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HttpReplyMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HttpReplyMessage *pp = omnetpp::fromAnyPtr<HttpReplyMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HttpReplyMessage'", field);
    }
}

}  // namespace httptools
}  // namespace inet

namespace omnetpp {

}  // namespace omnetpp


#ifndef PROPERTYDEFINITION_H
#define PROPERTYDEFINITION_H

#include "PropertyKind.h"

#include <functional>
#include <sstream>
#include <string>

using namespace std;


template<class T>
class PropertyDefinition
{
public:
    virtual ~PropertyDefinition() { }

    string propertyName;
    function<string (const T&)> mapping;
    PropertyKind propertyKind;

    virtual string serializeValue(const T& obj) const;
};

// ----------------------------------------------------------------------------


template<class T>
string PropertyDefinition<T>::serializeValue(const T& obj) const
{
    stringstream out;

    if (propertyKind == PropertyKind::String)
    {
        out << "\"" << mapping(obj) << "\"";
    }
    else if (propertyKind == PropertyKind::Value)
    {
        out << mapping(obj);
    }
    else if (propertyKind == PropertyKind::Object)
    {
        out << "tutaj lol";
    }

    return out.str();
}

#endif // PROPERTYDEFINITION_H

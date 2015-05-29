#ifndef PROPERTYDEFINITION_H
#define PROPERTYDEFINITION_H

#include "PropertyDefinitionBase.h"

#include <functional>
#include <sstream>
#include <string>

using namespace std;


template<class T>
class PropertyDefinition : public PropertyDefinitionBase<T>
{
public:
    virtual ~PropertyDefinition() { }

    function<string (const T&)> mapping;

    string serializeValue(const T& obj) const override;
};

// ----------------------------------------------------------------------------


template<class T>
string PropertyDefinition<T>::serializeValue(const T& obj) const
{
    stringstream out;

    if (this->propertyKind == PropertyKind::String)
    {
        out << "\"" << mapping(obj) << "\"";
    }
    else if (this->propertyKind == PropertyKind::Value)
    {
        out << mapping(obj);
    }

    return out.str();
}

#endif // PROPERTYDEFINITION_H

#ifndef OBJECTPROPERTYDEFINITION_H
#define OBJECTPROPERTYDEFINITION_H

#include "PropertyDefinitionBase.h"
#include "Serializer/ISerializer.h"
#include "Serializer/ObjectSerializer.hpp"

#include <functional>
#include <sstream>
#include <string>

using namespace std;


template<class T>
class Mapping;

template<class OBJ_T, class PROPERTY_T>
class ObjectPropertyDefinition : public PropertyDefinitionBase<OBJ_T>
{
public:
    virtual ~ObjectPropertyDefinition() { }

    ISerializer<PROPERTY_T>* serializer;

    Mapping<PROPERTY_T> propertyTypeMapping;
    function<PROPERTY_T (const OBJ_T&)> getValueFunction;

    string serializeValue(const OBJ_T& obj) const override;

    PropertyKind propertyKind() const override;
};

// ----------------------------------------------------------------------------

template<class OBJ_T, class PROPERTY_T>
string ObjectPropertyDefinition<OBJ_T, PROPERTY_T>::serializeValue(const OBJ_T &obj) const
{
    stringstream out;

    PROPERTY_T value = getValueFunction(obj);

    string serializedValue = serializer->serialize(value);

    out << serializedValue;

    return out.str();
}

template<class OBJ_T, class PROPERTY_T>
PropertyKind ObjectPropertyDefinition<OBJ_T, PROPERTY_T>::propertyKind() const
{
    return PropertyKind::Object;
}

#endif // OBJECTPROPERTYDEFINITION_H

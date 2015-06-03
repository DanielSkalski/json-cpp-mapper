#ifndef PROPERTYDEFINITION_H
#define PROPERTYDEFINITION_H

#include "PropertyDefinitionBase.h"

#include <functional>
#include <sstream>
#include <string>

using namespace std;


template<class OBJ_T, class PROPERTY_T>
class PropertyDefinition : public PropertyDefinitionBase<OBJ_T>
{
public:
    virtual ~PropertyDefinition() { }

    PropertyKind _propertyKind;

    ISerializer<PROPERTY_T>* serializer;

    function<PROPERTY_T (const OBJ_T&)> getValueFunction;

    string serializeValue(const OBJ_T& obj) const override;

    PropertyKind propertyKind() const override;
};

// ----------------------------------------------------------------------------

template<class OBJ_T, class PROPERTY_T>
string PropertyDefinition<OBJ_T, PROPERTY_T>::serializeValue(const OBJ_T& obj) const
{
    stringstream out;

    PROPERTY_T value = getValueFunction(obj);

    out << serializer->serialize(value);

    return out.str();
}

template<class OBJ_T, class PROPERTY_T>
PropertyKind PropertyDefinition<OBJ_T, PROPERTY_T>::propertyKind() const
{
    return _propertyKind;
}

#endif // PROPERTYDEFINITION_H

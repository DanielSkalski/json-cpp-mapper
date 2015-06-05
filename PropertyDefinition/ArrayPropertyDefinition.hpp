#ifndef ARRAYPROPERTYDEFINITION_H
#define ARRAYPROPERTYDEFINITION_H

#include "PropertyDefinitionBase.h"
#include "Mapping.hpp"

#include <functional>
#include <sstream>
#include <string>

using namespace std;


template<class OBJ_T, class ELEMENT_T>
class ArrayPropertyDefinition : public PropertyDefinitionBase<OBJ_T>
{
public:
    virtual ~ArrayPropertyDefinition() { }

    ISerializer<OBJ_T>* serializer;

    function<int (const OBJ_T&)> arraySize;
    function<ELEMENT_T (const OBJ_T&, int)> elementAccess;

    string serializeValue(const OBJ_T &obj) const override;

    PropertyKind propertyKind() const override;
};


// ----------------------------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
string ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::serializeValue(const OBJ_T &obj) const
{
    return serializer->serialize(obj);
}

template<class OBJ_T, class ELEMENT_T>
PropertyKind ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::propertyKind() const
{
    return PropertyKind::Array;
}


#endif // ARRAYPROPERTYDEFINITION_H

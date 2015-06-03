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

    ISerializer<ELEMENT_T>* elementSerializer;

    function<int (const OBJ_T&)> arraySize;
    function<ELEMENT_T (const OBJ_T&, int)> elementAccess;

    string serializeValue(const OBJ_T &obj) const override;

    PropertyKind propertyKind() const override;
};


// ----------------------------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
string ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::serializeValue(const OBJ_T &obj) const
{
    stringstream out;

    out << "[" << endl;

    for (int i = 0; i < arraySize(obj); i++)
    {
        ELEMENT_T value = elementAccess(obj, i);

        string serializedValue = elementSerializer->serialize(value);

        out << serializedValue << "," << endl;
    }

    if (arraySize(obj) > 0)
    {
        // remove last "," sign
        out.seekp(-2, out.cur);
    }

    out << "]" << endl;

    return out.str();
}

template<class OBJ_T, class ELEMENT_T>
PropertyKind ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::propertyKind() const
{
    return PropertyKind::Array;
}


#endif // ARRAYPROPERTYDEFINITION_H

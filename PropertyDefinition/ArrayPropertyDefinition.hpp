#ifndef ARRAYPROPERTYDEFINITION_H
#define ARRAYPROPERTYDEFINITION_H

#include "PropertyDefinitionCommon.h"


template<class OBJ_T, class ELEMENT_T>
class ArrayPropertyDefinition : public PropertyDefinitionBase<OBJ_T>
{
    friend class PropertyDefinitionFactory<OBJ_T>;

    explicit ArrayPropertyDefinition(const string& propertyName);

    shared_ptr< ISerializer<OBJ_T> > m_serializer;

    function<int (const OBJ_T&)> m_arraySize;
    function<ELEMENT_T (const OBJ_T&, int)> m_elementAccess;

public:
    virtual ~ArrayPropertyDefinition() { }

    string serializeValue(const OBJ_T &obj) const override;

    PropertyKind propertyKind() const override;
};


// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::ArrayPropertyDefinition(const string& propertyName)
    : PropertyDefinitionBase<OBJ_T>(propertyName)
{
}

// ----- METHODS --------------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
string ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::serializeValue(const OBJ_T &obj) const
{
    return m_serializer->serialize(obj);
}

template<class OBJ_T, class ELEMENT_T>
PropertyKind ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::propertyKind() const
{
    return PropertyKind::Array;
}


#endif // ARRAYPROPERTYDEFINITION_H

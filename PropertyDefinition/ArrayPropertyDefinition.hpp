#ifndef ARRAYPROPERTYDEFINITION_H
#define ARRAYPROPERTYDEFINITION_H

#include "PropertyDefinitionCommon.h"


namespace mapper {

template<class OBJ_T, class ELEMENT_T>
class ArrayPropertyDefinition : public PropertyDefinitionBase<OBJ_T>
{
    friend class PropertyDefinitionFactory<OBJ_T>;
    struct private_ctor { };

    static shared_ptr<ArrayPropertyDefinition<OBJ_T, ELEMENT_T>> make_shared(const string& propertyName)
    {
        return std::make_shared<ArrayPropertyDefinition<OBJ_T, ELEMENT_T>>(private_ctor(), propertyName);
    }

    shared_ptr< ISerializer<OBJ_T> > m_serializer;

    function<int (const OBJ_T&)> m_arraySize;
    function<ELEMENT_T (const OBJ_T&, int)> m_elementAccess;

public:
    ArrayPropertyDefinition(const private_ctor&, const string& propertyName);
    virtual ~ArrayPropertyDefinition() { }

    JsonStream& serializeValue(const OBJ_T &obj, JsonStream& out) const override;

    PropertyKind propertyKind() const override;
};


// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::ArrayPropertyDefinition(const private_ctor &,
                                                                   const string& propertyName)
    : PropertyDefinitionBase<OBJ_T>(propertyName)
{
}

// ----- METHODS --------------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
JsonStream &ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::serializeValue(const OBJ_T &obj, JsonStream &out) const
{
    m_serializer->serialize(obj, out);

    return out;
}

template<class OBJ_T, class ELEMENT_T>
PropertyKind ArrayPropertyDefinition<OBJ_T, ELEMENT_T>::propertyKind() const
{
    return PropertyKind::Array;
}

} // namespace mapper

#endif // ARRAYPROPERTYDEFINITION_H

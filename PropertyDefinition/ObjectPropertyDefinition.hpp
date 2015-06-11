#ifndef OBJECTPROPERTYDEFINITION_H
#define OBJECTPROPERTYDEFINITION_H

#include "PropertyDefinitionCommon.h"

#include "Serializer/ObjectSerializer.hpp"

namespace mapper {

template<class T>
class Mapping;

template<class OBJ_T, class PROPERTY_T>
class ObjectPropertyDefinition : public PropertyDefinitionBase<OBJ_T>
{
    friend class PropertyDefinitionFactory<OBJ_T>;
    struct private_ctor { };

    static shared_ptr<ObjectPropertyDefinition<OBJ_T, PROPERTY_T>> make_shared(const string& propertyName)
    {
        return std::make_shared<ObjectPropertyDefinition<OBJ_T, PROPERTY_T>>(private_ctor(), propertyName);
    }

    shared_ptr< ISerializer<PROPERTY_T> > m_serializer;

    Mapping<PROPERTY_T> m_propertyTypeMapping;
    function<PROPERTY_T (const OBJ_T&)> m_getValueFunction;

public:
    ObjectPropertyDefinition(const private_ctor&, const string& propertyName);
    virtual ~ObjectPropertyDefinition() { }

    string serializeValue(const OBJ_T& obj) const override;

    PropertyKind propertyKind() const override;
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class OBJ_T, class PROPERTY_T>
ObjectPropertyDefinition<OBJ_T, PROPERTY_T>::ObjectPropertyDefinition(const private_ctor&,
                                                                      const string& propertyName)
    : PropertyDefinitionBase<OBJ_T>(propertyName)
{

}

// ----- METHODS --------------------------------------------------------------

template<class OBJ_T, class PROPERTY_T>
string ObjectPropertyDefinition<OBJ_T, PROPERTY_T>::serializeValue(const OBJ_T &obj) const
{
    stringstream out;

    PROPERTY_T value = m_getValueFunction(obj);

    string serializedValue = m_serializer->serialize(value);

    out << serializedValue;

    return out.str();
}

template<class OBJ_T, class PROPERTY_T>
PropertyKind ObjectPropertyDefinition<OBJ_T, PROPERTY_T>::propertyKind() const
{
    return PropertyKind::Object;
}

} // namespace mapper

#endif // OBJECTPROPERTYDEFINITION_H

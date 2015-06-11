#ifndef PROPERTYDEFINITION_H
#define PROPERTYDEFINITION_H

#include "PropertyDefinitionCommon.h"

namespace mapper {

template<class OBJ_T, class PROPERTY_T>
class PropertyDefinition : public PropertyDefinitionBase<OBJ_T>
{
    friend class PropertyDefinitionFactory<OBJ_T>;
    struct private_ctor { };

    static shared_ptr<PropertyDefinition<OBJ_T, PROPERTY_T>> make_shared(const string& propertyName,
                                                                         PropertyKind propertyKind = PropertyKind::String)
    {
        return std::make_shared<PropertyDefinition<OBJ_T, PROPERTY_T>>(private_ctor(),
                                                                       propertyName,
                                                                       propertyKind);
    }

    PropertyKind m_propertyKind;
    shared_ptr< ISerializer<PROPERTY_T> > m_serializer;
    function<PROPERTY_T (const OBJ_T&)> m_getValueFunction;

public:
    PropertyDefinition(const private_ctor&, const string& propertyName, PropertyKind propertyKind = PropertyKind::String);
    virtual ~PropertyDefinition() { }

    string serializeValue(const OBJ_T& obj) const override;

    PropertyKind propertyKind() const override;
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class OBJ_T, class PROPERTY_T>
PropertyDefinition<OBJ_T, PROPERTY_T>::PropertyDefinition(const private_ctor&,
                                                          const string& propertyName,
                                                          PropertyKind propertyKind)
    : PropertyDefinitionBase<OBJ_T>(propertyName), m_propertyKind(propertyKind)
{
}

// ----- METHODS --------------------------------------------------------------

template<class OBJ_T, class PROPERTY_T>
string PropertyDefinition<OBJ_T, PROPERTY_T>::serializeValue(const OBJ_T& obj) const
{
    stringstream out;

    PROPERTY_T value = m_getValueFunction(obj);

    out << m_serializer->serialize(value);

    return out.str();
}

template<class OBJ_T, class PROPERTY_T>
PropertyKind PropertyDefinition<OBJ_T, PROPERTY_T>::propertyKind() const
{
    return m_propertyKind;
}

} // namespace mapper

#endif // PROPERTYDEFINITION_H

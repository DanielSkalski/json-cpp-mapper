#ifndef OBJECTSERIALIZER_H
#define OBJECTSERIALIZER_H

#include "SerializerCommon.h"
#include "Mapping.hpp"

namespace mapper {


template<class T>
class Mapping;


template<class T>
class ObjectSerializer : public ISerializer<T>
{
    friend class SerializerFactory;
    struct private_ctor { };

    static shared_ptr<ObjectSerializer<T>> make_shared(const Mapping<T>& mapping)
    {
        return std::make_shared<ObjectSerializer<T>>(private_ctor(), mapping);
    }

    Mapping<T> m_mapping;

public:
    ObjectSerializer(const private_ctor&, const Mapping<T>& mapping);
    virtual ~ObjectSerializer() { }

    JsonStream& serialize(const T& value, JsonStream& out) const override;
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
ObjectSerializer<T>::ObjectSerializer(const private_ctor&, const Mapping<T>& mapping)
    : m_mapping(mapping)
{
}

// ----- METHODS --------------------------------------------------------------

template<class T>
JsonStream &ObjectSerializer<T>::serialize(const T &value, JsonStream &out) const
{
    out.beginObject();

    int propertyIndex = 0;
    int propertiesCount = m_mapping.properties().size();
    for (auto prop : m_mapping.properties())
    {
        out.beginProperty(prop->propertyName());

        prop->serializeValue(value, out);

        bool isLastProperty = (propertyIndex == propertiesCount - 1);
        out.endProperty(isLastProperty);

        propertyIndex++;
    }

    out.endObject();

    return out;
}

} // namespace mapper

#endif // OBJECTSERIALIZER_H

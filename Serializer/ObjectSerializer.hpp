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

    string serialize(const T& value) const override;
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
string ObjectSerializer<T>::serialize(const T &value) const
{
    stringstream out;

    out << "{" << endl;

    for (auto prop : m_mapping.properties())
    {
        string propValue = prop->serializeValue(value);

        out << "\"" << prop->propertyName() << "\" : " << propValue << "," << endl;
    }

    // Remove last ',' sign.
    if (m_mapping.properties().size() > 0)
    {
        out.seekp(-2, out.cur);
    }

    out << endl << "}" << endl;

    return out.str();
}

} // namespace mapper

#endif // OBJECTSERIALIZER_H

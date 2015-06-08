#ifndef OBJECTSERIALIZER_H
#define OBJECTSERIALIZER_H

#include "SerializerCommon.h"
#include "Mapping.hpp"


template<class T>
class Mapping;

template<class T>
class ObjectSerializer : public ISerializer<T>
{
    friend class SerializerFactory;

    explicit ObjectSerializer(const Mapping<T>& mapping);

    Mapping<T> m_mapping;

public:

    virtual ~ObjectSerializer() { }

    string serialize(const T& value) const override;
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
ObjectSerializer<T>::ObjectSerializer(const Mapping<T>& mapping)
    : m_mapping(mapping)
{
}

// ----- METHODS --------------------------------------------------------------

template<class T>
string ObjectSerializer<T>::serialize(const T &value) const
{
    stringstream out;

    out << "{" << endl;

    for (PropertyDefinitionBase<T>* prop : m_mapping.properties())
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

#endif // OBJECTSERIALIZER_H

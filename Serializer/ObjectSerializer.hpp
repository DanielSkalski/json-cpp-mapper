#ifndef OBJECTSERIALIZER_H
#define OBJECTSERIALIZER_H

#include "ISerializer.h"
#include "Mapping.hpp"

template<class T>
class Mapping;

template<class T>
class ObjectSerializer : public ISerializer<T>
{
    Mapping<T> mapping;

public:
    explicit ObjectSerializer(const Mapping<T>& mapping)
    {
        this->mapping = mapping;
    }

    virtual ~ObjectSerializer() { }

    string serialize(const T& value) const override;
};

// ----------------------------------------------------------------------------

template<class T>
string ObjectSerializer<T>::serialize(const T &value) const
{
    stringstream out;

    out << "{" << endl;

    for (PropertyDefinitionBase<T>* prop : mapping.m_properties)
    {
        string propValue = prop->serializeValue(value);

        out << "\"" << prop->propertyName << "\" : " << propValue << "," << endl;
    }

    // Remove last ',' sign.
    if (mapping.m_properties.size() > 0)
    {
        out.seekp(-2, out.cur);
    }

    out << endl << "}" << endl;

    return out.str();
}

#endif // OBJECTSERIALIZER_H

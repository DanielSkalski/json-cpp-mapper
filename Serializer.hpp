#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "PropertyDefinition/PropertyDefinition.hpp"
#include "PropertyDefinition/PropertyDefinitionFactory.hpp"

#include <functional>
#include <sstream>
#include <string>
#include <list>

using namespace std;


template<class T>
class Serializer
{
    list< PropertyDefinitionBase<T>* > m_properties;
    PropertyDefinitionFactory<T> m_propertyDefinitionFactory;

public:

    Serializer();
    virtual ~Serializer();

    void map(const string&               propertyName,
             function<string (const T&)> valueFunction,
             PropertyKind                propertyKind = PropertyKind::String);

    template<class IT>
    void map(const string &              propertyName,
             function<IT (const T &)>    valueFunction,
             const Serializer<IT>&       objectSerializer);

    template<class IT>
    void mapArrayOf(const string &                propertyName,
                    function<int (const T &)>     collectionSizeFunction,
                    function<IT (const T &, int)> elementAccessFunction,
                    const Serializer<IT>&         elementSerializer);

    string serialize(const T& obj) const;
};

// ----------------------------------------------------------------------------


template<class T>
Serializer<T>::Serializer()
{

}

template<class T>
Serializer<T>::~Serializer()
{
    for (PropertyDefinitionBase<T>* prop : m_properties)
    {
        delete prop;
    }
}

template<class T>
void Serializer<T>::map(const string& propertyName,
                        function<string (const T&)> valueFunction,
                        PropertyKind propertyKind)
{
    auto propertyDefinition = m_propertyDefinitionFactory
                                .createPropertyDefinition(propertyName, valueFunction, propertyKind);

    m_properties.push_back(propertyDefinition);
}

template<class T>
template<class IT>
void Serializer<T>::map(const string &propertyName,
                        function<IT (const T &)> valueFunction,
                        const Serializer<IT>& objectSerializer)
{
    auto propertyDefinition = m_propertyDefinitionFactory
                                .createPropertyDefinition(propertyName, valueFunction, objectSerializer);

    m_properties.push_back(propertyDefinition);
}

template<class T>
template<class IT>
void Serializer<T>::mapArrayOf(const string &                propertyName,
                               function<int (const T &)>     collectionSizeFunction,
                               function<IT (const T &, int)> elementAccessFunction,
                               const Serializer<IT>&         elementSerializer)
{
    auto arrayPropertyDefinition = m_propertyDefinitionFactory
                                .createArrayPropertyDefinition(propertyName,
                                                               collectionSizeFunction,
                                                               elementAccessFunction,
                                                               elementSerializer);

    m_properties.push_back(arrayPropertyDefinition);
}


template<class T>
string Serializer<T>::serialize(const T& obj) const
{
    stringstream out;

    out << "{" << endl;

    for (PropertyDefinitionBase<T>* prop : m_properties)
    {
        string value = prop->serializeValue(obj);

        out << "\"" << prop->propertyName << "\" : " << value << "," << endl;
    }

    // Remove last ',' sign.
    if (m_properties.size() > 0)
    {
        out.seekp(-2, out.cur);
    }

    out << endl << "}" << endl;

    return out.str();
}

#endif // SERIALIZER_H

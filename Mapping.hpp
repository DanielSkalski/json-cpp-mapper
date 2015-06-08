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
class Mapping
{
    PropertyDefinitionFactory<T> m_propertyDefinitionFactory;
    list< PropertyDefinitionBase<T>* > m_properties;

public:
    Mapping();
    virtual ~Mapping();

    list< PropertyDefinitionBase<T>* > properties() const;

    void map(const string&               propertyName,
             function<string (const T&)> valueFunction);

    template<typename PROP_T>
    void map(const string&               propertyName,
             function<PROP_T (const T&)> valueFunction);

    template<class PROP_T>
    void map(const string &               propertyName,
             function<PROP_T (const T &)> valueFunction,
             const Mapping<PROP_T>&       objectSerializer);

    template<class ELEM_T>
    void mapArrayOf(const string &                    propertyName,
                    function<int (const T &)>         collectionSizeFunction,
                    function<ELEM_T (const T &, int)> elementAccessFunction,
                    const Mapping<ELEM_T>&            elementTypeMapping);

    void mapArrayOfStrings
                   (const string &                    propertyName,
                    function<int (const T &)>         collectionSizeFunction,
                    function<string (const T &, int)> elementAccessFunction);

    template<typename ELEM_T>
    void mapArrayOfNumbers
                   (const string &                    propertyName,
                    function<int (const T &)>         collectionSizeFunction,
                    function<ELEM_T (const T &, int)> elementAccessFunction);

    void mapArrayOfStringArrays
                   (const string &                    propertyName,
                    function<int (const T &)>         collectionSizeFunction,
                    function<string* (const T &, int)> elementAccessFunction,
                    function<int (const string*)>    innerCollectionSizeFunction,
                    function<string (const string*, int)> innerArrayElementAccessFunction);
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
Mapping<T>::Mapping()
{
}

template<class T>
Mapping<T>::~Mapping()
{
    for (PropertyDefinitionBase<T>* prop : m_properties)
    {
        delete prop;
    }
}

// ----- METHODS --------------------------------------------------------------

template<class T>
list< PropertyDefinitionBase<T>* > Mapping<T>::properties() const
{
    return m_properties;
}

template<class T>
void Mapping<T>::map(const string& propertyName,
                        function<string (const T&)> valueFunction)
{
    auto propertyDefinition = m_propertyDefinitionFactory
                                .createPropertyDefinition(propertyName, valueFunction);

    m_properties.push_back(propertyDefinition);
}

template<class T>
template<typename PROP_T>
void Mapping<T>::map(const string& propertyName,
                     function<PROP_T (const T&)> valueFunction)
{
    auto propertyDefinition = m_propertyDefinitionFactory
                                .createValuePropertyDefinition(propertyName, valueFunction);

    m_properties.push_back(propertyDefinition);
}

template<class T>
template<class PROP_T>
void Mapping<T>::map(const string &propertyName,
                     function<PROP_T (const T &)> valueFunction,
                     const Mapping<PROP_T>& propertyTypeMapping)
{
    auto propertyDefinition = m_propertyDefinitionFactory
                                .createPropertyDefinition(propertyName, valueFunction, propertyTypeMapping);

    m_properties.push_back(propertyDefinition);
}

template<class T>
template<class ELEMENT_T>
void Mapping<T>::mapArrayOf(const string &                       propertyName,
                            function<int (const T &)>            collectionSizeFunction,
                            function<ELEMENT_T (const T &, int)> elementAccessFunction,
                            const Mapping<ELEMENT_T>&            elementTypeMapping)
{
    auto arrayPropertyDefinition = m_propertyDefinitionFactory
                                .createArrayPropertyDefinition(propertyName,
                                                               collectionSizeFunction,
                                                               elementAccessFunction,
                                                               elementTypeMapping);

    m_properties.push_back(arrayPropertyDefinition);
}


template<class T>
void Mapping<T>::mapArrayOfStrings
               (const string &                propertyName,
                function<int (const T &)>     collectionSizeFunction,
                function<string (const T &, int)> elementAccessFunction)
{
    auto arrayPropertyDefinition = m_propertyDefinitionFactory
                                .createArrayPropertyDefinition(propertyName,
                                                               collectionSizeFunction,
                                                               elementAccessFunction);

    m_properties.push_back(arrayPropertyDefinition);
}

template<class T>
template<class ELEM_T>
void Mapping<T>::mapArrayOfNumbers
               (const string &                    propertyName,
                function<int (const T &)>         collectionSizeFunction,
                function<ELEM_T (const T &, int)> elementAccessFunction)
{
    auto arrayPropertyDefinition = m_propertyDefinitionFactory
                                .createArrayPropertyDefinition(propertyName,
                                                               collectionSizeFunction,
                                                               elementAccessFunction);

    m_properties.push_back(arrayPropertyDefinition);
}

template<class T>
void Mapping<T>::mapArrayOfStringArrays
               (const string &                    propertyName,
                function<int (const T &)>         collectionSizeFunction,
                function<string* (const T &, int)> elementAccessFunction,
                function<int (const string*)>    innerCollectionSizeFunction,
                function<string (const string*, int)> innerArrayElementAccessFunction)
{
    auto arrayPropertyDefinition = m_propertyDefinitionFactory
                                .createArrayPropertyDefinition(propertyName,
                                                               collectionSizeFunction,
                                                               elementAccessFunction,
                                                               innerCollectionSizeFunction,
                                                               innerArrayElementAccessFunction);

    m_properties.push_back(arrayPropertyDefinition);
}


#endif // SERIALIZER_H

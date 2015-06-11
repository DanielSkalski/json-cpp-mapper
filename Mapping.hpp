#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "PropertyDefinition/PropertyDefinition.hpp"
#include "PropertyDefinition/PropertyDefinitionFactory.hpp"
#include "MappingBuild/MappingBuilder.hpp"
#include "MappingBuild/MappingPropertyKindChooser.hpp"

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <list>

using namespace std;

namespace mapper {

template<class T>
class Mapping
{
    friend class MappingBuilder<T>;

    PropertyDefinitionFactory<T> m_propertyDefinitionFactory;
    list<shared_ptr<PropertyDefinitionBase<T>>> m_properties;

public:
    Mapping();
    virtual ~Mapping();

    const list< shared_ptr< PropertyDefinitionBase<T> > >& properties() const;

    unique_ptr<MappingPropertyKindChooser<T>> map(const string& propertyName);

    void map(const string&               propertyName,
             function<string (const T&)> valueFunction);

    void map(const string&               propertyName,
             function<bool (const T&)> valueFunction);

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
}

// ----- METHODS --------------------------------------------------------------

template<class T>
const list<shared_ptr<PropertyDefinitionBase<T> > >& Mapping<T>::properties() const
{
    return m_properties;
}

template<class T>
unique_ptr<MappingPropertyKindChooser<T>> Mapping<T>::map(const string &propertyName)
{
    auto mb = unique_ptr<MappingBuilder<T>>(new MappingBuilder<T>(this));

    return mb->map(propertyName);
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
void Mapping<T>::map(const string&             propertyName,
                     function<bool (const T&)> valueFunction)
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
                                .createPropertyDefinition(propertyName, valueFunction);

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

} // namespace mapper

#endif // SERIALIZER_H

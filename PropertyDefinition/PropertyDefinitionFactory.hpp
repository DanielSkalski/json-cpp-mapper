#ifndef PROPERTYDEFINITIONFACTORY_H
#define PROPERTYDEFINITIONFACTORY_H

#include "PropertyKind.h"
#include "PropertyDefinitionBase.h"
#include "PropertyDefinition.hpp"
#include "ObjectPropertyDefinition.hpp"
#include "ArrayPropertyDefinition.hpp"

#include "Serializer/StringSerializer.hpp"
#include "Serializer/ValueSerializer.hpp"
#include "Serializer/ObjectSerializer.hpp"

#include <functional>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class PropertyDefinitionFactory
{
public:
    PropertyDefinitionBase<T>* createPropertyDefinition
                                                    (const string &propertyName,
                                                     function<string (const T&)> valueFunction) const;

    template<typename PROP_T>
    PropertyDefinitionBase<T>* createValuePropertyDefinition
                                                    (const string &propertyName,
                                                     function<PROP_T (const T&)> valueFunction) const;

    template<class PROP_T>
    PropertyDefinitionBase<T>* createPropertyDefinition
                                                    (const string &propertyName,
                                                     function<PROP_T (const T&)> valueFunction,
                                                     const Mapping<PROP_T> &propertyTypeMapping) const;

    template<class ELEM_T>
    PropertyDefinitionBase<T>* createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<ELEM_T (const T&, int)> elementAccessFunction,
                                                     const Mapping<ELEM_T>& elementTypeMapping) const;

    template<typename ELEM_T>
    PropertyDefinitionBase<T>* createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<ELEM_T (const T&, int)> elementAccessFunction) const;

    PropertyDefinitionBase<T>* createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<string (const T&, int)> elementAccessFunction) const;
};

// ----------------------------------------------------------------------------

template<class T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createPropertyDefinition
                                                        (const string &propertyName,
                                                         function<string (const T&)> valueFunction) const
{
    auto propertyDefinition = new PropertyDefinition<T, string>;
    propertyDefinition->propertyName     = propertyName;
    propertyDefinition->getValueFunction = valueFunction;
    propertyDefinition->serializer       = new StringSerializer();
    propertyDefinition->_propertyKind    = PropertyKind::String;

    return propertyDefinition;
}

template<class T>
template<typename PROP_T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createValuePropertyDefinition
                                                (const string &propertyName,
                                                 function<PROP_T (const T&)> valueFunction) const
{
    auto propertyDefinition = new PropertyDefinition<T, PROP_T>;
    propertyDefinition->propertyName     = propertyName;
    propertyDefinition->getValueFunction = valueFunction;
    propertyDefinition->serializer       = new ValueSerializer<PROP_T>();
    propertyDefinition->_propertyKind    = PropertyKind::Value;

    return propertyDefinition;
}

template<class T>
template<class PROP_T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createPropertyDefinition
                                                      (const string &propertyName,
                                                       function<PROP_T (const T &)> valueFunction,
                                                       const Mapping<PROP_T> &propertyTypeMapping) const
{
    auto propertyDefinition = new ObjectPropertyDefinition<T, PROP_T>;
    propertyDefinition->propertyName        = propertyName;
    propertyDefinition->getValueFunction    = valueFunction;
    propertyDefinition->propertyTypeMapping = propertyTypeMapping;
    propertyDefinition->serializer          = new ObjectSerializer<PROP_T>(propertyTypeMapping);

    return propertyDefinition;
}


template<class T>
template<class ELEM_T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<ELEM_T (const T&, int)> elementAccessFunction,
                                                     const Mapping<ELEM_T>& elementTypeMapping) const
{
    auto propertyDefinition = new ArrayPropertyDefinition<T, ELEM_T>;
    propertyDefinition->propertyName      = propertyName;
    propertyDefinition->arraySize         = collectionSizeFunction;
    propertyDefinition->elementAccess     = elementAccessFunction;
    propertyDefinition->elementSerializer = new ObjectSerializer<ELEM_T>(elementTypeMapping);

    return propertyDefinition;
}


template<class T>
template<class ELEM_T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<ELEM_T (const T&, int)> elementAccessFunction) const
{
    auto propertyDefinition = new ArrayPropertyDefinition<T, ELEM_T>;
    propertyDefinition->propertyName      = propertyName;
    propertyDefinition->arraySize         = collectionSizeFunction;
    propertyDefinition->elementAccess     = elementAccessFunction;
    propertyDefinition->elementSerializer = new ValueSerializer<ELEM_T>();

    return propertyDefinition;
}

template<class T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<string (const T&, int)> elementAccessFunction) const
{
    auto propertyDefinition = new ArrayPropertyDefinition<T, string>;
    propertyDefinition->propertyName      = propertyName;
    propertyDefinition->arraySize         = collectionSizeFunction;
    propertyDefinition->elementAccess     = elementAccessFunction;
    propertyDefinition->elementSerializer = new StringSerializer();

    return propertyDefinition;
}

#endif // PROPERTYDEFINITIONFACTORY_H

#ifndef PROPERTYDEFINITIONFACTORY_H
#define PROPERTYDEFINITIONFACTORY_H

#include "PropertyKind.h"
#include "PropertyDefinitionBase.h"
#include "PropertyDefinition.hpp"
#include "ObjectPropertyDefinition.hpp"
#include "ArrayPropertyDefinition.hpp"

#include "Serializer/StringSerializer.hpp"
#include "Serializer/NumberSerializer.hpp"
#include "Serializer/ObjectSerializer.hpp"
#include "Serializer/ArraySerializer.hpp"

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

    PropertyDefinitionBase<T>* createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<string* (const T&, int)> elementAccessFunction,
                                                     function<int (const string*)> innerCollectionSizeFunction,
                                                     function<string (const string*, int)> innerElementAccessFunction) const;
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
    propertyDefinition->serializer       = new NumberSerializer<PROP_T>();
    propertyDefinition->_propertyKind    = PropertyKind::Number;

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
    propertyDefinition->propertyName   = propertyName;
    propertyDefinition->arraySize      = collectionSizeFunction;
    propertyDefinition->elementAccess  = elementAccessFunction;

    auto arraySerializer = new ArraySerializer<T, ELEM_T>;
    arraySerializer->arraySize         = collectionSizeFunction;
    arraySerializer->elementAccess     = elementAccessFunction;
    arraySerializer->elementSerializer = new ObjectSerializer<ELEM_T>(elementTypeMapping);

    propertyDefinition->serializer     = arraySerializer;

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
    propertyDefinition->propertyName   = propertyName;
    propertyDefinition->arraySize      = collectionSizeFunction;
    propertyDefinition->elementAccess  = elementAccessFunction;

    auto arraySerializer = new ArraySerializer<T, ELEM_T>;
    arraySerializer->arraySize         = collectionSizeFunction;
    arraySerializer->elementAccess     = elementAccessFunction;
    arraySerializer->elementSerializer = new NumberSerializer<ELEM_T>();

    propertyDefinition->serializer     = arraySerializer;

    return propertyDefinition;
}

template<class T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<string (const T&, int)> elementAccessFunction) const
{
    auto propertyDefinition = new ArrayPropertyDefinition<T, string>;
    propertyDefinition->propertyName   = propertyName;
    propertyDefinition->arraySize      = collectionSizeFunction;
    propertyDefinition->elementAccess  = elementAccessFunction;

    auto arraySerializer = new ArraySerializer<T, string>;
    arraySerializer->arraySize         = collectionSizeFunction;
    arraySerializer->elementAccess     = elementAccessFunction;
    arraySerializer->elementSerializer = new StringSerializer();

    propertyDefinition->serializer     = arraySerializer;

    return propertyDefinition;
}


template<class T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createArrayPropertyDefinition
                                                (const string& propertyName,
                                                 function<int (const T&)> collectionSizeFunction,
                                                 function<string* (const T&, int)> elementAccessFunction,
                                                 function<int (const string*)> innerCollectionSizeFunction,
                                                 function<string (const string*, int)> innerElementAccessFunction) const
{
    auto propertyDefinition = new ArrayPropertyDefinition<T, string*>;
    propertyDefinition->propertyName   = propertyName;
    propertyDefinition->arraySize      = collectionSizeFunction;
    propertyDefinition->elementAccess  = elementAccessFunction;

    auto innerArraySerializer = new ArraySerializer<string*, string>;
    innerArraySerializer->arraySize         = innerCollectionSizeFunction;
    innerArraySerializer->elementAccess     = innerElementAccessFunction;
    innerArraySerializer->elementSerializer = new StringSerializer();

    auto arraySerializer = new ArraySerializer<T, string*>;
    arraySerializer->arraySize         = collectionSizeFunction;
    arraySerializer->elementAccess     = elementAccessFunction;
    arraySerializer->elementSerializer = innerArraySerializer;

    propertyDefinition->serializer     = arraySerializer;

    return propertyDefinition;
}

#endif // PROPERTYDEFINITIONFACTORY_H

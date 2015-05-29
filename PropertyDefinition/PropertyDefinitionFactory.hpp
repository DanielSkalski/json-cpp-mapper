#ifndef PROPERTYDEFINITIONFACTORY_H
#define PROPERTYDEFINITIONFACTORY_H

#include "PropertyKind.h"
#include "PropertyDefinitionBase.h"
#include "PropertyDefinition.hpp"
#include "ObjectPropertyDefinition.hpp"
#include "ArrayPropertyDefinition.hpp"

#include <functional>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class PropertyDefinitionFactory
{
public:
    PropertyDefinitionBase<T>* createPropertyDefinition(string propertyName,
                                                   function<string (const T&)> valueFunction,
                                                   PropertyKind propertyKind = PropertyKind::String) const;

    template<class IT>
    PropertyDefinitionBase<T>* createPropertyDefinition(string propertyName,
                                                   function<IT (const T&)> valueFunction,
                                                   const Serializer<IT>& objectSerializer) const;

    template<class IT>
    PropertyDefinitionBase<T>* createArrayPropertyDefinition(const string& propertyName,
                                                         function<int (const T&)> collectionSizeFunction,
                                                         function<IT (const T&, int)> elementAccessFunction,
                                                         const Serializer<IT>& elementSerializer) const;
};

// ----------------------------------------------------------------------------

template<class T>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createPropertyDefinition(string propertyName,
                                                       function<string (const T&)> valueFunction,
                                                       PropertyKind propertyKind) const
{
    auto propertyDefinition = new PropertyDefinition<T>;
    propertyDefinition->propertyName = propertyName;
    propertyDefinition->mapping      = valueFunction;
    propertyDefinition->propertyKind = propertyKind;

    return propertyDefinition;
}

template<class T>
template<class IT>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createPropertyDefinition(string propertyName,
                                                       function<IT (const T&)> valueFunction,
                                                       const Serializer<IT>& objectSerializer) const
{
    auto propertyDefinition = new ObjectPropertyDefinition<T, IT>;
    propertyDefinition->propertyName  = propertyName;
    propertyDefinition->mappingObject = valueFunction;
    propertyDefinition->serializer    = objectSerializer;
    propertyDefinition->propertyKind  = PropertyKind::Object;

    return propertyDefinition;
}


template<class T>
template<class IT>
PropertyDefinitionBase<T>* PropertyDefinitionFactory<T>::createArrayPropertyDefinition(
                                                        const string& propertyName,
                                                        function<int (const T&)> collectionSizeFunction,
                                                        function<IT (const T&, int)> elementAccessFunction,
                                                        const Serializer<IT>& elementSerializer) const
{
    auto propertyDefinition = new ArrayPropertyDefinition<T, IT>;
    propertyDefinition->propertyName      = propertyName;
    propertyDefinition->arraySize         = collectionSizeFunction;
    propertyDefinition->elementAccess     = elementAccessFunction;
    propertyDefinition->elementSerializer = elementSerializer;
    propertyDefinition->propertyKind      = PropertyKind::Array;

    return propertyDefinition;
}

#endif // PROPERTYDEFINITIONFACTORY_H

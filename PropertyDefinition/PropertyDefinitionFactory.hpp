#ifndef PROPERTYDEFINITIONFACTORY_H
#define PROPERTYDEFINITIONFACTORY_H

#include "PropertyKind.h"
#include "PropertyDefinition.hpp"
#include "ObjectPropertyDefinition.hpp"

#include <functional>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class PropertyDefinitionFactory
{
public:
    PropertyDefinition<T>* createPropertyDefinition(string propertyName,
                                                   function<string (const T&)> valueFunction,
                                                   PropertyKind propertyKind = PropertyKind::String) const;

    template<class IT>
    PropertyDefinition<T>* createPropertyDefinition(string propertyName,
                                                   function<IT (const T&)> valueFunction,
                                                   const Serializer<IT>& objectSerializer) const;
};

// ----------------------------------------------------------------------------

template<class T>
PropertyDefinition<T>* PropertyDefinitionFactory<T>::createPropertyDefinition(string propertyName,
                                                       function<string (const T&)> valueFunction,
                                                       PropertyKind propertyKind) const
{
    auto propertyDefinition = new PropertyDefinition<T>;
    propertyDefinition->propertyName = propertyName;
    propertyDefinition->mapping = valueFunction;
    propertyDefinition->propertyKind = propertyKind;

    return propertyDefinition;
}

template<class T>
template<class IT>
PropertyDefinition<T>* PropertyDefinitionFactory<T>::createPropertyDefinition(string propertyName,
                                                       function<IT (const T&)> valueFunction,
                                                       const Serializer<IT>& objectSerializer) const
{
    auto propertyDefinition = new ObjectPropertyDefinition<T, IT>;
    propertyDefinition->propertyName = propertyName;
    propertyDefinition->mappingObject = valueFunction;
    propertyDefinition->propertyKind = PropertyKind::Object;
    propertyDefinition->serializer = objectSerializer;

    return propertyDefinition;
}

#endif // PROPERTYDEFINITIONFACTORY_H

#ifndef PROPERTYDEFINITIONFACTORY_H
#define PROPERTYDEFINITIONFACTORY_H

#include "PropertyKind.h"
#include "PropertyDefinitionBase.h"
#include "PropertyDefinition.hpp"
#include "ObjectPropertyDefinition.hpp"
#include "ArrayPropertyDefinition.hpp"

#include "Serializer/SerializerFactory.hpp"

#include <functional>
#include <string>

using namespace std;

template<class T>
class PropertyDefinitionFactory
{
    SerializerFactory m_serializerFactory;

public:
    shared_ptr< PropertyDefinitionBase<T> > createPropertyDefinition
                                                    (const string &propertyName,
                                                     function<string (const T&)> valueFunction) const;

    template<typename PROP_T>
    shared_ptr< PropertyDefinitionBase<T> > createValuePropertyDefinition
                                                    (const string &propertyName,
                                                     function<PROP_T (const T&)> valueFunction) const;

    template<class PROP_T>
    shared_ptr< PropertyDefinitionBase<T> > createPropertyDefinition
                                                    (const string &propertyName,
                                                     function<PROP_T (const T&)> valueFunction,
                                                     const Mapping<PROP_T> &propertyTypeMapping) const;

    template<class ELEM_T>
    shared_ptr< PropertyDefinitionBase<T> > createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<ELEM_T (const T&, int)> elementAccessFunction,
                                                     const Mapping<ELEM_T>& elementTypeMapping) const;

    template<typename ELEM_T>
    shared_ptr< PropertyDefinitionBase<T> > createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<ELEM_T (const T&, int)> elementAccessFunction) const;

    shared_ptr< PropertyDefinitionBase<T> > createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<string (const T&, int)> elementAccessFunction) const;

    shared_ptr< PropertyDefinitionBase<T> > createArrayPropertyDefinition
                                                    (const string& propertyName,
                                                     function<int (const T&)> collectionSizeFunction,
                                                     function<string* (const T&, int)> elementAccessFunction,
                                                     function<int (const string*)> innerCollectionSizeFunction,
                                                     function<string (const string*, int)> innerElementAccessFunction) const;
};

// ----------------------------------------------------------------------------

template<class T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createPropertyDefinition(const string &propertyName,
                                                       function<string (const T&)> valueFunction) const
{
    auto propertyDefinition = new PropertyDefinition<T, string>(propertyName, PropertyKind::String);
    propertyDefinition->m_getValueFunction = valueFunction;
    propertyDefinition->m_serializer       = m_serializerFactory.getStringSerializer();

    return shared_ptr< PropertyDefinitionBase<T> >(propertyDefinition);
}

template<class T>
template<typename PROP_T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createValuePropertyDefinition(const string &propertyName,
                                                            function<PROP_T (const T&)> valueFunction) const
{
    auto propertyDefinition = new PropertyDefinition<T, PROP_T>(propertyName, PropertyKind::Number);
    propertyDefinition->m_getValueFunction = valueFunction;
    propertyDefinition->m_serializer       = m_serializerFactory.getNumberSerializer<PROP_T>();

    return shared_ptr< PropertyDefinitionBase<T> >(propertyDefinition);
}

template<class T>
template<class PROP_T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createPropertyDefinition(const string &propertyName,
                                                       function<PROP_T (const T &)> valueFunction,
                                                       const Mapping<PROP_T> &propertyTypeMapping) const
{
    auto propertyDefinition = new ObjectPropertyDefinition<T, PROP_T>(propertyName);
    propertyDefinition->m_getValueFunction    = valueFunction;
    propertyDefinition->m_propertyTypeMapping = propertyTypeMapping;
    propertyDefinition->m_serializer          = m_serializerFactory.getObjectSerializer(propertyTypeMapping);

    return shared_ptr< PropertyDefinitionBase<T> >(propertyDefinition);
}


template<class T>
template<class ELEM_T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createArrayPropertyDefinition(const string& propertyName,
                                                            function<int (const T&)> collectionSizeFunction,
                                                            function<ELEM_T (const T&, int)> elementAccessFunction,
                                                            const Mapping<ELEM_T>& elementTypeMapping) const
{
    auto elementSerializer = m_serializerFactory.getObjectSerializer(elementTypeMapping);

    auto propertyDefinition = new ArrayPropertyDefinition<T, ELEM_T>(propertyName);
    propertyDefinition->m_arraySize     = collectionSizeFunction;
    propertyDefinition->m_elementAccess = elementAccessFunction;
    propertyDefinition->m_serializer    = m_serializerFactory.getArraySerializer<T, ELEM_T>(elementSerializer,
                                                                                 collectionSizeFunction,
                                                                                 elementAccessFunction);

    return shared_ptr< PropertyDefinitionBase<T> >(propertyDefinition);
}


template<class T>
template<class ELEM_T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createArrayPropertyDefinition(const string& propertyName,
                                                            function<int (const T&)> collectionSizeFunction,
                                                            function<ELEM_T (const T&, int)> elementAccessFunction) const
{
    auto elementSerializer = m_serializerFactory.getNumberSerializer<ELEM_T>();

    auto propertyDefinition = new ArrayPropertyDefinition<T, ELEM_T>(propertyName);
    propertyDefinition->m_arraySize      = collectionSizeFunction;
    propertyDefinition->m_elementAccess  = elementAccessFunction;
    propertyDefinition->m_serializer     = m_serializerFactory.getArraySerializer<T, ELEM_T>(
                                                                        elementSerializer,
                                                                        collectionSizeFunction,
                                                                        elementAccessFunction);

    return shared_ptr< PropertyDefinitionBase<T> >(propertyDefinition);
}

template<class T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createArrayPropertyDefinition (const string& propertyName,
                                                             function<int (const T&)> collectionSizeFunction,
                                                             function<string (const T&, int)> elementAccessFunction) const
{
    auto elementSerializer = m_serializerFactory.getStringSerializer();

    auto propertyDefinition = new ArrayPropertyDefinition<T, string>(propertyName);
    propertyDefinition->m_arraySize      = collectionSizeFunction;
    propertyDefinition->m_elementAccess  = elementAccessFunction;
    propertyDefinition->m_serializer     = m_serializerFactory.getArraySerializer<T, string>(
                                                                            elementSerializer,
                                                                            collectionSizeFunction,
                                                                            elementAccessFunction);

    return shared_ptr< PropertyDefinitionBase<T> >(propertyDefinition);
}


template<class T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createArrayPropertyDefinition(const string& propertyName,
                                                            function<int (const T&)> collectionSizeFunction,
                                                            function<string* (const T&, int)> elementAccessFunction,
                                                            function<int (const string*)> innerCollectionSizeFunction,
                                                            function<string (const string*, int)> innerElementAccessFunction) const
{
    auto innerSerializer = m_serializerFactory.getArraySerializer<string*, string>(
                                                        m_serializerFactory.getStringSerializer(),
                                                        innerCollectionSizeFunction,
                                                        innerElementAccessFunction);

    auto serializer = m_serializerFactory.getArraySerializer<T, string*>(
                                                        innerSerializer,
                                                        collectionSizeFunction,
                                                        elementAccessFunction);

    auto propertyDefinition = new ArrayPropertyDefinition<T, string*>(propertyName);
    propertyDefinition->m_arraySize      = collectionSizeFunction;
    propertyDefinition->m_elementAccess  = elementAccessFunction;
    propertyDefinition->m_serializer     = serializer;

    return shared_ptr< PropertyDefinitionBase<T> >(propertyDefinition);
}

#endif // PROPERTYDEFINITIONFACTORY_H

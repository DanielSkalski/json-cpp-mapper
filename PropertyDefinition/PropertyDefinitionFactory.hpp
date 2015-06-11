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

namespace mapper {

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
    auto propertyDefinition = PropertyDefinition<T, string>::make_shared(propertyName, PropertyKind::String);
    propertyDefinition->m_getValueFunction = valueFunction;
    propertyDefinition->m_serializer       = m_serializerFactory.getStringSerializer();

    return propertyDefinition;
}

template<class T>
template<typename PROP_T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createValuePropertyDefinition(const string &propertyName,
                                                            function<PROP_T (const T&)> valueFunction) const
{
    auto propertyDefinition = PropertyDefinition<T, PROP_T>::make_shared(propertyName, PropertyKind::Number);
    propertyDefinition->m_getValueFunction = valueFunction;
    propertyDefinition->m_serializer       = m_serializerFactory.getNumberSerializer<PROP_T>();

    return propertyDefinition;
}

template<class T>
template<class PROP_T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createPropertyDefinition(const string &propertyName,
                                                       function<PROP_T (const T &)> valueFunction,
                                                       const Mapping<PROP_T> &propertyTypeMapping) const
{
    auto propertyDefinition = ObjectPropertyDefinition<T, PROP_T>::make_shared(propertyName);
    propertyDefinition->m_getValueFunction    = valueFunction;
    propertyDefinition->m_propertyTypeMapping = propertyTypeMapping;
    propertyDefinition->m_serializer          = m_serializerFactory.getObjectSerializer(propertyTypeMapping);

    return propertyDefinition;
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

    auto propertyDefinition = ArrayPropertyDefinition<T, ELEM_T>::make_shared(propertyName);
    propertyDefinition->m_arraySize     = collectionSizeFunction;
    propertyDefinition->m_elementAccess = elementAccessFunction;
    propertyDefinition->m_serializer    = m_serializerFactory.getArraySerializer<T, ELEM_T>(elementSerializer,
                                                                                 collectionSizeFunction,
                                                                                 elementAccessFunction);

    return propertyDefinition;
}


template<class T>
template<class ELEM_T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createArrayPropertyDefinition(const string& propertyName,
                                                            function<int (const T&)> collectionSizeFunction,
                                                            function<ELEM_T (const T&, int)> elementAccessFunction) const
{
    auto elementSerializer = m_serializerFactory.getNumberSerializer<ELEM_T>();

    auto propertyDefinition = ArrayPropertyDefinition<T, ELEM_T>::make_shared(propertyName);
    propertyDefinition->m_arraySize      = collectionSizeFunction;
    propertyDefinition->m_elementAccess  = elementAccessFunction;
    propertyDefinition->m_serializer     = m_serializerFactory.getArraySerializer<T, ELEM_T>(
                                                                        elementSerializer,
                                                                        collectionSizeFunction,
                                                                        elementAccessFunction);

    return propertyDefinition;
}

template<class T>
shared_ptr< PropertyDefinitionBase<T> >
PropertyDefinitionFactory<T>::createArrayPropertyDefinition (const string& propertyName,
                                                             function<int (const T&)> collectionSizeFunction,
                                                             function<string (const T&, int)> elementAccessFunction) const
{
    auto elementSerializer = m_serializerFactory.getStringSerializer();

    auto propertyDefinition = ArrayPropertyDefinition<T, string>::make_shared(propertyName);
    propertyDefinition->m_arraySize      = collectionSizeFunction;
    propertyDefinition->m_elementAccess  = elementAccessFunction;
    propertyDefinition->m_serializer     = m_serializerFactory.getArraySerializer<T, string>(
                                                                            elementSerializer,
                                                                            collectionSizeFunction,
                                                                            elementAccessFunction);

    return propertyDefinition;
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

    auto propertyDefinition = ArrayPropertyDefinition<T, string*>::make_shared(propertyName);
    propertyDefinition->m_arraySize      = collectionSizeFunction;
    propertyDefinition->m_elementAccess  = elementAccessFunction;
    propertyDefinition->m_serializer     = serializer;

    return propertyDefinition;
}

} // namespace mapper

#endif // PROPERTYDEFINITIONFACTORY_H

#ifndef SERIALIZERFACTORY_H
#define SERIALIZERFACTORY_H

#include "NumberSerializer.hpp"
#include "ObjectSerializer.hpp"
#include "ArraySerializer.hpp"
#include "StringSerializer.hpp"

#include <memory>

class SerializerFactory
{
    std::shared_ptr< NumberSerializer<int> > m_numberSerializer;
    std::shared_ptr<StringSerializer> m_stringSerializer;

public:
    SerializerFactory();
    ~SerializerFactory();

    template<typename NUM_T>
    shared_ptr< NumberSerializer<NUM_T> > getNumberSerializer() const;

    shared_ptr< StringSerializer > getStringSerializer() const;

    template<class OBJ_T>
    shared_ptr< ObjectSerializer<OBJ_T> > getObjectSerializer(const Mapping<OBJ_T>& mapping) const;

    template<class OBJ_T, class ELEMENT_T>
    shared_ptr< ArraySerializer<OBJ_T, ELEMENT_T> > getArraySerializer(
                                                          shared_ptr< ISerializer<ELEMENT_T> > elementSerializer,
                                                          function<int (const OBJ_T&)> collectionSizeFunction,
                                                          function<ELEMENT_T (const OBJ_T&, int)> elementAccessFunction) const;
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

SerializerFactory::SerializerFactory()
{

}

SerializerFactory::~SerializerFactory()
{

}

// ----- METHODS --------------------------------------------------------------

template<typename NUM_T>
shared_ptr< NumberSerializer<NUM_T> > SerializerFactory::getNumberSerializer() const
{
    return NumberSerializer<NUM_T>::make_shared();
}

shared_ptr<StringSerializer> SerializerFactory::getStringSerializer() const
{
    return StringSerializer::make_shared();
}

template<class OBJ_T>
shared_ptr< ObjectSerializer<OBJ_T> > SerializerFactory::getObjectSerializer(const Mapping<OBJ_T>& mapping) const
{
    return ObjectSerializer<OBJ_T>::make_shared(mapping);
}

template<class OBJ_T, class ELEMENT_T>
shared_ptr< ArraySerializer<OBJ_T, ELEMENT_T> > SerializerFactory::getArraySerializer(
                                                       shared_ptr< ISerializer<ELEMENT_T> > elementSerializer,
                                                       function<int (const OBJ_T&)> collectionSizeFunction,
                                                       function<ELEMENT_T (const OBJ_T&, int)> elementAccessFunction) const
{
    auto serializer = ArraySerializer<OBJ_T, ELEMENT_T>::make_shared(elementSerializer);
    serializer->m_arraySize     = collectionSizeFunction;
    serializer->m_elementAccess = elementAccessFunction;

    return serializer;
}

#endif // SERIALIZERFACTORY_H

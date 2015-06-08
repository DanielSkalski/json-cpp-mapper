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
    NumberSerializer<NUM_T>* getNumberSerializer() const;

    StringSerializer* getStringSerializer() const;

    template<class OBJ_T>
    ObjectSerializer<OBJ_T>* getObjectSerializer(const Mapping<OBJ_T>& mapping) const;

    template<class OBJ_T, class ELEMENT_T>
    ArraySerializer<OBJ_T, ELEMENT_T>* getArraySerializer(ISerializer<ELEMENT_T>* elementSerializer,
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
NumberSerializer<NUM_T>* SerializerFactory::getNumberSerializer() const
{
    return new NumberSerializer<NUM_T>();
}

StringSerializer* SerializerFactory::getStringSerializer() const
{
    return new StringSerializer();
}

template<class OBJ_T>
ObjectSerializer<OBJ_T>* SerializerFactory::getObjectSerializer(const Mapping<OBJ_T>& mapping) const
{
    return new ObjectSerializer<OBJ_T>(mapping);
}

template<class OBJ_T, class ELEMENT_T>
ArraySerializer<OBJ_T, ELEMENT_T>* SerializerFactory::getArraySerializer(ISerializer<ELEMENT_T>* elementSerializer,
                                                       function<int (const OBJ_T&)> collectionSizeFunction,
                                                       function<ELEMENT_T (const OBJ_T&, int)> elementAccessFunction) const
{
    auto serializer = new ArraySerializer<OBJ_T, ELEMENT_T>(elementSerializer);
    serializer->m_arraySize     = collectionSizeFunction;
    serializer->m_elementAccess = elementAccessFunction;

    return serializer;
}

#endif // SERIALIZERFACTORY_H

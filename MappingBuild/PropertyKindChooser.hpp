#ifndef PROPERTYKINDCHOOSER_H
#define PROPERTYKINDCHOOSER_H

#include "MappingBuilder.hpp"
#include "MappingForObjectPropertyChooser.hpp"
#include "ItemsForArrayPropertyChooser.hpp"
#include <functional>
#include <iostream>

using namespace std;

namespace mapper {

template<class T>
class PropertyKindChooser
{
    template<class, class>
    friend class MappingForObjectPropertyChooser;

    friend class ItemsForArrayPropertyChooser<T>;

    MappingBuilder<T>* m_mappingBuilder;

public:
    explicit PropertyKindChooser(MappingBuilder<T>* mappingBuilder);

    ~PropertyKindChooser()
    {
//        std::cout << "Destruktor MappingPropertyKindChooser" << std::endl;
    }

    void asString(function<string (const T&)> getFunc);

    void asBoolean(function<bool (const T&)> getFunc);

    void asNumber(function<int (const T&)> getFunc);
    void asNumber(function<float (const T&)> getFunc);
//    void asNumber(function<double (const T&)> getFunc);
//    void asNumber(function<long long (const T&)> getFunc);
//    void asNumber(function<char (const T&)> getFunc);
//    void asNumber(function<short (const T&)> getFunc);

    template<class OBJ_T>
    MappingForObjectPropertyChooser<T, OBJ_T>* asObject(function<OBJ_T (const T&)>);

    ItemsForArrayPropertyChooser<T>* asArray();

private:
    template<class OBJ_T>
    void mapAsObjectMappedWith(Mapping<OBJ_T> mapping, function<OBJ_T (const T&)> getFunc);

    template<class ELEM_T>
    void mapAsArrayOf(function<int (const T &)>     collectionSizeFunction,
                      function<ELEM_T (const T &, int)> elementAccessFunction);

    template<class ELEM_T>
    void mapAsArrayOf(function<int (const T &)>     collectionSizeFunction,
                      function<ELEM_T (const T &, int)> elementAccessFunction,
                      Mapping<ELEM_T> mapping);
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
PropertyKindChooser<T>::PropertyKindChooser(MappingBuilder<T> *mappingBuilder)
    : m_mappingBuilder(mappingBuilder)
{

}

// ----- METHODS --------------------------------------------------------------

template<class T>
void PropertyKindChooser<T>::asString(function<string (const T&)> getFunc)
{
    m_mappingBuilder->mapAsString(getFunc);

    delete this;
}

template<class T>
void PropertyKindChooser<T>::asBoolean(function<bool (const T&)> getFunc)
{
    m_mappingBuilder->mapAsBoolean(getFunc);
    delete this;
}

template<class T>
void PropertyKindChooser<T>::asNumber(function<int (const T&)> getFunc)
{
    m_mappingBuilder->mapAsNumber(getFunc);
    delete this;
}

template<class T>
void PropertyKindChooser<T>::asNumber(function<float (const T&)> getFunc)
{
    m_mappingBuilder->mapAsNumber(getFunc);
    delete this;
}

template<class T>
template<class OBJ_T>
MappingForObjectPropertyChooser<T, OBJ_T> *PropertyKindChooser<T>::asObject(
        function<OBJ_T (const T&)> getFunc)
{
    return new MappingForObjectPropertyChooser<T, OBJ_T>(this, getFunc);
}

template<class T>
ItemsForArrayPropertyChooser<T>* PropertyKindChooser<T>::asArray()
{
    return new ItemsForArrayPropertyChooser<T>(this);
}

// --- PRIVATE ---

template<class T>
template<class OBJ_T>
void PropertyKindChooser<T>::mapAsObjectMappedWith(Mapping<OBJ_T> mapping,
                                                          function<OBJ_T (const T&)> getFunc)
{
    m_mappingBuilder->mapAsObjectMappedWith(mapping, getFunc);
    delete this;
}

template<class T>
template<class ELEM_T>
void PropertyKindChooser<T>::mapAsArrayOf(function<int (const T &)>     collectionSizeFunction,
                                          function<ELEM_T (const T &, int)> elementAccessFunction)
{
    m_mappingBuilder->mapAsArrayOf(collectionSizeFunction, elementAccessFunction);
    delete this;
}

template<class T>
template<class ELEM_T>
void PropertyKindChooser<T>::mapAsArrayOf(function<int (const T &)>     collectionSizeFunction,
                                          function<ELEM_T (const T &, int)> elementAccessFunction,
                                          Mapping<ELEM_T> mapping)
{
    m_mappingBuilder->mapAsArrayOfObjects(collectionSizeFunction, elementAccessFunction, mapping);
    delete this;
}

} // namespace mapper

#endif // PROPERTYKINDCHOOSER_H

#ifndef MAPPINGPROPERTYKINDCHOOSER_H
#define MAPPINGPROPERTYKINDCHOOSER_H

#include "MappingBuilder.hpp"
#include "MappingForObjectPropertyChooser.hpp"
#include "ItemsForArrayPropertyChooser.hpp"
#include <functional>
#include <iostream>

using namespace std;

namespace mapper {

template<class T>
class MappingPropertyKindChooser
{
    template<class, class>
    friend class MappingForObjectPropertyChooser;

    friend class ItemsForArrayPropertyChooser<T>;

    MappingBuilder<T>* m_mappingBuilder;

public:
    explicit MappingPropertyKindChooser(MappingBuilder<T>* mappingBuilder);

    ~MappingPropertyKindChooser()
    {
        std::cout << "Destruktor MappingPropertyKindChooser" << std::endl;
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

    void mapAsArrayOfStrings(function<int (const T &)>     collectionSizeFunction,
                             function<string (const T &, int)> elementAccessFunction);
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
MappingPropertyKindChooser<T>::MappingPropertyKindChooser(MappingBuilder<T> *mappingBuilder)
    : m_mappingBuilder(mappingBuilder)
{

}

// ----- METHODS --------------------------------------------------------------

template<class T>
void MappingPropertyKindChooser<T>::asString(function<string (const T&)> getFunc)
{
    m_mappingBuilder->mapAsString(getFunc);

    delete this;
}

template<class T>
void MappingPropertyKindChooser<T>::asBoolean(function<bool (const T&)> getFunc)
{
    m_mappingBuilder->mapAsBoolean(getFunc);
    delete this;
}

template<class T>
void MappingPropertyKindChooser<T>::asNumber(function<int (const T&)> getFunc)
{
    m_mappingBuilder->mapAsNumber(getFunc);
    delete this;
}

template<class T>
void MappingPropertyKindChooser<T>::asNumber(function<float (const T&)> getFunc)
{
    m_mappingBuilder->mapAsNumber(getFunc);
    delete this;
}

template<class T>
template<class OBJ_T>
MappingForObjectPropertyChooser<T, OBJ_T> *MappingPropertyKindChooser<T>::asObject(
        function<OBJ_T (const T&)> getFunc)
{
    return new MappingForObjectPropertyChooser<T, OBJ_T>(this, getFunc);
}

template<class T>
ItemsForArrayPropertyChooser<T>* MappingPropertyKindChooser<T>::asArray()
{
    return new ItemsForArrayPropertyChooser<T>(this);
}

// --- PRIVATE ---

template<class T>
template<class OBJ_T>
void MappingPropertyKindChooser<T>::mapAsObjectMappedWith(Mapping<OBJ_T> mapping,
                                                          function<OBJ_T (const T&)> getFunc)
{
    m_mappingBuilder->mapAsObjectMappedWith(mapping, getFunc);
    delete this;
}

template<class T>
void MappingPropertyKindChooser<T>::mapAsArrayOfStrings(function<int (const T &)>     collectionSizeFunction,
                                                        function<string (const T &, int)> elementAccessFunction)
{
    m_mappingBuilder->mapAsArrayOfStrings(collectionSizeFunction, elementAccessFunction);
    delete this;
}

} // namespace mapper

#endif // MAPPINGPROPERTYKINDCHOOSER_H

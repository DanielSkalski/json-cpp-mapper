#ifndef MAPPINGPROPERTYKINDCHOOSER_H
#define MAPPINGPROPERTYKINDCHOOSER_H

#include "MappingBuilder.hpp"
#include "MappingForObjectPropertyChooser.hpp"
#include <functional>
#include <iostream>

using namespace std;

namespace mapper {

template<class T>
class MappingPropertyKindChooser
{
    template<class, class>
    friend class MappingForObjectPropertyChooser;

    MappingBuilder<T>* m_mappingBuilder;

public:
    explicit MappingPropertyKindChooser(MappingBuilder<T>* mappingBuilder);

    void asString(function<string (const T&)> getFunc);

    void asBoolean(function<bool (const T&)> getFunc);

    void asNumber(function<int (const T&)> getFunc);
    void asNumber(function<float (const T&)> getFunc);
//    void asNumber(function<double (const T&)> getFunc);
//    void asNumber(function<long long (const T&)> getFunc);
//    void asNumber(function<char (const T&)> getFunc);
//    void asNumber(function<short (const T&)> getFunc);

    template<class OBJ_T>
    unique_ptr<MappingForObjectPropertyChooser<T, OBJ_T>> asObject(function<OBJ_T (const T&)>);

//    void asArray();

private:
    template<class OBJ_T>
    void mapAsObjectMappedWith(Mapping<OBJ_T> mapping, function<OBJ_T (const T&)> getFunc);
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
}

template<class T>
void MappingPropertyKindChooser<T>::asBoolean(function<bool (const T&)> getFunc)
{
    m_mappingBuilder->mapAsBoolean(getFunc);
}

template<class T>
void MappingPropertyKindChooser<T>::asNumber(function<int (const T&)> getFunc)
{
    m_mappingBuilder->mapAsNumber(getFunc);
}

template<class T>
void MappingPropertyKindChooser<T>::asNumber(function<float (const T&)> getFunc)
{
    m_mappingBuilder->mapAsNumber(getFunc);
}

template<class T>
template<class OBJ_T>
unique_ptr<MappingForObjectPropertyChooser<T, OBJ_T>>
MappingPropertyKindChooser<T>::asObject(function<OBJ_T (const T&)> getFunc)
{
//    return unique_ptr<MappingForObjectPropertyChooser<T, OBJ_T>>(
//            new MappingForObjectPropertyChooser<T, OBJ_T>(this, getFunc));

    return unique_ptr<MappingForObjectPropertyChooser<T, OBJ_T>>(
            new MappingForObjectPropertyChooser<T, OBJ_T>(m_mappingBuilder, getFunc));
}

// --- PRIVATE ---

template<class T>
template<class OBJ_T>
void MappingPropertyKindChooser<T>::mapAsObjectMappedWith(Mapping<OBJ_T> mapping,
                                                          function<OBJ_T (const T&)> getFunc)
{
    m_mappingBuilder->mapAsObjectMappedWith(mapping, getFunc);
}

} // namespace mapper

#endif // MAPPINGPROPERTYKINDCHOOSER_H

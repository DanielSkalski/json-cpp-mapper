#ifndef MAPPINGPROPERTYKINDCHOOSER_H
#define MAPPINGPROPERTYKINDCHOOSER_H

#include "MappingBuilder.hpp"
#include <functional>

using namespace std;

namespace mapper {

template<class T>
class MappingPropertyKindChooser
{
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

//    void asObject();

//    void asArray();
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

} // namespace mapper

#endif // MAPPINGPROPERTYKINDCHOOSER_H

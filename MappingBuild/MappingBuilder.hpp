#ifndef MAPPINGBUILDER_H
#define MAPPINGBUILDER_H

#include <string>
#include <functional>
#include <memory>
#include <PropertyDefinition/PropertyDefinitionFactory.hpp>

using namespace std;

namespace mapper {

template<class T>
class MappingPropertyKindChooser;

template<class T>
class Mapping;

template<class T>
class MappingBuilder
{
    friend class MappingPropertyKindChooser<T>;

    string m_propertyName;
    Mapping<T>* m_mapping;

    PropertyDefinitionFactory<T> m_propertyDefinitionFactory;

public:
    explicit MappingBuilder(Mapping<T>* mapping);

    unique_ptr<MappingPropertyKindChooser<T>> map(const string& propertyName);

private:
    void mapAsString(function<string (const T&)> getFunc);

    void mapAsBoolean(function<bool (const T&)> getFunc);

    template<typename RET>
    void mapAsNumber(function<RET (const T&)> getFunc);
};


// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
MappingBuilder<T>::MappingBuilder(Mapping<T> *mapping)
    : m_mapping(mapping)
{

}

// ----- METHODS --------------------------------------------------------------

template<class T>
unique_ptr<MappingPropertyKindChooser<T>> MappingBuilder<T>::map(const string &propertyName)
{
    this->m_propertyName = propertyName;

    return unique_ptr<MappingPropertyKindChooser<T>>(new MappingPropertyKindChooser<T>(this));
}

template<class T>
void MappingBuilder<T>::mapAsString(function<string (const T&)> getFunc)
{
    auto propDef = m_propertyDefinitionFactory.createPropertyDefinition(m_propertyName, getFunc);

    m_mapping->m_properties.push_back(propDef);
}

template<class T>
void MappingBuilder<T>::mapAsBoolean(function<bool (const T&)> getFunc)
{
    auto propDef = m_propertyDefinitionFactory.createPropertyDefinition(m_propertyName, getFunc);

    m_mapping->m_properties.push_back(propDef);
}

template<class T>
template<typename RET>
void MappingBuilder<T>::mapAsNumber(function<RET (const T&)> getFunc)
{
    auto propDef = m_propertyDefinitionFactory.createPropertyDefinition(m_propertyName, getFunc);

    m_mapping->m_properties.push_back(propDef);
}

} // namespace mapper

#endif // MAPPINGBUILDER_H

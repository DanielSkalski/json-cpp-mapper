#ifndef MAPPINGBUILDER_H
#define MAPPINGBUILDER_H

#include <string>
#include <iostream>
#include <functional>
#include <memory>
#include <PropertyDefinition/PropertyDefinitionFactory.hpp>

using namespace std;

namespace mapper {

template<class T>
class PropertyKindChooser;

template<class T>
class Mapping;

template<class T>
class MappingBuilder
{
    friend class PropertyKindChooser<T>;

    template<class, class>
    friend class MappingForObjectPropertyChooser;

    string m_propertyName;
    Mapping<T>* m_mapping;

    PropertyDefinitionFactory<T> m_propertyDefinitionFactory;

public:
    explicit MappingBuilder(Mapping<T>* mapping);

    ~MappingBuilder()
    {
//        std::cout << "Destruktor MappingBuilder" << std::endl;
    }

    PropertyKindChooser<T>* map(const string& propertyName);

private:
    void mapAsString(function<string (const T&)> getFunc);

    void mapAsBoolean(function<bool (const T&)> getFunc);

    template<typename RET>
    void mapAsNumber(function<RET (const T&)> getFunc);

    template<class OBJ_T>
    void mapAsObjectMappedWith(Mapping<OBJ_T> mapping, function<OBJ_T (const T&)> getFunc);

    template<class ELEM_T>
    void mapAsArrayOf(function<int (const T &)>     collectionSizeFunction,
                      function<ELEM_T (const T &, int)> elementAccessFunction);

    template<class ELEM_T>
    void mapAsArrayOfObjects(function<int (const T &)>     collectionSizeFunction,
                             function<ELEM_T (const T &, int)> elementAccessFunction,
                             const Mapping<ELEM_T>& elementTypeMapping);
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
PropertyKindChooser<T>* MappingBuilder<T>::map(const string &propertyName)
{
    this->m_propertyName = propertyName;

    return new PropertyKindChooser<T>(this);
}

template<class T>
void MappingBuilder<T>::mapAsString(function<string (const T&)> getFunc)
{
    auto propDef = m_propertyDefinitionFactory.createPropertyDefinition(m_propertyName, getFunc);

    m_mapping->m_properties.push_back(propDef);
    delete this;
}

template<class T>
void MappingBuilder<T>::mapAsBoolean(function<bool (const T&)> getFunc)
{
    auto propDef = m_propertyDefinitionFactory.createPropertyDefinition(m_propertyName, getFunc);

    m_mapping->m_properties.push_back(propDef);
    delete this;
}

template<class T>
template<typename RET>
void MappingBuilder<T>::mapAsNumber(function<RET (const T&)> getFunc)
{
    auto propDef = m_propertyDefinitionFactory.createPropertyDefinition(m_propertyName, getFunc);

    m_mapping->m_properties.push_back(propDef);
    delete this;
}

template<class T>
template<class OBJ_T>
void MappingBuilder<T>::mapAsObjectMappedWith(Mapping<OBJ_T> mapping, function<OBJ_T (const T&)> getFunc)
{
    auto propDef = m_propertyDefinitionFactory.createPropertyDefinition(m_propertyName,
                                                                        getFunc,
                                                                        mapping);

    m_mapping->m_properties.push_back(propDef);
    delete this;
}

template<class T>
template<class ELEM_T>
void MappingBuilder<T>::mapAsArrayOf(function<int (const T &)>     collectionSizeFunction,
                                     function<ELEM_T (const T &, int)> elementAccessFunction)
{
    auto propDef = m_propertyDefinitionFactory.createArrayPropertyDefinition(m_propertyName,
                                                                             collectionSizeFunction,
                                                                             elementAccessFunction);

    m_mapping->m_properties.push_back(propDef);
    delete this;
}

template<class T>
template<class ELEM_T>
void MappingBuilder<T>::mapAsArrayOfObjects(function<int (const T &)>     collectionSizeFunction,
                                            function<ELEM_T (const T &, int)> elementAccessFunction,
                                            const Mapping<ELEM_T>& elementTypeMapping)
{
    auto propDef = m_propertyDefinitionFactory.createArrayPropertyDefinition(m_propertyName,
                                                                             collectionSizeFunction,
                                                                             elementAccessFunction,
                                                                             elementTypeMapping);

    m_mapping->m_properties.push_back(propDef);
    delete this;
}

} // namespace mapper

#endif // MAPPINGBUILDER_H

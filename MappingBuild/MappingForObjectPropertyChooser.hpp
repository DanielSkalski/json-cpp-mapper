#ifndef MAPPINGFOROBJECTPROPERTYCHOOSER_H
#define MAPPINGFOROBJECTPROPERTYCHOOSER_H

#include "PropertyKindChooser.hpp"

namespace mapper {

template<class T>
class Mapping;

template<class T, class OBJ_T>
class MappingForObjectPropertyChooser
{
    PropertyKindChooser<T>* m_previousChooser;
    MappingBuilder<T>* m_mappingBuilder;

    function<OBJ_T (const T&)> m_getFunc;

public:
    MappingForObjectPropertyChooser(PropertyKindChooser<T>* previousChooser,
                                    function<OBJ_T (const T&)> getFunc);

    MappingForObjectPropertyChooser(MappingBuilder<T>* mappingBuilder,
                                    function<OBJ_T (const T&)> getFunc);

    ~MappingForObjectPropertyChooser()
    {
        std::cout << "Destructor MappingForObjectPropertyChooser" << std::endl;
    }

    void mappedWith(Mapping<OBJ_T> mapping);
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T, class OBJ_T>
MappingForObjectPropertyChooser<T, OBJ_T>::MappingForObjectPropertyChooser(
        PropertyKindChooser<T>* previousChooser,
        function<OBJ_T (const T&)> getFunc)
    : m_previousChooser(previousChooser), m_getFunc(getFunc)
{

}

template<class T, class OBJ_T>
MappingForObjectPropertyChooser<T, OBJ_T>::MappingForObjectPropertyChooser(
        MappingBuilder<T>* mappingBuilder,
        function<OBJ_T (const T&)> getFunc)
    : m_mappingBuilder(mappingBuilder), m_getFunc(getFunc)
{

}

// ----- METHODS --------------------------------------------------------------

template<class T, class OBJ_T>
void MappingForObjectPropertyChooser<T, OBJ_T>::mappedWith(Mapping<OBJ_T> mapping)
{
    m_previousChooser->mapAsObjectMappedWith(mapping, m_getFunc);
    delete this;
}

}

#endif // MAPPINGFOROBJECTPROPERTYCHOOSER_H

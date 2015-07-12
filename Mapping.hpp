#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "PropertyDefinition/PropertyDefinition.hpp"
#include "PropertyDefinition/PropertyDefinitionFactory.hpp"
#include "MappingBuild/MappingBuilder.hpp"
#include "MappingBuild/PropertyKindChooser.hpp"

#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include <list>

using namespace std;

namespace mapper {

template<class T>
class Mapping
{
    friend class MappingBuilder<T>;

    PropertyDefinitionFactory<T> m_propertyDefinitionFactory;
    list<shared_ptr<PropertyDefinitionBase<T>>> m_properties;

public:
    Mapping();
    virtual ~Mapping();

    const list< shared_ptr< PropertyDefinitionBase<T> > >& properties() const;

    PropertyKindChooser<T>* map(const string& propertyName);
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class T>
Mapping<T>::Mapping()
{
}

template<class T>
Mapping<T>::~Mapping()
{
}

// ----- METHODS --------------------------------------------------------------

template<class T>
const list<shared_ptr<PropertyDefinitionBase<T> > >& Mapping<T>::properties() const
{
    return m_properties;
}

template<class T>
PropertyKindChooser<T> *Mapping<T>::map(const string &propertyName)
{
    auto mb = new MappingBuilder<T>(this);

    return mb->map(propertyName);
}

} // namespace mapper

#endif // SERIALIZER_H

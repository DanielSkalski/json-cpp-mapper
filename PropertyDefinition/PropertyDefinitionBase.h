#ifndef PROPERTYDEFINITIONBASE_H
#define PROPERTYDEFINITIONBASE_H

#include <string>
#include "PropertyKind.h"

using namespace std;

namespace mapper {

template<class OBJ_T>
class PropertyDefinitionBase
{
    string m_propertyName;

public:

    explicit PropertyDefinitionBase(const string& propertyName)
        : m_propertyName(propertyName)
    { }

    virtual ~PropertyDefinitionBase() { }

    string inline propertyName() const
    {
        return m_propertyName;
    }

    virtual string serializeValue(const OBJ_T& obj) const = 0;

    virtual PropertyKind propertyKind() const = 0;
};

} // namespace mapper

#endif // PROPERTYDEFINITIONBASE_H

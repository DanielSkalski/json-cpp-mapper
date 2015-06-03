#ifndef PROPERTYDEFINITIONBASE_H
#define PROPERTYDEFINITIONBASE_H

#include <string>
#include "PropertyKind.h"
#include "Serializer/ISerializer.h"

using namespace std;

template<class OBJ_T>
class PropertyDefinitionBase
{
public:
    string propertyName;

    virtual ~PropertyDefinitionBase() { }

    virtual string serializeValue(const OBJ_T& obj) const = 0;

    virtual PropertyKind propertyKind() const = 0;
};

#endif // PROPERTYDEFINITIONBASE_H

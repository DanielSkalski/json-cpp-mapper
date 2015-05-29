#ifndef PROPERTYDEFINITIONBASE_H
#define PROPERTYDEFINITIONBASE_H

#include <string>
#include "PropertyKind.h"

using namespace std;

template<class T>
class PropertyDefinitionBase
{
public:
    string propertyName;
    PropertyKind propertyKind;

    virtual ~PropertyDefinitionBase() { }

    virtual string serializeValue(const T& obj) const = 0;
};

#endif // PROPERTYDEFINITIONBASE_H

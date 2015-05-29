#ifndef OBJECTPROPERTYDEFINITION_H
#define OBJECTPROPERTYDEFINITION_H

#include "PropertyDefinition.hpp"

#include <functional>
#include <sstream>
#include <string>

using namespace std;


template<class T>
class Serializer;

template<class T, class OT>
class ObjectPropertyDefinition : public PropertyDefinition<T>
{
public:
    virtual ~ObjectPropertyDefinition() { }

    Serializer<OT> serializer;
    function<OT (const T&)> mappingObject;

    string serializeValue(const T &obj) const override;
};

// ----------------------------------------------------------------------------

template<class T, class OT>
string ObjectPropertyDefinition<T, OT>::serializeValue(const T &obj) const
{
    stringstream out;

    OT value = mappingObject(obj);

    string serializedValue = serializer.serialize(value);

    if (serializedValue.empty())
    {
        serializedValue = "null";
    }

    out << serializedValue;

    return out.str();
}


#endif // OBJECTPROPERTYDEFINITION_H

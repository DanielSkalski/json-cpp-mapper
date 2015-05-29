#ifndef ARRAYPROPERTYDEFINITION_H
#define ARRAYPROPERTYDEFINITION_H

#include "PropertyDefinitionBase.h"

#include <functional>
#include <sstream>
#include <string>

using namespace std;

template<class T>
class Serializer;


template<class T, class OT>
class ArrayPropertyDefinition : public PropertyDefinitionBase<T>
{
public:
    virtual ~ArrayPropertyDefinition() { }

    Serializer<OT> elementSerializer;
    function<int (const T&)> arraySize;
    function<OT (const T&, int)> elementAccess;

    string serializeValue(const T &obj) const override;
};


// ----------------------------------------------------------------------------

template<class T, class OT>
string ArrayPropertyDefinition<T, OT>::serializeValue(const T &obj) const
{
    stringstream out;

    out << "[" << endl;

    for (int i = 0; i < arraySize(obj); i++)
    {
        OT value = elementAccess(obj, i);

        string serializedValue = elementSerializer.serialize(value);

        if (serializedValue.empty())
        {
            serializedValue = "null";
        }

        out << serializedValue << "," << endl;
    }

    if (arraySize(obj) > 0)
    {
        // remove last "," sign
        out.seekp(-2, out.cur);
    }

    out << "]" << endl;

    return out.str();
}

#endif // ARRAYPROPERTYDEFINITION_H

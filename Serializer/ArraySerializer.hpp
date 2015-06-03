#ifndef ARRAYSERIALIZER_H
#define ARRAYSERIALIZER_H

#include "ISerializer.h"

template<class OBJ_T, class ELEMENT_T>
class ArraySerializer : ISerializer<OBJ_T>
{
public:
    explicit ArraySerializer(ISerializer<ELEMENT_T>* elementSerializer)
    {
        this->elementSerializer = elementSerializer;
    }

    virtual ~ArraySerializer() {}

    ISerializer<ELEMENT_T>* elementSerializer;

    string serialize(const OBJ_T &obj) const override;
};

// ----------------------------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
string ArraySerializer<OBJ_T, ELEMENT_T>::serialize(const OBJ_T &obj) const
{
    stringstream out;

    out << "[" << endl;

    for (int i = 0; i < arraySize(obj); i++)
    {
        ELEMENT_T value = elementAccess(obj, i);

        string serializedValue = elementSerializer->serialize(value);

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

#endif // ARRAYSERIALIZER_H

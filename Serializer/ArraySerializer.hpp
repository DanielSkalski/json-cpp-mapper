#ifndef ARRAYSERIALIZER_H
#define ARRAYSERIALIZER_H

#include "ISerializer.h"
#include <functional>

template<class OBJ_T, class ELEMENT_T>
class ArraySerializer : public ISerializer<OBJ_T>
{
public:
    ArraySerializer()
    {

    }

    explicit ArraySerializer(ISerializer<ELEMENT_T>* elementSerializer)
    {
        this->elementSerializer = elementSerializer;
    }

    virtual ~ArraySerializer() {}

    ISerializer<ELEMENT_T>* elementSerializer;
    function<int (const OBJ_T&)> arraySize;
    function<ELEMENT_T (const OBJ_T&, int)> elementAccess;

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

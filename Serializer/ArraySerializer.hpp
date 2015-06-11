#ifndef ARRAYSERIALIZER_H
#define ARRAYSERIALIZER_H

#include "SerializerCommon.h"
#include <functional>

namespace mapper {

template<class OBJ_T, class ELEMENT_T>
class ArraySerializer : public ISerializer<OBJ_T>
{
    friend class SerializerFactory;
    struct private_ctor { };

    static shared_ptr<ArraySerializer<OBJ_T, ELEMENT_T>> make_shared(
            shared_ptr<ISerializer<ELEMENT_T>>& elementSerializer)
    {
        return std::make_shared<ArraySerializer<OBJ_T, ELEMENT_T>>(private_ctor(), elementSerializer);
    }

    shared_ptr< ISerializer<ELEMENT_T> > m_elementSerializer;
    function<int (const OBJ_T&)> m_arraySize;
    function<ELEMENT_T (const OBJ_T&, int)> m_elementAccess;

public:
    ArraySerializer(const private_ctor&, shared_ptr< ISerializer<ELEMENT_T> >& elementSerializer);
    virtual ~ArraySerializer() {}

    string serialize(const OBJ_T &obj) const override;
};

// ----------------------------------------------------------------------------

// ---- CONSTRUCTORS ----------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
ArraySerializer<OBJ_T, ELEMENT_T>::ArraySerializer(const private_ctor &,
                                                   shared_ptr< ISerializer<ELEMENT_T> >& elementSerializer)
    : m_elementSerializer(elementSerializer)
{
}

// ----- METHODS --------------------------------------------------------------

template<class OBJ_T, class ELEMENT_T>
string ArraySerializer<OBJ_T, ELEMENT_T>::serialize(const OBJ_T &obj) const
{
    stringstream out;

    out << "[" << endl;

    for (int i = 0; i < m_arraySize(obj); i++)
    {
        ELEMENT_T value = m_elementAccess(obj, i);

        string serializedValue = m_elementSerializer->serialize(value);

        out << serializedValue << "," << endl;
    }

    if (m_arraySize(obj) > 0)
    {
        // remove last "," sign
        out.seekp(-2, out.cur);
    }

    out << "]" << endl;

    return out.str();
}

} // namespace mapper

#endif // ARRAYSERIALIZER_H

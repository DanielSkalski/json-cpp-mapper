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

    JsonStream& serialize(const OBJ_T &obj, JsonStream& out) const override;
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
JsonStream& ArraySerializer<OBJ_T, ELEMENT_T>::serialize(const OBJ_T &obj, JsonStream& out) const
{
    out << "[" << "\n";

    int arraySize =  m_arraySize(obj);

    for (int i = 0; i < arraySize; i++)
    {
        ELEMENT_T value = m_elementAccess(obj, i);

        m_elementSerializer->serialize(value, out);

        if (i < arraySize - 1)
        {
            out << "," << "\n";
        }
    }

    out << "]" << "\n";

    return out;
}

} // namespace mapper

#endif // ARRAYSERIALIZER_H

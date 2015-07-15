#ifndef VALUESERIALIZER_H
#define VALUESERIALIZER_H

#include "SerializerCommon.h"

namespace mapper {

template<class T>
class NumberSerializer : public ISerializer<T>
{
    friend class SerializerFactory;
    struct private_ctor { };

    NumberSerializer() { }

    static shared_ptr<NumberSerializer<T>> make_shared()
    {
        return std::make_shared<NumberSerializer<T>>(private_ctor());
    }

public:
    explicit NumberSerializer(const private_ctor&) {}
    virtual ~NumberSerializer() { }

    JsonStream& serialize(const T &value, JsonStream& out) const override;
};

// ----------------------------------------------------------------------------

template<class T>
JsonStream &NumberSerializer<T>::serialize(const T &value, JsonStream &out) const
{
    out << std::to_string(value);

    return out;
}

} // namespace mapper

#endif // VALUESERIALIZER_H

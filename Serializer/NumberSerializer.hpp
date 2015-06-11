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

    string serialize(const T &value) const override;
};

// ----------------------------------------------------------------------------

template<class T>
string NumberSerializer<T>::serialize(const T &value) const
{
    std::stringstream out;

    out << std::to_string(value);

    return out.str();
}

} // namespace mapper

#endif // VALUESERIALIZER_H

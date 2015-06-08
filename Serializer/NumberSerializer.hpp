#ifndef VALUESERIALIZER_H
#define VALUESERIALIZER_H

#include "SerializerCommon.h"


template<class T>
class NumberSerializer : public ISerializer<T>
{
    friend class SerializerFactory;

    NumberSerializer() { }

public:
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

#endif // VALUESERIALIZER_H

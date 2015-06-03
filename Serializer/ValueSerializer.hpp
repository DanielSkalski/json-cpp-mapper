#ifndef VALUESERIALIZER_H
#define VALUESERIALIZER_H

#include "ISerializer.h"
#include <string>

template<class T>
class ValueSerializer : public ISerializer<T>
{
public:
    virtual ~ValueSerializer() { }

    string serialize(const T &value) const override;
};

// ----------------------------------------------------------------------------

template<class T>
string ValueSerializer<T>::serialize(const T &value) const
{
    std::stringstream out;

    out << std::to_string(value);

    return out.str();
}

#endif // VALUESERIALIZER_H

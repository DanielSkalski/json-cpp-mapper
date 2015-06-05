#ifndef VALUESERIALIZER_H
#define VALUESERIALIZER_H

#include "ISerializer.h"
#include <string>

template<class T>
class NumberSerializer : public ISerializer<T>
{
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

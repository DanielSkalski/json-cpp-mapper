#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <string>
#include "JsonStream.hpp"

using namespace std;

namespace mapper {

template<class T>
class ISerializer
{
public:
    virtual ~ISerializer() { }

    virtual JsonStream& serialize(const T& value, JsonStream& out) const = 0;
};

} // namespace mapper

#endif // ISERIALIZER_H

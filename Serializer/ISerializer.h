#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <string>

using namespace std;

namespace mapper {

template<class T>
class ISerializer
{
public:
    virtual ~ISerializer() { }

    virtual string serialize(const T& value) const = 0;
};

} // namespace mapper

#endif // ISERIALIZER_H

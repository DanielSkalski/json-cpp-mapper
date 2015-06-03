#ifndef ISERIALIZER_H
#define ISERIALIZER_H

#include <string>

using namespace std;

template<class T>
class ISerializer
{
public:
    virtual ~ISerializer() { }

    virtual string serialize(const T& value) const = 0;
};

#endif // ISERIALIZER_H

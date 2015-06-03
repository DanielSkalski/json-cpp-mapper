#ifndef STRINGSERIALIZER_H
#define STRINGSERIALIZER_H

#include "ISerializer.h"
#include <sstream>


class StringSerializer : public ISerializer<string>
{
public:
    virtual ~StringSerializer() { }

    string serialize(const string &value) const override;
};


// ----------------------------------------------------------------------------

string StringSerializer::serialize(const string &value) const
{
    std::stringstream out;

    out << "\"" << value << "\"";

    return out.str();
}

#endif // STRINGSERIALIZER_H

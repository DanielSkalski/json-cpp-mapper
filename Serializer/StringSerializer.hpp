#ifndef STRINGSERIALIZER_H
#define STRINGSERIALIZER_H

#include "SerializerCommon.h"


class StringSerializer : public ISerializer<string>
{
    friend class SerializerFactory;

    StringSerializer() { }

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

#ifndef STRINGSERIALIZER_H
#define STRINGSERIALIZER_H

#include "SerializerCommon.h"


class StringSerializer : public ISerializer<string>
{
    friend class SerializerFactory;
    struct private_ctor { };

    StringSerializer() { }

    static shared_ptr<StringSerializer> make_shared()
    {
        return std::make_shared<StringSerializer>(private_ctor());
    }

public:
    explicit StringSerializer(const private_ctor&) { }
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

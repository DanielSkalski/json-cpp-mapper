#ifndef STRINGSERIALIZER_H
#define STRINGSERIALIZER_H

#include "SerializerCommon.h"

namespace mapper {

class StringSerializer : public ISerializer<string>
{
    friend class SerializerFactory;
    struct private_ctor { };

    static shared_ptr<StringSerializer> make_shared()
    {
        return std::make_shared<StringSerializer>(private_ctor());
    }

public:
    explicit StringSerializer(const private_ctor&) { }
    virtual ~StringSerializer() { }

    JsonStream &serialize(const string &value, JsonStream& out) const override;
};


// ----------------------------------------------------------------------------

JsonStream& StringSerializer::serialize(const string &value, JsonStream &out) const
{
    out << "\"" << value << "\"";

    return out;
}

} // namespace mapper

#endif // STRINGSERIALIZER_H

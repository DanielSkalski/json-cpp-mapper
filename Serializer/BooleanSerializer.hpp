#ifndef BOOLEANSERIALIZER_H
#define BOOLEANSERIALIZER_H

#include "SerializerCommon.h"

namespace mapper {

class BooleanSerializer : public ISerializer<bool>
{
    friend class SerializerFactory;
    struct private_ctor { };

    static shared_ptr<BooleanSerializer> make_shared()
    {
        return std::make_shared<BooleanSerializer>(private_ctor());
    }

public:
    explicit BooleanSerializer(const private_ctor&) { }

    JsonStream& serialize(const bool &value, JsonStream& out) const override;
};

JsonStream &BooleanSerializer::serialize(const bool& value, JsonStream &out) const
{
    out << (value ? "true" : "false");

    return out;
}

} // namespace mapper

#endif // BOOLEANSERIALIZER_H

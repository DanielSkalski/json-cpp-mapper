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

    string serialize(const bool &value) const override;
};

string BooleanSerializer::serialize(const bool& value) const
{
    std::stringstream out;

    out << (value ? "true" : "false");

    return out.str();
}

} // namespace mapper

#endif // BOOLEANSERIALIZER_H

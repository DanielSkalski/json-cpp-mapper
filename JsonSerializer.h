#ifndef JSONSERIALIZER
#define JSONSERIALIZER

#include "Mapping.hpp"
#include "Serializer/ObjectSerializer.hpp"

namespace mapper {

#define MAPPER_GET_VALUE(T, RET)           [](const T& x) -> string  { return x.RET; }
#define MAPPER_GET_VALUE_BOOL(T, RET)      [](const T& x) -> bool    { return x.RET; }
#define MAPPER_GET_VALUE_OBJ(T, TRET, RET) [](const T& x) -> TRET    { return x.RET; }
#define MAPPER_GET_VALUE_INT(T, RET)       (function<int (const T&)>)  ([](const T& x) -> int   { return x.RET; })
#define MAPPER_GET_VALUE_FLOAT(T, RET)     (function<float (const T&)>)([](const T& x) -> float { return x.RET; })
#define MAPPER_GET_VALUE_(T, RET)          [](const T& x) -> string  { return to_string(x.RET); }

#define MAPPER_ARRAY_GET_COUNT(T, RET)     [](const T& x) -> int { return x.RET; }
#define MAPPER_GET_INDEXED_VALUE(T, RET)        [](const T& x, int index) -> string { return x.RET[index]; }
#define MAPPER_GET_INDEXED_VALUE_BOOL(T, RET)   [](const T& x, int index) -> bool   { return x.RET[index]; }
#define MAPPER_GET_INDEXED_VALUE_INT(T, RET)    ((function<int (const T&, int)>)  [](const T& x, int index) -> int   { return x.RET[index]; })
#define MAPPER_GET_INDEXED_VALUE_FLOAT(T, RET)  ((function<float (const T&, int)>)[](const T& x, int index) -> float { return x.RET[index]; })
#define MAPPER_GET_INDEXED_VALUE_OBJ(T, TRET, RET)   [](const T& x, int index) -> TRET   { return x.RET[index]; }

}

#endif // JSONSERIALIZER

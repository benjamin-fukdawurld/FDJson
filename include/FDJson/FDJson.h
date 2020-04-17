#ifndef FDJSON_H
#define FDJSON_H

#include <FDSerialize/SerializerBase.h>

namespace FDJson
{
    class JsonSerializerImpl;
    typedef FDSerialize::SerializerBase<JsonSerializerImpl> Serializer;
}

#endif // FDJSON_H

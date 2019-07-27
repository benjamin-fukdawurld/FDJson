#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <FDSerialize/SerializerBase.h>

#include <rapidjson/document.h>
#include "Json_utils.h"

namespace FDJson
{
    struct JsonSerializerImpl
    {
        typedef rapidjson::Value Value;

        template<typename T>
        static Value serialize(T &&obj)
        {
            return FDJson::serialize(std::forward<T>(obj));
        }

        template<typename T>
        static Value serialize(const T &obj)
        {
            return FDJson::serialize(obj);
        }

        template<typename T>
        static Value serialize(T obj[], size_t len)
        {
            return FDJson::serialize(obj, len);
        }

        template<typename T>
        static bool unserialize(const Value &val, T &out, std::string *err = nullptr)
        {
            return FDJson::unserialize(val, out, err);
        }

        template<typename T>
        static bool unserialize(const Value &val, T out[], size_t len, std::string *err = nullptr)
        {
            return FDJson::unserialize(val, out, len, err);
        }
    };

    typedef FDSerialize::SerializerBase<JsonSerializerImpl> Serializer;
}

#endif // JSONSERIALIZER_H

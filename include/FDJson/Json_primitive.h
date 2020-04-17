#ifndef JSON_PRIMITIVE_H
#define JSON_PRIMITIVE_H

#include <FDJson/Json_primitive_fwd.h>
#include <FDJson/JsonSerializer.h>

#include <rapidjson/document.h>

namespace FDJson
{
    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidjson::Value> serialize(const T &i, Serializer &)
    {
        return rapidjson::Value(i);
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value,
    bool> unserialize(const rapidjson::Value &val, T &i, Serializer &, std::string *err)
    {
        if(!val.IsInt())
        {
            if(err)
                *err = "Value is not an integer";

            return false;
        }

        i = static_cast<T>(val.GetInt());
        return true;
    }

    template<typename T>
    std::enable_if_t<std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value,
    bool> unserialize(const rapidjson::Value &val, T &i, Serializer &, std::string *err)
    {
        if(!val.IsUint())
        {
            if(err)
                *err = "Value is not an unsigned integer";

            return false;
        }

        i = static_cast<T>(val.GetUint());
        return true;
    }

    template<typename T>
    bool unserialize(const rapidjson::Value &val, std::optional<T> &opt, Serializer &tag, std::string *err)
    {
        if(val.IsNull())
        {
            opt = std::nullopt;
            return true;
        }

        return unserialize(val, opt.value(), tag, err);
    }
}

#endif // JSON_PRIMITIVE_H

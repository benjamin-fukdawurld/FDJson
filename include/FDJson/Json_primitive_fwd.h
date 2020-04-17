#ifndef JSON_PRIMITIVE_FWD_H
#define JSON_PRIMITIVE_FWD_H

#include <string>
#include <cstdint>
#include <type_traits>

#include <optional>

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

namespace FDJson
{
    template<typename T>
    bool unserialize(const rapidjson::Value &val, std::optional<T> &opt, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(std::nullptr_t, Serializer &serializer);

    rapidjson::Value serialize(const char c, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, char &c, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const char *c, Serializer &serializer);

    rapidjson::Value serialize(const std::string &c, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, std::string &str, Serializer &serializer, std::string *err = nullptr);

    rapidjson::Value serialize(const bool b, Serializer &serializer);

    rapidjson::Value serialize(const float f, Serializer &serializer);

    rapidjson::Value serialize(const double &d, Serializer &serializer);

    bool unserialize(const rapidjson::Value &val, bool &b, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidjson::Value> serialize(const T &i, Serializer &serializer);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value,
    bool> unserialize(const rapidjson::Value &val, T &i, Serializer &serializer, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, int64_t &i, Serializer &serializer, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value,
    bool> unserialize(const rapidjson::Value &val, T &i, Serializer &serializer, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, uint64_t &i, Serializer &serializer, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, float &f, Serializer &serializer, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, double &d, Serializer &serializer, std::string *err = nullptr);
}

#endif // JSON_PRIMITIVE_FWD_H

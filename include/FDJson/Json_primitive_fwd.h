#ifndef JSON_PRIMITIVE_FWD_H
#define JSON_PRIMITIVE_FWD_H

#include <string>
#include <cstdint>
#include <type_traits>

#include <optional>

#include <rapidjson/fwd.h>

namespace FDJson
{
    template<typename T>
    bool unserialize(const rapidjson::Value &val, std::optional<T> &opt, std::string *err = nullptr);

    rapidjson::Value serialize(std::nullptr_t);

    rapidjson::Value serialize(const char c);

    bool unserialize(const rapidjson::Value &val, char &c, std::string *err = nullptr);

    rapidjson::Value serialize(const char *c);

    rapidjson::Value serialize(std::string &&c);

    rapidjson::Value serialize(const std::string &c);

    bool unserialize(const rapidjson::Value &val, std::string &str, std::string *err = nullptr);

    rapidjson::Value serialize(const bool b);

    bool unserialize(const rapidjson::Value &val, bool &b, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidjson::Value> serialize(T &&i);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value
                         || std::is_same<T, int64_t>::value
                         || std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value
                         || std::is_same<T, uint64_t>::value,
    rapidjson::Value> serialize(const T &i);

    template<typename T>
    std::enable_if_t<std::is_same<T, int16_t>::value
                         || std::is_same<T, int32_t>::value,
    bool> unserialize(const rapidjson::Value &val, T &i, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, int64_t &i, std::string *err = nullptr);

    template<typename T>
    std::enable_if_t<std::is_same<T, uint16_t>::value
                         || std::is_same<T, uint32_t>::value,
    bool> unserialize(const rapidjson::Value &val, T &i, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, uint64_t &i, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, float &f, std::string *err = nullptr);

    bool unserialize(const rapidjson::Value &val, double &d, std::string *err = nullptr);
}

#endif // JSON_PRIMITIVE_FWD_H

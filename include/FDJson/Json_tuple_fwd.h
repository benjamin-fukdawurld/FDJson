#ifndef JSON_TUPLE_FWD_H
#define JSON_TUPLE_FWD_H

#include <tuple>
#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

namespace FDJson
{
    namespace internal
    {
        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, Serializer &serializer, rapidjson::Value &val);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, Serializer &serializer, rapidjson::Value &val);

        template<typename... Args>
        rapidjson::Value serialize_tuple(const std::tuple<Args...> &t, Serializer &serializer);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        bool> unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, Serializer &serializer, std::string *err = nullptr);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        bool> unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, Serializer &serializer, std::string *err = nullptr);
    }

    template<typename First, typename Second>
    rapidjson::Value serialize(const std::pair<First, Second> &p, Serializer &serializer);

    template<typename First, typename Second>
    bool unserialize(const rapidjson::Value &val, std::pair<First, Second> &p, Serializer &serializer, std::string *err = nullptr);

    template<typename ...Args>
    rapidjson::Value serialize(const std::tuple<Args...> &t, Serializer &serializer);

    template<typename ...Args>
    bool unserialize(const rapidjson::Value &val, std::tuple<Args...> &t, Serializer &serializer, std::string *err = nullptr);
}

#endif // JSON_TUPLE_FWD_H

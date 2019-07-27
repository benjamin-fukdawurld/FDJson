#ifndef JSON_TUPLE_FWD_H
#define JSON_TUPLE_FWD_H

#include <tuple>
#include <rapidjson/fwd.h>

namespace FDJson
{
    namespace internal
    {
        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, rapidjson::Value &val);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, rapidjson::Value &val);

        template<typename... Args>
        rapidjson::Value serialize_tuple(const std::tuple<Args...> &t);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        bool> unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, std::string *err = nullptr);

        template<std::size_t I = 0, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        bool> unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, std::string *err = nullptr);
    }

    template<typename First, typename Second>
    rapidjson::Value serialize(std::pair<First, Second> &&p);

    template<typename First, typename Second>
    rapidjson::Value serialize(const std::pair<First, Second> &p);

    template<typename First, typename Second>
    bool unserialize(const rapidjson::Value &val, std::pair<First, Second> &p, std::string *err = nullptr);

    template<typename ...Args>
    rapidjson::Value serialize(std::tuple<Args...> &&t);

    template<typename ...Args>
    rapidjson::Value serialize(const std::tuple<Args...> &t);

    template<typename ...Args>
    bool unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, std::string *err = nullptr);
}

#endif // JSON_TUPLE_FWD_H

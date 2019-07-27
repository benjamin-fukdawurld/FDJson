#ifndef JSON_TUPLE_H
#define JSON_TUPLE_H

#include <FDJson/Json_allocator.h>
#include <FDJson/Json_tuple_fwd.h>
#include <FDJson/Json_primitive.h>

#include <rapidjson/document.h>

namespace FDJson
{
    template<std::size_t I, typename... Args>
    std::enable_if_t<I == sizeof...(Args),
    void> internal::serialize_tuple(const std::tuple<Args...> &, rapidjson::Value &)
    {}

    template<std::size_t I, typename... Args>
    std::enable_if_t<I < sizeof...(Args),
    void> internal::serialize_tuple(const std::tuple<Args...> &t, rapidjson::Value &val)
    {
        val.PushBack(FDJson::serialize(std::get<I>(t)), Json_helper::allocator);
        return serialize_tuple<I + 1, Args...>(t, val);
    }

    template<typename... Args>
    rapidjson::Value internal::serialize_tuple(const std::tuple<Args...> &t)
    {
        rapidjson::Value val(rapidjson::kArrayType);

        serialize_tuple<0, Args...>(t, val);

        return val;
    }

    template<std::size_t I, typename... Args>
    std::enable_if_t<I == sizeof...(Args),
    bool> internal::unserialize_tuple(const rapidjson::Value &, std::tuple<Args...> &, std::string *)
    {
        return true;
    }

    template<std::size_t I, typename...Args>
    std::enable_if_t<I < sizeof...(Args),
    bool> internal::unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, std::string *err)
    {
        if(!val.IsArray())
        {
            if(err)
            {
                *err = "Value is not an array";
            }

            return false;
        }

        if(val.Size() != sizeof...(Args))
        {
            if(err)
            {
                *err = std::string("Value is not an array of size ") + std::to_string(sizeof...(Args));
            }

            return false;
        }

        return FDJson::unserialize(val[I], std::get<I>(t), err) && unserialize_tuple<I + 1, Args...>(val, t, err);
    }

    template<typename First, typename Second>
    rapidjson::Value serialize(std::pair<First, Second> &&p)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("first", FDJson::serialize(p.first), Json_helper::allocator);
        val.AddMember("second", FDJson::serialize(p.second), Json_helper::allocator);
        return val;
    }

    template<typename First, typename Second>
    rapidjson::Value serialize(const std::pair<First, Second> &p)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("first", FDJson::serialize(p.first), Json_helper::allocator);
        val.AddMember("second", FDJson::serialize(p.second), Json_helper::allocator);
        return val;
    }

    template<typename First, typename Second>
    bool unserialize(const rapidjson::Value &val, std::pair<First, Second> &p, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
            {
                *err = "Value is not an object";
            }

            return false;
        }

        if(!val.HasMember("first"))
        {
            if(err)
            {
                *err = "Value has no member named 'first'";
            }

            return false;
        }

        if(!val.HasMember("second"))
        {
            if(err)
            {
                *err = "Value has no member named 'second'";
            }

            return false;
        }

        return unserialize(val["first"], p.first, err) && unserialize(val["second"], p.second, err);
    }

    template<typename ...Args>
    rapidjson::Value serialize(std::tuple<Args...> &&t)
    {
        return internal::serialize_tuple(t);
    }

    template<typename ...Args>
    rapidjson::Value serialize(const std::tuple<Args...> &t)
    {
        return internal::serialize_tuple(t);
    }

    template<typename...Args>
    bool unserialize(const rapidjson::Value &val, std::tuple<Args...> &t, std::string *err)
    {
        return internal::unserialize_tuple(val, t, err);
    }
}

#endif // JSON_TUPLE_H

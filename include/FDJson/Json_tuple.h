#ifndef JSON_TUPLE_H
#define JSON_TUPLE_H

#include <FDJson/Json_tuple_fwd.h>
#include <FDJson/JsonSerializer.h>

#include <rapidjson/document.h>

namespace FDJson
{
    namespace internal
    {
        template<std::size_t I, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &, Serializer &, rapidjson::Value &)
        {}

        template<std::size_t I, typename... Args>
        std::enable_if_t<I < sizeof...(Args),
        void> serialize_tuple(const std::tuple<Args...> &t, Serializer &serializer, rapidjson::Value &val)
        {
            val.PushBack(FDJson::serialize(std::get<I>(t), serializer), serializer.getAllocator());
            serialize_tuple<I + 1, Args...>(t, serializer, val);
        }

        template<typename... Args>
        rapidjson::Value serialize_tuple(const std::tuple<Args...> &t, Serializer &serializer)
        {
            rapidjson::Value val(rapidjson::kArrayType);

            serialize_tuple<0, Args...>(t, serializer, val);

            return val;
        }

        template<std::size_t I, typename... Args>
        std::enable_if_t<I == sizeof...(Args),
        bool> unserialize_tuple(const rapidjson::Value &, std::tuple<Args...> &, Serializer &, std::string *)
        {
            return true;
        }

        template<std::size_t I, typename...Args>
        std::enable_if_t<I < sizeof...(Args),
        bool> unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, Serializer &serializer, std::string *err)
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

            return FDJson::unserialize(val[I], std::get<I>(t), serializer, err) && unserialize_tuple<I + 1, Args...>(val, t, serializer, err);
        }
    }

    template<typename First, typename Second>
    rapidjson::Value serialize(const std::pair<First, Second> &p, Serializer &serializer)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("first", FDJson::serialize(p.first, serializer), serializer.getAllocator());
        val.AddMember("second", FDJson::serialize(p.second, serializer), serializer.getAllocator());
        return val;
    }

    template<typename First, typename Second>
    bool unserialize(const rapidjson::Value &val, std::pair<First, Second> &p, Serializer &serializer, std::string *err)
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

        return unserialize(val["first"], p.first, serializer, err) && unserialize(val["second"], p.second, serializer, err);
    }

    template<typename ...Args>
    rapidjson::Value serialize(const std::tuple<Args...> &t, Serializer &serializer)
    {
        return internal::serialize_tuple(t, serializer);
    }

    template<typename...Args>
    bool unserialize(const rapidjson::Value &val, std::tuple<Args...> &t, Serializer &serializer, std::string *err)
    {
        return internal::unserialize_tuple(val, t, serializer, err);
    }
}

#endif // JSON_TUPLE_H

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
        void> serialize_tuple(const std::tuple<Args...> &t, Serializer &tag, rapidjson::Value &val)
        {
            val.PushBack(FDJson::serialize(std::get<I>(t), tag), FDJson::Serializer::getInstance().getAllocator());
            serialize_tuple<I + 1, Args...>(t, tag, val);
        }

        template<typename... Args>
        rapidjson::Value serialize_tuple(const std::tuple<Args...> &t, Serializer &tag)
        {
            rapidjson::Value val(rapidjson::kArrayType);

            serialize_tuple<0, Args...>(t, tag, val);

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
        bool> unserialize_tuple(const rapidjson::Value &val, std::tuple<Args...> &t, Serializer &tag, std::string *err)
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

            return FDJson::unserialize(val[I], std::get<I>(t), tag, err) && unserialize_tuple<I + 1, Args...>(val, t, tag, err);
        }
    }

    template<typename First, typename Second>
    rapidjson::Value serialize(const std::pair<First, Second> &p, Serializer &tag)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("first", FDJson::serialize(p.first, tag), FDJson::Serializer::getInstance().getAllocator());
        val.AddMember("second", FDJson::serialize(p.second, tag), FDJson::Serializer::getInstance().getAllocator());
        return val;
    }

    template<typename First, typename Second>
    bool unserialize(const rapidjson::Value &val, std::pair<First, Second> &p, Serializer &tag, std::string *err)
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

        return unserialize(val["first"], p.first, tag, err) && unserialize(val["second"], p.second, tag, err);
    }

    template<typename ...Args>
    rapidjson::Value serialize(const std::tuple<Args...> &t, Serializer &tag)
    {
        return internal::serialize_tuple(t, tag);
    }

    template<typename...Args>
    bool unserialize(const rapidjson::Value &val, std::tuple<Args...> &t, Serializer &tag, std::string *err)
    {
        return internal::unserialize_tuple(val, t, tag, err);
    }
}

#endif // JSON_TUPLE_H

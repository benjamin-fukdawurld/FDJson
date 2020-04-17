#ifndef JSON_LIST_H
#define JSON_LIST_H

#include <FDJson/Json_list_fwd.h>
#include <FDJson/JsonSerializer.h>

#include <rapidjson/document.h>

namespace FDJson
{
    namespace internal
    {
        template<typename T>
        rapidjson::Value serialize_list(const T &l, Serializer &tag)
        {
            rapidjson::Value v(rapidjson::kArrayType);
            for (auto it = l.begin(), end = l.end(); it != end; ++it)
                v.PushBack(FDJson::serialize(*it, tag), FDJson::Serializer::getInstance().getAllocator());
            return v;
        }
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Allocator> &l, Serializer &tag)
    {
        return internal::serialize_list(l, tag);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Allocator> &l, Serializer &tag, std::string *err)
    {
        if(!val.IsArray())
        {
            if(err)
            {
                *err = "Value is not an array";
            }

            return false;
        }

        for(auto it = val.Begin(), end = val.End(); it != end; ++it)
        {
            T tmp;
            if(!unserialize(*it, tmp, tag, err))
                return false;

            l.push_back(std::move(tmp));
        }

        return true;
    }

    template<typename T>
    rapidjson::Value serialize(const std::initializer_list<T> &l, Serializer &tag)
    {
        return internal::serialize_list(l, tag);
    }
}

#endif // JSON_LIST_H

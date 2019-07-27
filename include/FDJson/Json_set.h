#ifndef JSON_SET_H
#define JSON_SET_H

#include <FDJson/Json_allocator.h>
#include <FDJson/Json_set_fwd.h>

#include <rapidjson/document.h>

namespace FDJson
{
    template<typename T>
    rapidjson::Value internal::serialize_set(T &&s)
    {
        rapidjson::Value v(rapidjson::kArrayType);
        for (auto it = s.begin(), end = s.end(); it != end; ++it)
            v.PushBack(FDJson::serialize(*it), Json_helper::allocator);
        return v;
    }

    template<typename T>
    rapidjson::Value internal::serialize_set(const T &s)
    {
        rapidjson::Value v(rapidjson::kArrayType);
        for (auto it = s.begin(), end = s.end(); it != end; ++it)
            v.PushBack(FDJson::serialize(*it), Json_helper::allocator);
        return v;
    }

    template<typename T, typename ValueType>
    bool internal::unserialize_set(const rapidjson::Value &val, T &s, std::string *err)
    {
        if(!val.IsArray())
        {
            if(err)
                *err = "Value is not an array";

            return false;
        }

        for(auto it = val.Begin(), end = val.End(); it != end; ++it)
        {
            ValueType tmp;
            if(!unserialize(*it, tmp, err))
                return false;

            s.insert(tmp);
        }

        return true;
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    rapidjson::Value> serialize(Container<T, Compare, Allocator> &&s)
    {
        return internal::serialize_set(std::forward<Container<T, Compare, Allocator>>(s));
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Compare, Allocator> &s)
    {
        return internal::serialize_set(s);
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Compare, Allocator> &s, std::string *err)
    {
        return internal::unserialize_set(val, s, err);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    rapidjson::Value> serialize(Container<T, Hash, KeyEqual, Allocator> &&s)
    {
        return internal::serialize_set(std::forward<Container<T, Hash, KeyEqual, Allocator>>(s));
    }


    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Hash, KeyEqual, Allocator> &s)
    {
        return internal::serialize_set(s);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Hash, KeyEqual, Allocator> &s, std::string *err)
    {
        return internal::unserialize_set(val, s, err);
    }
}

#endif // JSON_SET_H

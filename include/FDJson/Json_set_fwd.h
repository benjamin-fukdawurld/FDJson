#ifndef JSON_SET_FWD_H
#define JSON_SET_FWD_H

#include <type_traits>

#include <set>
#include <unordered_set>

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

namespace FDJson
{
    namespace internal
    {
        template<typename T>
        rapidjson::Value serialize_set(const T &s, Serializer &serializer);

        template<typename T, typename ValueType = typename T::value_type>
        bool unserialize_set(const rapidjson::Value &val, T &s, Serializer &serializer, std::string *err);
    }

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare = std::less<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Compare, Allocator> &s, Serializer &serializer);

    template<template<typename, typename, typename> typename Container,
             typename T,
             typename Compare = std::less<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Compare, Allocator>, std::set<T, Compare, Allocator>>::value
                         || std::is_same<Container<T, Compare, Allocator>, std::multiset<T, Compare, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Compare, Allocator> &s, Serializer &serializer, std::string *err);

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash = std::hash<T>,
             typename KeyEqual = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Hash, KeyEqual, Allocator> &s, Serializer &serializer);

    template<template<typename, typename, typename, typename> typename Container,
             typename T,
             typename Hash = std::hash<T>,
             typename KeyEqual = std::equal_to<T>,
             typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_set<T, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<T, Hash, KeyEqual, Allocator>, std::unordered_multiset<T, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Hash, KeyEqual, Allocator> &s, Serializer &serializer, std::string *err);
}

#endif // JSON_SET_FWD_H

#ifndef JSON_LIST_FWD_H
#define JSON_LIST_FWD_H

#include <type_traits>

#include <list>
#include <forward_list>
#include <initializer_list>

#include <string>
#include <rapidjson/fwd.h>

namespace FDJson
{
    namespace internal
    {
        template<typename T>
        rapidjson::Value serialize_list(T &&l);

        template<typename T>
        rapidjson::Value serialize_list(const T &l);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    rapidjson::Value> serialize(Container<T, Allocator> &&l);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Allocator> &l);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::list<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::forward_list<T, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Allocator> &l, std::string *err);

    template<typename T>
    rapidjson::Value serialize(std::initializer_list<T> &&l);

    template<typename T>
    rapidjson::Value serialize(const std::initializer_list<T> &l);
}

#endif // JSON_LIST_FWD_H

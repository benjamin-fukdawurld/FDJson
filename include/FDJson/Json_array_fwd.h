#ifndef JSON_ARRAY_FWD_H
#define JSON_ARRAY_FWD_H

#include <array>
#include <vector>
#include <deque>

#include <rapidjson/fwd.h>

namespace FDJson
{
    namespace internal
    {
        template<size_t S>
        struct array_helper
        {
            template<typename T>
            static rapidjson::Value serialize(T &&arr);

            template<typename T>
            static rapidjson::Value serialize(const T &arr);

            template<typename T>
            static bool unserialize(const rapidjson::Value &val, T &arr, std::string *err = nullptr);
        };

        template<>
        struct array_helper<0>
        {
            template<typename T>
            static rapidjson::Value serialize(T &&arr, size_t len);

            template<typename T>
            static rapidjson::Value serialize(const T &arr, size_t len);

            template<typename T>
            static bool unserialize(const rapidjson::Value &val, T &arr, size_t len, std::string *err = nullptr);

            template<typename T>
            static bool unserialize(const rapidjson::Value &val, T &arr, std::string *err = nullptr);
        };
    }

    template<typename T>
    rapidjson::Value serialize(const T arr[], size_t len);

    template<typename T>
    bool unserialize(const rapidjson::Value &val, T arr[], size_t len, std::string *err = nullptr);

    template<typename T, size_t N>
    rapidjson::Value serialize(const T arr[]);

    template<typename T, size_t N>
    bool unserialize(const rapidjson::Value &val, T arr[], std::string *err = nullptr);

    template<typename T, size_t N>
    rapidjson::Value serialize(std::array<T, N> &&arr);

    template<typename T, size_t N>
    rapidjson::Value serialize(const std::array<T, N> &arr);

    template<typename T, size_t N>
    bool unserialize(const rapidjson::Value &val, std::array<T, N> &arr, std::string *err = nullptr);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    rapidjson::Value> serialize(Container<T, Allocator> &&arr);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Allocator> &arr);

    template<template<typename, typename> typename Container, typename T, typename Allocator = std::allocator<T>>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Allocator> &arr, std::string *err = nullptr);
}

#endif // JSON_ARRAY_FWD_H

#ifndef JSON_MAP_FWD_H
#define JSON_MAP_FWD_H

#include <type_traits>
#include <map>
#include <unordered_map>

#include <rapidjson/fwd.h>

#include <FDJson/FDJson.h>

namespace FDJson
{
    namespace internal
    {
        template<typename Key, typename Value>
        struct map_helper
        {
            template<typename Map>
            static rapidjson::Value serialize(const Map &m, Serializer &serializer);

            template<typename Map>
            static bool unserialize(const rapidjson::Value &val, Map &m, Serializer &serializer, std::string *err = nullptr);
        };

        template<typename Value>
        struct map_helper<std::string, Value>
        {
            template<typename Map>
            static rapidjson::Value serialize(const Map &m, Serializer &serializer);

            template<typename Map>
            static bool unserialize(const rapidjson::Value &val, Map &m, Serializer &serializer, std::string *err = nullptr);
        };
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare = std::less<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    rapidjson::Value> serialize(const Container<Key, Value, Compare, Allocator> &i, Serializer &serializer);

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare = std::less<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
                         || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<Key, Value, Compare, Allocator> &m, Serializer &serializer, std::string *err = nullptr);

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash = std::hash<Key>,
             typename KeyEqual = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    rapidjson::Value> serialize(const Container<Key, Value, Hash, KeyEqual, Allocator> &i, Serializer &serializer);

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash = std::hash<Key>,
             typename KeyEqual = std::equal_to<Key>,
             typename Allocator = std::allocator<std::pair<const Key, Value>>>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
                         || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<Key, Value, Hash, KeyEqual, Allocator> &m, Serializer &serializer, std::string *err = nullptr);
}

#endif // JSON_MAP_FWD_H

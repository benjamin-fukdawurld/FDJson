#ifndef JSON_MAP_H
#define JSON_MAP_H

#include <FDJson/Json_allocator.h>
#include <FDJson/Json_primitive_fwd.h>
#include <FDJson/Json_map_fwd.h>

#include <rapidjson/document.h>

namespace FDJson
{
    template<typename Key, typename Value>
    template<typename Map>
    rapidjson::Value internal::map_helper<Key, Value>::serialize(Map &&m)
    {
        rapidjson::Value result(rapidjson::kArrayType);
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            rapidjson::Value item(rapidjson::kObjectType);
            rapidjson::Value key = serialize(it->first);
            rapidjson::Value value = serialize(it->second);
            item.AddMember("key", key, Json_helper::allocator);
            item.AddMember("value", value, Json_helper::allocator);
            result.PushBack(item, Json_helper::allocator);
        }
        return result;
    }


    template<typename Key, typename Value>
    template<typename Map>
    rapidjson::Value internal::map_helper<Key, Value>::serialize(const Map &m)
    {
        rapidjson::Value result(rapidjson::kArrayType);
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            rapidjson::Value item(rapidjson::kObjectType);
            rapidjson::Value key = FDJson::serialize(it->first);
            rapidjson::Value value = FDJson::serialize(it->second);
            item.AddMember("key", key, Json_helper::allocator);
            item.AddMember("value", value, Json_helper::allocator);
            result.PushBack(item, Json_helper::allocator);
        }
        return result;
    }

    template<typename  Key, typename Value>
    template<typename Map>
    bool internal::map_helper<Key, Value>::unserialize(const rapidjson::Value &val, Map &m, std::string *err)
    {
        if(!val.IsArray())
        {
            if(err)
                *err = "Value is not an array";

            return false;
        }

        for(auto it = val.Begin(), end = val.End(); it != end; ++it)
        {
            if(!it->HasMember("key"))
            {
                if(err)
                    *err = "Value has no member 'key'";

                return false;
            }

            if(!it->HasMember("value"))
            {
                if(err)
                    *err = "Value has no member 'value'";

                return false;
            }

            Key k;
            Value v;
            if(!FDJson::unserialize((*it)["key"], k, err) || !FDJson::unserialize((*it)["value"], v, err))
                return false;

            m.emplace(k, v);
        }

        return true;
    }

    template<typename Value>
    template<typename Map>
    rapidjson::Value internal::map_helper<std::string, Value>::serialize(Map &&m)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            result.AddMember(rapidjson::StringRef(it->first.c_str(), it->first.size()), FDJson::serialize(it->second), Json_helper::allocator);
        }

        return result;
    }

    template<typename Value>
    template<typename Map>
    rapidjson::Value internal::map_helper<std::string, Value>::serialize(const Map &m)
    {
        rapidjson::Value result(rapidjson::kObjectType);
        for(auto it = m.begin(), end = m.end(); it != end; ++it)
        {
            result.AddMember(rapidjson::StringRef(it->first.c_str(), it->first.size()), FDJson::serialize(it->second), Json_helper::allocator);
        }

        return result;
    }

    template<typename Value>
    template<typename Map>
    bool internal::map_helper<std::string, Value>::unserialize(const rapidjson::Value &val, Map &m, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "Value is not an object";

            return false;
        }

        for(auto it = val.MemberBegin(), end = val.MemberEnd(); it != end; ++it)
        {
            Value v;
            if(!FDJson::unserialize(it->value, v, err))
                return false;

            m.emplace(it->name.GetString(), v);
        }

        return true;
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
    || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    rapidjson::Value> serialize(Container<Key, Value, Compare, Allocator> &&m)
    {
        return internal::map_helper<Key, Value>::serialize(std::forward<Container<Key, Value, Compare, Allocator>>(m));
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
    || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    rapidjson::Value> serialize(const Container<Key, Value, Compare, Allocator> &m)
    {
        return internal::map_helper<Key, Value>::serialize(m);
    }

    template<template<typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Compare,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Compare, Allocator>, std::map<Key, Value, Compare, Allocator>>::value
    || std::is_same<Container<Key, Value, Compare, Allocator>, std::multimap<Key, Value, Compare, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<Key, Value, Compare, Allocator> &m, std::string *err)
    {
        return internal::map_helper<Key, Value>::unserialize(val, m, err);
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
    || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    rapidjson::Value> serialize(Container<Key, Value, Hash, KeyEqual, Allocator> &&m)
    {
        return internal::map_helper<Key, Value>::serialize(std::forward<Container<Key, Value, Hash, KeyEqual, Allocator>>(m));
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
    || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    rapidjson::Value> serialize(const Container<Key, Value, Hash, KeyEqual, Allocator> &m)
    {
        return internal::map_helper<Key, Value>::serialize(m);
    }

    template<template<typename, typename, typename, typename, typename> typename Container,
             typename Key,
             typename Value,
             typename Hash,
             typename KeyEqual,
             typename Allocator>
    std::enable_if_t<std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>>::value
    || std::is_same<Container<Key, Value, Hash, KeyEqual, Allocator>, std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<Key, Value, Hash, KeyEqual, Allocator> &m, std::string *err)
    {
        return internal::map_helper<Key, Value>::unserialize(val, m, err);
    }
}

#endif // JSON_MAP_H

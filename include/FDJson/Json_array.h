#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <FDJson/Json_array_fwd.h>
#include <FDJson/JsonSerializer.h>

#include <rapidjson/document.h>
#include <sstream>

namespace FDJson
{
    template<size_t S>
    template<typename T>
    rapidjson::Value internal::array_helper<S>::serialize(const T &arr, Serializer &serializer)
    {
        rapidjson::Value v(rapidjson::kArrayType);
        for (size_t i = 0; i < S; ++i)
            v.PushBack(FDJson::serialize(arr[i], serializer), serializer.getAllocator());
        return v;
    }

    template<size_t S>
    template<typename T>
    bool internal::array_helper<S>::unserialize(const rapidjson::Value &val, T &arr, Serializer &serializer, std::string *err)
    {
        if(!val.IsArray())
        {
            if(err)
                *err = "Value is not an array";
            return false;
        }

        if(val.Size() != S)
        {
            if(err)
            {
                std::ostringstream oss;
                oss << "Value array size is " << val.Size() << " while " << S << " elements was expected";
                *err = oss.str();
            }
            return false;
        }

        for(size_t i = 0, i_max = S; i < i_max; ++i)
        {
            if(!FDJson::unserialize(val[i], arr[i], serializer, err))
                return false;
        }

        return true;
    }

    template<typename T>
    rapidjson::Value internal::array_helper<0>::serialize(const T &arr, size_t len, Serializer &serializer)
    {
        rapidjson::Value v(rapidjson::kArrayType);
        for (size_t i = 0; i < len; ++i)
            v.PushBack(FDJson::serialize(arr[i], serializer), serializer.getAllocator());
        return v;
    }

    template<typename T>
    bool internal::array_helper<0>::unserialize(const rapidjson::Value &val, T &arr, size_t len, Serializer &serializer, std::string *err)
    {
        if(!val.IsArray())
        {
            if(err)
                *err = "Value is not an array";
            return false;
        }

        if(val.Size() != len)
        {
            if(err)
            {
                std::ostringstream oss;
                oss << "Value array size is " << val.Size() << " while " << len << " elements was expected";
                *err = oss.str();
            }
            return false;
        }

        for(size_t i = 0, i_max = len; i < i_max; ++i)
        {
            if(!FDJson::unserialize(val[i], arr[i], serializer, err))
                return false;
        }

        return true;
    }


    template<typename T>
    bool internal::array_helper<0>::unserialize(const rapidjson::Value &val, T &arr, Serializer &serializer, std::string *err)
    {
        if(!val.IsArray())
        {
            if(err)
                *err = "Value is not an array";
            return false;
        }

        for(size_t i = 0, i_max = val.Size(); i < i_max; ++i)
        {
            typename T::value_type tmp;
            if(!FDJson::unserialize(val[i], tmp, serializer, err))
                return false;

            arr.push_back(std::move(tmp));
        }

        return true;
    }


    template<typename T>
    rapidjson::Value serialize(const T arr[], size_t len, Serializer &serializer)
    {
        return internal::array_helper<0>::serialize(arr, len, serializer);
    }

    template<typename T>
    bool unserialize(const rapidjson::Value &val, T arr[], size_t len, Serializer &serializer, std::string *err)
    {
        return internal::array_helper<0>::unserialize(val, arr, len, serializer, err);
    }

    template<typename T, size_t N>
    rapidjson::Value serialize(const T arr[], Serializer &serializer)
    {
        return internal::array_helper<N>::serialize(arr, serializer);
    }

    template<typename T, size_t N>
    bool unserialize(const rapidjson::Value &val, T arr[], Serializer &serializer, std::string *err)
    {
        return internal::array_helper<N>::unserialize(val, arr, serializer, err);
    }

    template<typename T, size_t N>
    rapidjson::Value serialize(const std::array<T, N> &arr, Serializer &serializer)
    {
        return internal::array_helper<N>::serialize(arr, serializer);
    }

    template<typename T, size_t N>
    bool unserialize(const rapidjson::Value &val, std::array<T, N> &arr, Serializer &serializer, std::string *err)
    {
        return internal::array_helper<N>::unserialize(val, arr, serializer, err);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    rapidjson::Value> serialize(const Container<T, Allocator> &arr, Serializer &serializer)
    {
        return internal::array_helper<0>::serialize(arr, arr.size(), serializer);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    bool> unserialize(const rapidjson::Value &val, Container<T, Allocator> &arr, Serializer &serializer, std::string *err)
    {
        return internal::array_helper<0>::unserialize(val, arr, serializer, err);
    }
}

#endif // JSON_ARRAY_H

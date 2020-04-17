#ifndef FDJSON_TEST_MAP_H
#define FDJSON_TEST_MAP_H

#include <gtest/gtest.h>

#include <FDJson/Json_fwd.h>
#include <FDJson/Json_map.h>
#include <FDJson/JsonSerializer.h>

TEST(TestJsonMap, TestSerializeMap)
{
    FDJson::Serializer serializer;
    {
        std::map<int, int> m = {{0, 4}, {1, 3}, {2, 2}, {3, 1}, {4, 0}};
        FDJson::Serializer::Value val = serializer.serialize(m);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), m.size());
        for(auto it = val.Begin(), end = val.End(); it != end; ++it)
        {
            ASSERT_TRUE(it->IsObject());
            ASSERT_TRUE(it->HasMember("key"));
            ASSERT_TRUE(it->HasMember("value"));
            ASSERT_TRUE((*it)["key"].IsInt());
            ASSERT_TRUE((*it)["value"].IsInt());
            auto key_it = m.find((*it)["key"].GetInt());
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(key_it->second, (*it)["value"].GetInt());
        }
    }

    {
        std::map<std::string, int> m = {{"fezgve", 4}, {"vzseg", 3}, {"fzsgfrze", 2}, {"3zbverza", 1}};
        FDJson::Serializer::Value val = serializer.serialize(m);
        ASSERT_TRUE(val.IsObject());
        for(auto it = val.MemberBegin(), end = val.MemberEnd(); it != end; ++it)
        {
            ASSERT_TRUE(it->name.IsString());
            ASSERT_TRUE(it->value.IsInt());
            auto key_it = m.find(it->name.GetString());
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(key_it->second, it->value.GetInt());
        }
    }
}

TEST(TestJsonMap, TestUnserializeMap)
{
    FDJson::Serializer serializer;
    {
        const std::map<int, int> in = {{0, 4}, {1, 3}, {2, 2}, {3, 1}, {4, 0}};
        std::map<int, int> m;
        FDJson::Serializer::Value val(rapidjson::kArrayType);
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            FDJson::Serializer::Value cell(rapidjson::kObjectType);
            cell.AddMember("key", FDJson::Serializer::Value(it->first), serializer.getAllocator());
            cell.AddMember("value", FDJson::Serializer::Value(it->second), serializer.getAllocator());
            val.PushBack(cell, serializer.getAllocator());
        }

        std::string err;
        ASSERT_TRUE(serializer.unserialize(val, m, &err));
        ASSERT_EQ(in.size(), m.size());
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            auto key_it = m.find(it->first);
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(key_it->second, it->second);
        }
    }

    {
        const std::map<std::string, int> in = {{"fezgve", 4}, {"vzseg", 3}, {"fzsgfrze", 2}, {"3zbverza", 1}};
        std::map<std::string, int> m;
        FDJson::Serializer::Value val(rapidjson::kObjectType);
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            val.AddMember(FDJson::Serializer::Value(it->first.c_str(), serializer.getAllocator()),
                          FDJson::Serializer::Value(it->second), serializer.getAllocator());
        }
        std::string err;

        ASSERT_TRUE(serializer.unserialize(val, m, &err));
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            auto key_it = m.find(it->first);
            ASSERT_NE(key_it, m.end());
            ASSERT_EQ(key_it->second, it->second);
        }
    }
}

#endif // FDJSON_TEST_MAP_H

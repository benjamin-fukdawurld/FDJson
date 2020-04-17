#ifndef FDJSON_TEST_SET_H
#define FDJSON_TEST_SET_H

#include <gtest/gtest.h>

#include <FDJson/Json_fwd.h>
#include <FDJson/Json_primitive.h>
#include <FDJson/Json_set.h>
#include <FDJson/JsonSerializer.h>

TEST(TestJsonSet, TestSerializeSet)
{
    {
        const std::unordered_set<int> s = {0, 1, 2, 3};
        FDJson::Serializer::Value val = FDJson::Serializer::getInstance().serialize(s);

        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), s.size());
        for(auto it = val.Begin(), end = val.End(); it != end; ++it)
        {
            ASSERT_TRUE(it->IsInt());
            ASSERT_TRUE(s.find(it->GetInt()) != s.end());
        }

    }

    {
        const std::set<std::string> s = {"faubaf", "azfaezf", "000000", ""};
        FDJson::Serializer::Value val = FDJson::Serializer::getInstance().serialize(s);

        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), s.size());
        for(auto it = val.Begin(), end = val.End(); it != end; ++it)
        {
            ASSERT_TRUE(it->IsString());
            ASSERT_TRUE(s.find(it->GetString()) != s.end());
        }
    }
}

TEST(TestJsonSet, TestUnserializeSet)
{
    {
        const std::unordered_set<int> in = {0, 1, 2, 3};
        FDJson::Serializer::Value val = FDJson::Serializer::getInstance().serialize(in);
        std::unordered_set<int> s;
        std::string err;

        ASSERT_TRUE(FDJson::Serializer::getInstance().unserialize(val, s, &err)) << err;
        for(int i = 0, i_max = 4; i < i_max; ++i)
        {
            ASSERT_TRUE(s.find(i) != s.end());
        }
    }

    {
        const std::set<std::string> in = {"faubaf", "azfaezf", "000000", ""};
        FDJson::Serializer::Value val = FDJson::Serializer::getInstance().serialize(in);
        std::unordered_set<std::string> s;
        std::string err;

        ASSERT_TRUE(FDJson::Serializer::getInstance().unserialize(val, s, &err)) << err;
        for(auto it = in.begin(), end = in.end(); it != end; ++it)
        {
            ASSERT_TRUE(s.find(*it) != s.end());
        }
    }
}

#endif // FDJSON_TEST_SET_H

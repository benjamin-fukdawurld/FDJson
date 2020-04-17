#ifndef FDJSON_TEST_LIST_H
#define FDJSON_TEST_LIST_H

#include <gtest/gtest.h>

#include <FDJson/Json_primitive.h>
#include <FDJson/Json_list.h>
#include <FDJson/JsonSerializer.h>

TEST(TestJsonList, TestSerializeList)
{
    FDJson::Serializer serializer;
    { // std::vector of int
        std::list<int> l = {0, 1, 2, 3};
        FDJson::Serializer::Value val = serializer.serialize(l);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 4u);
        auto it = l.begin();
        for(rapidjson::SizeType i = 0, i_max = 4; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].IsInt());
            EXPECT_EQ(val[i].GetInt(), *it);
        }
    }

    { // std::deque of string
        std::forward_list<std::string> l = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDJson::Serializer::Value val = serializer.serialize(l);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 6u);
        auto it = l.begin();
        for(rapidjson::SizeType i = 0, i_max = 6; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].IsString());
            EXPECT_STREQ(val[i].GetString(), it->c_str());
        }
    }
}

TEST(TestJsonList, TestUnserializeList)
{
    FDJson::Serializer serializer;
    { // std::vector of int
        std::list<int> l;
        FDJson::Serializer::Value val = serializer.serialize(std::initializer_list<int>{0, 1, 2, 3});
        std::string err;
        ASSERT_TRUE(serializer.unserialize(val, l, &err)) << err;
        ASSERT_EQ(l.size(), 4u);
        auto it = l.begin();
        for(rapidjson::SizeType i = 0, i_max = 4; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].IsInt());
            EXPECT_EQ(val[i].GetInt(), *it);
        }
    }

    { // std::deque of string
        std::forward_list<std::string> l = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDJson::Serializer::Value val = serializer.serialize(l);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 6u);
        auto it = l.begin();
        for(rapidjson::SizeType i = 0, i_max = 6; i < i_max; ++i, ++it)
        {
            ASSERT_TRUE(val[i].IsString());
            EXPECT_STREQ(val[i].GetString(), it->c_str());
        }
    }
}

#endif // FDJSON_TEST_LIST_H

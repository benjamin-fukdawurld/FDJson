#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include <gtest/gtest.h>

#include <FDJson/Json_primitive.h>
#include <FDJson/Json_array.h>
#include <FDJson/JsonSerializer.h>

TEST(TestArray, TestSerializeStaticArray)
{
    { // int[]
        int t[4] = {0, 1, 2, 3};
        FDJson::Serializer::Value val = FDJson::Serializer::serialize(t, 4);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 4u);
        for(rapidjson::SizeType i = 0, i_max = 4; i < i_max; ++i)
        {
            ASSERT_TRUE(val[i].IsInt());
            EXPECT_EQ(val[i].GetInt(), t[i]);
        }
    }

    { // std::array of string
        std::array<std::string, 6> t = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDJson::Serializer::Value val = FDJson::Serializer::serialize(t);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 6u);
        for(rapidjson::SizeType i = 0, i_max = 6; i < i_max; ++i)
        {
            ASSERT_TRUE(val[i].IsString());
            EXPECT_EQ(val[i].GetString(), t[i].c_str());
        }
    }
}

TEST(TestArray, TestUnserializeStaticArray)
{
    { // int[]
        int t[4];
        FDJson::Serializer::Value val(rapidjson::kArrayType);
        val.PushBack(rapidjson::Value(0), FDJson::Json_helper::allocator);
        val.PushBack(rapidjson::Value(1), FDJson::Json_helper::allocator);
        val.PushBack(rapidjson::Value(2), FDJson::Json_helper::allocator);
        val.PushBack(rapidjson::Value(3), FDJson::Json_helper::allocator);
        std::string err;
        ASSERT_TRUE(FDJson::Serializer::unserialize(val, t, 4, &err)) << err;
        for(int i = 0, i_max = 4; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], i);
        }
    }

    { // std::array of string
        const std::array<std::string, 6> in = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        std::array<std::string, 6> t;
        FDJson::Serializer::Value val(rapidjson::kArrayType);
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
            val.PushBack(FDJson::Serializer::Value(in[i].c_str(), FDJson::Json_helper::allocator), FDJson::Json_helper::allocator);

        std::string err;
        ASSERT_TRUE(FDJson::Serializer::unserialize(val, t, &err)) << err;
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], in[i]);
        }
    }
}


TEST(TestArray, TestSerializeDynamicArray)
{
    { // std::vector of int
        std::vector<int> v = {0, 1, 2, 3};
        FDJson::Serializer::Value val = FDJson::Serializer::serialize(v);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 4u);
        for(rapidjson::SizeType i = 0, i_max = 4; i < i_max; ++i)
        {
            ASSERT_TRUE(val[i].IsInt());
            EXPECT_EQ(val[i].GetInt(), v[i]);
        }
    }

    { // std::deque of string
        std::deque<std::string> d = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        FDJson::Serializer::Value val = FDJson::Serializer::serialize(d);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 6u);
        for(rapidjson::SizeType i = 0, i_max = 6; i < i_max; ++i)
        {
            ASSERT_TRUE(val[i].IsString());
            EXPECT_EQ(val[i].GetString(), d[i].c_str());
        }
    }
}

TEST(TestArray, TestUnserializeDynamicArray)
{
    { // std::vector of int
        int t[4];
        FDJson::Serializer::Value val(rapidjson::kArrayType);
        val.PushBack(rapidjson::Value(0), FDJson::Json_helper::allocator);
        val.PushBack(rapidjson::Value(1), FDJson::Json_helper::allocator);
        val.PushBack(rapidjson::Value(2), FDJson::Json_helper::allocator);
        val.PushBack(rapidjson::Value(3), FDJson::Json_helper::allocator);
        std::string err;
        ASSERT_TRUE(FDJson::Serializer::unserialize(val, t, 4, &err)) << err;
        for(int i = 0, i_max = 4; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], i);
        }
    }

    { // std::deque of string
        const std::array<std::string, 6> in = {"", "1", "zafaezf", "fabzf\n", "kpkp", "pjpij"};
        std::deque<std::string> t;
        FDJson::Serializer::Value val(rapidjson::kArrayType);
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
            val.PushBack(FDJson::Serializer::Value(in[i].c_str(), FDJson::Json_helper::allocator), FDJson::Json_helper::allocator);

        std::string err;
        ASSERT_TRUE(FDJson::Serializer::unserialize(val, t, &err)) << err;
        for(size_t i = 0, i_max = 6; i < i_max; ++i)
        {
            EXPECT_EQ(t[i], in[i]);
        }
    }
}

#endif // TEST_ARRAY_H

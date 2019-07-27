#ifndef TEST_TUPLE_H
#define TEST_TUPLE_H


#include <gtest/gtest.h>

#include <FDJson/Json_primitive.h>
#include <FDJson/Json_tuple.h>
#include <FDJson/JsonSerializer.h>

TEST(TestTuple, TestSerializeTuple)
{
    {
        std::tuple<int, float, std::string> t = std::make_tuple(1, 3.14f, "test");
        FDJson::Serializer::Value val = FDJson::Serializer::serialize(t);
        ASSERT_TRUE(val.IsArray());
        ASSERT_EQ(val.Size(), 3u);
        EXPECT_TRUE(val[0].IsInt());
        EXPECT_EQ(val[0].GetInt(), std::get<0>(t));
        EXPECT_TRUE(val[1].IsFloat());
        EXPECT_EQ(val[1].GetFloat(), std::get<1>(t));
        EXPECT_TRUE(val[2].IsString());
        EXPECT_STREQ(val[2].GetString(), std::get<2>(t).c_str());
    }
}

TEST(TestTuple, TestSerializePair)
{
    {
        std::pair<int, std::string> p = std::make_pair(1, "test");
        FDJson::Serializer::Value val = FDJson::Serializer::serialize(p);
        ASSERT_TRUE(val.IsObject());
        ASSERT_TRUE(val.HasMember("first"));
        EXPECT_TRUE(val["first"].IsInt());
        EXPECT_EQ(val["first"].GetInt(), p.first);
        ASSERT_TRUE(val.HasMember("second"));
        EXPECT_TRUE(val["second"].IsString());
        EXPECT_STREQ(val["second"].GetString(), p.second.c_str());
    }
}

TEST(TestTuple, TestUnserializepair)
{
    {
        std::pair<int, std::string> in = std::make_pair(1, "test");
        std::pair<int, std::string> t;
        FDJson::Serializer::Value val(rapidjson::kObjectType);
        val.AddMember("first", FDJson::Serializer::Value(in.first), FDJson::Json_helper::allocator);
        val.AddMember("second", FDJson::Serializer::Value(in.second.c_str(), FDJson::Json_helper::allocator), FDJson::Json_helper::allocator);
        std::string err;
        ASSERT_TRUE(FDJson::Serializer::unserialize(val, t, &err)) << err;
        for(size_t i = 0, i_max = 3; i < i_max; ++i)
        {
            EXPECT_EQ(std::get<0>(t), std::get<0>(t));
        }
    }
}

TEST(TestTuple, TestUnserializeTuple)
{
    {
        std::tuple<int, float, std::string> in = std::make_tuple(1, 3.14f, "test");
        std::tuple<int, float, std::string> t;
        FDJson::Serializer::Value val(rapidjson::kArrayType);
        val.PushBack(FDJson::Serializer::Value(std::get<0>(in)), FDJson::Json_helper::allocator);
        val.PushBack(FDJson::Serializer::Value(std::get<1>(in)), FDJson::Json_helper::allocator);
        val.PushBack(FDJson::Serializer::Value(std::get<2>(in).c_str(), FDJson::Json_helper::allocator), FDJson::Json_helper::allocator);
        std::string err;
        ASSERT_TRUE(FDJson::Serializer::unserialize(val, t, &err)) << err;
        for(size_t i = 0, i_max = 3; i < i_max; ++i)
        {
            EXPECT_EQ(std::get<0>(t), std::get<0>(t));
        }
    }
}

#endif // TEST_TUPLE_H

#ifndef FDJSON_TEST_TUPLE_H
#define FDJSON_TEST_TUPLE_H


#include <gtest/gtest.h>

#include <FDJson/Json_tuple.h>
#include <FDJson/JsonSerializer.h>

TEST(TestJsonTuple, TestSerializeTuple)
{
    {
        std::tuple<int, float, std::string> t = std::make_tuple(1, 3.14f, "test");
        FDJson::Serializer::Value val = FDJson::Serializer::getInstance().serialize(t);
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

TEST(TestJsonTuple, TestSerializePair)
{
    {
        std::pair<int, std::string> p = std::make_pair(1, "test");
        FDJson::Serializer::Value val = FDJson::Serializer::getInstance().serialize(p);
        ASSERT_TRUE(val.IsObject());
        ASSERT_TRUE(val.HasMember("first"));
        EXPECT_TRUE(val["first"].IsInt());
        EXPECT_EQ(val["first"].GetInt(), p.first);
        ASSERT_TRUE(val.HasMember("second"));
        EXPECT_TRUE(val["second"].IsString());
        EXPECT_STREQ(val["second"].GetString(), p.second.c_str());
    }
}

TEST(TestJsonTuple, TestUnserializePair)
{
    {
        std::pair<int, std::string> in = std::make_pair(1, "test");
        std::pair<int, std::string> t;
        FDJson::Serializer::Value val(rapidjson::kObjectType);
        val.AddMember("first", FDJson::Serializer::Value(in.first), FDJson::Serializer::getInstance().getAllocator());
        val.AddMember("second", FDJson::Serializer::Value(in.second.c_str(), FDJson::Serializer::getInstance().getAllocator()), FDJson::Serializer::getInstance().getAllocator());
        std::string err;
        ASSERT_TRUE(FDJson::Serializer::getInstance().unserialize(val, t, &err)) << err;
        EXPECT_EQ(t.first, in.first);
        EXPECT_EQ(t.second, in.second);
    }
}

TEST(TestJsonTuple, TestUnserializeTuple)
{
    {
        std::tuple<int, float, std::string> in = std::make_tuple(1, 3.14f, "test");
        std::tuple<int, float, std::string> t;
        FDJson::Serializer::Value val(rapidjson::kArrayType);
        val.PushBack(FDJson::Serializer::Value(std::get<0>(in)), FDJson::Serializer::getInstance().getAllocator());
        val.PushBack(FDJson::Serializer::Value(std::get<1>(in)), FDJson::Serializer::getInstance().getAllocator());
        val.PushBack(FDJson::Serializer::Value(std::get<2>(in).c_str(), FDJson::Serializer::getInstance().getAllocator()), FDJson::Serializer::getInstance().getAllocator());
        std::string err;
        ASSERT_TRUE(FDJson::Serializer::getInstance().unserialize(val, t, &err)) << err;
        EXPECT_EQ(std::get<0>(t), std::get<0>(in));
        EXPECT_EQ(std::get<1>(t), std::get<1>(in));
        EXPECT_EQ(std::get<2>(t), std::get<2>(in));
    }
}

#endif // FDJSON_TEST_TUPLE_H

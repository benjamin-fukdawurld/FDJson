#ifndef FDJSON_TEST_PRIMITIVE_H
#define FDJSON_TEST_PRIMITIVE_H

#include <gtest/gtest.h>

#include <FDJson/Json_primitive.h>
#include <FDJson/JsonSerializer.h>

#include <FDJson/FDJson.h>

TEST(TestJsonPrimitive, TestSerializeText)
{
    FDJson::Serializer serializer;
    { // Char
        char c = 'A';
        FDJson::Serializer::Value val = serializer.serialize(c);
        ASSERT_TRUE(val.IsString());
        EXPECT_EQ(val.GetStringLength(), 1u);
        EXPECT_STREQ(val.GetString(), "A");
    }

    { // C String
        const char *cstr = "this is a text string";
        size_t len = strlen(cstr);
        FDJson::Serializer::Value val = serializer.serialize(cstr);
        ASSERT_TRUE(val.IsString());
        EXPECT_EQ(val.GetStringLength(), len);
        EXPECT_STREQ(val.GetString(), cstr);
    }

    { // String
        std::string str = "this is a text string";
        FDJson::Serializer::Value val = serializer.serialize(str);
        ASSERT_TRUE(val.IsString());
        EXPECT_EQ(val.GetStringLength(), str.size());
        EXPECT_STREQ(val.GetString(), str.c_str());
    }
}

TEST(TestJsonPrimitive, TestUnserializeText)
{
    FDJson::Serializer serializer;
    { // Char
        char c = '\0';
        FDJson::Serializer::Value val("A", 1u, serializer.getAllocator());
        std::string err;
        ASSERT_TRUE(serializer.unserialize(val, c, &err)) << err;
        ASSERT_EQ(val.GetStringLength(), 1u);
        ASSERT_EQ('A', c);
    }

    { // String
        const char *in = "test string";
        std::string str;
        FDJson::Serializer::Value val(in, serializer.getAllocator());
        std::string err;
        ASSERT_TRUE(serializer.unserialize(val, str, &err)) << err;
        ASSERT_EQ(strlen(in), str.size());
        ASSERT_STREQ(in, str.c_str());
    }
}

TEST(TestJsonPrimitive, TestSerializeBoolean)
{
    FDJson::Serializer serializer;
    bool b = true;
    FDJson::Serializer::Value val = serializer.serialize(b);
    ASSERT_TRUE(val.IsBool());
    EXPECT_EQ(b, val.GetBool());
}

TEST(TestJsonPrimitive, TestUnserializeBoolean)
{
    FDJson::Serializer serializer;
    bool b;
    FDJson::Serializer::Value val = serializer.serialize(true);
    std::string err;
    ASSERT_TRUE(serializer.unserialize(val, b, &err)) << err;
    ASSERT_EQ(b, true);
}

TEST(TestJsonPrimitive, TestSerializeInteger)
{
    FDJson::Serializer serializer;
    { // Int 16 & Uint 16
        {
            int16_t i = -1564;
            FDJson::Serializer::Value val = serializer.serialize(i);
            ASSERT_TRUE(val.IsInt());
            EXPECT_EQ(i, val.GetInt());
        }

        {
            uint16_t u = 26116u;
            FDJson::Serializer::Value val = serializer.serialize(u);
            ASSERT_TRUE(val.IsUint());
            EXPECT_EQ(u, val.GetUint());
        }
    }

    { // Int 32 & Uint 32
        {
            int32_t i = 6496461;
            FDJson::Serializer::Value val = serializer.serialize(i);
            ASSERT_TRUE(val.IsInt());
            EXPECT_EQ(i, val.GetInt());
        }

        {
            uint32_t u = 646486432u;
            FDJson::Serializer::Value val = serializer.serialize(u);
            ASSERT_TRUE(val.IsUint());
            EXPECT_EQ(u, val.GetUint());
        }
    }

    { // Int 64 & Uint 64
        {
            int64_t i = 56148646;
            FDJson::Serializer::Value val = serializer.serialize(i);
            ASSERT_TRUE(val.IsInt());
            EXPECT_EQ(i, val.GetInt());
        }

        {
            uint64_t u = 54646131564u;
            FDJson::Serializer::Value val = serializer.serialize(u);
            ASSERT_TRUE(val.IsUint64());
            EXPECT_EQ(u, val.GetUint64());
        }
    }
}

TEST(TestJsonPrimitive, TestUnserializeInteger)
{
    FDJson::Serializer serializer;
    { // Int 16 & Uint 16
        {
            int16_t i;
            FDJson::Serializer::Value val(-1564);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, i, &err)) << err;
            EXPECT_EQ(-1564, i);
        }

        {
            uint16_t u;
            FDJson::Serializer::Value val(26116u);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, u, &err)) << err;
            EXPECT_EQ(26116u, u);
        }
    }

    { // Int 32 & Uint 32
        {
            int32_t i;
            FDJson::Serializer::Value val(6496461);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, i, &err)) << err;
            EXPECT_EQ(6496461, i);
        }

        {
            uint32_t u;
            FDJson::Serializer::Value val(646486432u);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, u, &err)) << err;
            EXPECT_EQ(646486432u, u);
        }
    }

    { // Int 64 & Uint 64
        {
            int64_t i;
            FDJson::Serializer::Value val(56148646);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, i, &err)) << err;
            EXPECT_EQ(56148646, i);
        }

        {
            uint64_t u;
            FDJson::Serializer::Value val(54646131564u);
            std::string err;
            ASSERT_TRUE(serializer.unserialize(val, u, &err)) << err;
            EXPECT_EQ(54646131564u, u);
        }
    }
}

TEST(TestJsonPrimitive, TestSerializeNull)
{
    FDJson::Serializer serializer;
    FDJson::Serializer::Value val = serializer.serialize(nullptr);
    ASSERT_TRUE(val.IsNull());
}

TEST(TestJsonPrimitive, TestUnserializeNull)
{
    FDJson::Serializer serializer;
    std::optional<bool> b;
    FDJson::Serializer::Value val(rapidjson::kNullType);
    std::string err;
    ASSERT_TRUE(serializer.unserialize(val, b, &err)) << err;
    ASSERT_FALSE(b.has_value());
}

#endif // FDJSON_TEST_PRIMITIVE_H

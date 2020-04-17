#ifndef FDJSON_TEST_CUSTOM_H
#define FDJSON_TEST_CUSTOM_H

#include <gtest/gtest.h>

#include <functional>

#include <FDJson/Json_fwd.h>

struct TestClass2
{
    int i;
    float f;
    char c;
    std::string str;

    TestClass2(int i = 42, float f = 3.14f, char c = 'A', const std::string &str = "toto"):
        i(i), f(f), c(c), str(str)
    {}
};

namespace FDXml
{
    rapidjson::Value serialize(const TestClass2 &c);

    bool unserialize(const rapidjson::Value &val, TestClass2 &str, std::string *err = nullptr);
}


#include <FDJson/Json_utils.h>
#include <FDJson/JsonSerializer.h>

namespace FDJson
{
    rapidjson::Value serialize(const TestClass2 &c, Serializer &)
    {
        rapidjson::Value val(rapidjson::kObjectType);

        val.AddMember(FDJson::Serializer::getInstance().serialize("i"),
                      FDJson::Serializer::getInstance().serialize(c.i), FDJson::Serializer::getInstance().getAllocator());

        val.AddMember(FDJson::Serializer::getInstance().serialize("f"),
                      FDJson::Serializer::getInstance().serialize(c.f), FDJson::Serializer::getInstance().getAllocator());

        val.AddMember(FDJson::Serializer::getInstance().serialize("c"),
                      FDJson::Serializer::getInstance().serialize(c.c), FDJson::Serializer::getInstance().getAllocator());

        val.AddMember(FDJson::Serializer::getInstance().serialize("str"),
                      FDJson::Serializer::getInstance().serialize(c.str), FDJson::Serializer::getInstance().getAllocator());
        return val;
    }

    bool unserialize(const rapidjson::Value &val, TestClass2 &c, Serializer &tag, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "Value is not an object";

            return false;
        }

        return FDJson::unserialize(val["i"], c.i, tag, err)
                && FDJson::unserialize(val["f"], c.f, tag, err)
                && FDJson::unserialize(val["c"], c.c, tag, err)
                && FDJson::unserialize(val["str"], c.str, tag, err);
    }
}

TEST(TestXmlCustom, TestSerializeCustomType)
{
    FDJson::Serializer::Value val = FDJson::serialize(TestClass2(), FDJson::Serializer::getInstance());
    ASSERT_EQ(val["i"].GetInt(), 42);
    ASSERT_FLOAT_EQ(val["f"].GetFloat(), 3.14f);
    ASSERT_STREQ(val["c"].GetString(), "A");
    ASSERT_STREQ(val["str"].GetString(), "toto");

    FDJson::Serializer::getInstance().save(val, "TestClass.json");
}

TEST(TestXmlCustom, TestUnserializeReflectConfig)
{
    std::string err;
    ASSERT_TRUE(FDJson::Serializer::getInstance().parseFile("TestClass.json")) << err;
    const FDJson::Serializer::Document &val(FDJson::Serializer::getInstance().getCurrentDocument());

    TestClass2 c;
    ASSERT_TRUE(FDJson::unserialize(val, c, FDJson::Serializer::getInstance(), &err)) << err;
    ASSERT_EQ(c.i, 42);
    ASSERT_FLOAT_EQ(c.f, 3.14f);
    ASSERT_EQ(c.c, 'A');
    ASSERT_EQ(c.str, "toto");
}


#endif // FDJSON_TEST_CUSTOM_H

#ifndef TEST_CUSTOM_H
#define TEST_CUSTOM_H

#include <gtest/gtest.h>

#include <functional>

#include <FDJson/Json_allocator.h>
#include <FDJson/Json_fwd.h>

class AnalyserConfig
{
    public:
        class CompilerConfig
        {
            public:
                CompilerConfig() {}

                std::string m_compiler;
                std::set<std::string> m_defines;
                std::set<std::string> m_include;
                std::set<std::string> m_flags;
        };

        class Filter
        {
            public:
                Filter() {}

                bool match(const std::string &value) const
                {
                    for (auto it = m_parse.begin(); it != m_parse.end(); ++it)
                    {
                        if(value == *it)
                            return true;

                        if(!m_patternMatcher || m_patternMatcher(value, *it))
                        {
                            for (auto it2 = m_ignore.begin(); it2 != m_ignore.end(); ++it2)
                            {
                                if(m_patternMatcher(value, *it2))
                                    return false;
                            }
                        }
                    }

                    return false;
                }

                std::set<std::string> m_ignore;
                std::set<std::string> m_parse;
                std::function<bool(const std::string &, const std::string &)> m_patternMatcher;
        };

    public:
        AnalyserConfig() {}

    public:
        CompilerConfig m_compilerConfig;
        Filter m_fileFilter;
        Filter m_nameFilter;

};

namespace FDJson
{
    rapidjson::Value serialize(AnalyserConfig::CompilerConfig &&c);

    rapidjson::Value serialize(const AnalyserConfig::CompilerConfig &c);

    bool unserialize(const rapidjson::Value &val, AnalyserConfig::CompilerConfig &str, std::string *err = nullptr);

    rapidjson::Value serialize(AnalyserConfig::Filter &&c);

    rapidjson::Value serialize(const AnalyserConfig::Filter &c);

    bool unserialize(const rapidjson::Value &val, AnalyserConfig::Filter &str, std::string *err = nullptr);

    rapidjson::Value serialize(AnalyserConfig &&c);

    rapidjson::Value serialize(const AnalyserConfig &c);

    bool unserialize(const rapidjson::Value &val, AnalyserConfig &str, std::string *err = nullptr);
}


#include <FDJson/Json_utils.h>
#include <FDJson/JsonSerializer.h>

namespace FDJson
{
    rapidjson::Value serialize(AnalyserConfig::CompilerConfig &&c)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("compiler", FDJson::serialize(c.m_compiler), FDJson::Json_helper::allocator);
        val.AddMember("defines", FDJson::serialize(c.m_defines), FDJson::Json_helper::allocator);
        val.AddMember("include", FDJson::serialize(c.m_include), FDJson::Json_helper::allocator);
        val.AddMember("flags", FDJson::serialize(c.m_flags), FDJson::Json_helper::allocator);

        return val;
    }

    rapidjson::Value serialize(const AnalyserConfig::CompilerConfig &c)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("compiler", FDJson::serialize(c.m_compiler), FDJson::Json_helper::allocator);
        val.AddMember("defines", FDJson::serialize(c.m_defines), FDJson::Json_helper::allocator);
        val.AddMember("include", FDJson::serialize(c.m_include), FDJson::Json_helper::allocator);
        val.AddMember("flags", FDJson::serialize(c.m_flags), FDJson::Json_helper::allocator);

        return val;
    }

    bool unserialize(const rapidjson::Value &val, AnalyserConfig::CompilerConfig &c, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "Value is not an object";

            return false;
        }

        if(!val.HasMember("compiler"))
        {
            if(err)
                *err = "Value has no member compiler";

            return false;
        }
        else if(!FDJson::unserialize(val["compiler"], c.m_compiler, err))
            return false;

        if(!val.HasMember("defines"))
        {
            if(err)
                *err = "Value has no member defines";

            return false;
        }
        else if(!FDJson::unserialize(val["defines"], c.m_defines, err))
            return false;

        if(!val.HasMember("include"))
        {
            if(err)
                *err = "Value has no member defines";

            return false;
        }
        else if(!FDJson::unserialize(val["include"], c.m_include, err))
            return false;

        if(!val.HasMember("flags"))
        {
            if(err)
                *err = "Value has no member defines";

            return false;
        }
        else if(!FDJson::unserialize(val["flags"], c.m_flags, err))
            return false;

        return true;
    }

    rapidjson::Value serialize(AnalyserConfig::Filter &&c)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("ignore", FDJson::serialize(c.m_ignore), FDJson::Json_helper::allocator);
        val.AddMember("parse", FDJson::serialize(c.m_parse), FDJson::Json_helper::allocator);

        return val;
    }

    rapidjson::Value serialize(const AnalyserConfig::Filter &c)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("ignore", FDJson::serialize(c.m_ignore), FDJson::Json_helper::allocator);
        val.AddMember("parse", FDJson::serialize(c.m_parse), FDJson::Json_helper::allocator);

        return val;
    }

    bool unserialize(const rapidjson::Value &val, AnalyserConfig::Filter &c, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "Value is not an object";

            return false;
        }

        if(!val.HasMember("ignore"))
        {
            if(err)
                *err = "Value has no member ignore";

            return false;
        }
        else if(!FDJson::unserialize(val["ignore"], c.m_ignore, err))
            return false;

        if(!val.HasMember("parse"))
        {
            if(err)
                *err = "Value has no member parse";

            return false;
        }
        else if(!FDJson::unserialize(val["parse"], c.m_parse, err))
            return false;

        return true;
    }

    rapidjson::Value serialize(AnalyserConfig &&c)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("configuration", FDJson::serialize(c.m_compilerConfig), FDJson::Json_helper::allocator);
        val.AddMember("file-filter", FDJson::serialize(c.m_fileFilter), FDJson::Json_helper::allocator);
        val.AddMember("name-filter", FDJson::serialize(c.m_nameFilter), FDJson::Json_helper::allocator);
        return val;
    }

    rapidjson::Value serialize(const AnalyserConfig &c)
    {
        rapidjson::Value val(rapidjson::kObjectType);
        val.AddMember("configuration", FDJson::serialize(c.m_compilerConfig), FDJson::Json_helper::allocator);
        val.AddMember("file-filter", FDJson::serialize(c.m_fileFilter), FDJson::Json_helper::allocator);
        val.AddMember("name-filter", FDJson::serialize(c.m_nameFilter), FDJson::Json_helper::allocator);
        return val;
    }

    bool unserialize(const rapidjson::Value &val, AnalyserConfig &c, std::string *err)
    {
        if(!val.IsObject())
        {
            if(err)
                *err = "Value is not an object";

            return false;
        }

        if(!val.HasMember("configuration"))
        {
            if(err)
                *err = "Value has no member configuration";

            return false;
        }
        else if(!FDJson::unserialize(val["configuration"], c.m_compilerConfig, err))
            return false;

        if(!val.HasMember("file_filter"))
        {
            if(err)
                *err = "Value has no member file_filter";

            return false;
        }
        else if(!FDJson::unserialize(val["file_filter"], c.m_fileFilter, err))
            return false;

        if(!val.HasMember("name_filter"))
        {
            if(err)
                *err = "Value has no member name_filter";

            return false;
        }
        else if(!FDJson::unserialize(val["name_filter"], c.m_nameFilter, err))
            return false;

        return true;
    }
}


#include "rapidjson/filereadstream.h"
#include <cstdio>

TEST(TestCustom, TestUnserializeReflectConfig)
{
    FILE* fp = fopen("/home/ben/Bureau/dev/FanatikDevelopment/FDCodeAnalyser/analyser_config.json", "r");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document doc;
    doc.ParseStream(is);
    fclose(fp);

    std::string err;
    AnalyserConfig config;
    ASSERT_TRUE(FDJson::unserialize(doc.GetObject(), config, &err));

    ASSERT_STREQ(config.m_compilerConfig.m_compiler.c_str(), "../thirdparty/llvm/build/bin/clang++");

    ASSERT_NE(config.m_compilerConfig.m_defines.find("__STDC_CONSTANT_MACROS"), config.m_compilerConfig.m_defines.end());
    ASSERT_NE(config.m_compilerConfig.m_defines.find("__STDC_LIMIT_MACROS"), config.m_compilerConfig.m_defines.end());

    ASSERT_NE(config.m_compilerConfig.m_include.find("include"), config.m_compilerConfig.m_include.end());
    ASSERT_NE(config.m_compilerConfig.m_include.find("../thirdparty/build/tools/clang/include"), config.m_compilerConfig.m_include.end());
    ASSERT_NE(config.m_compilerConfig.m_include.find("../thirdparty/build/include"), config.m_compilerConfig.m_include.end());
    ASSERT_NE(config.m_compilerConfig.m_include.find("../thirdparty/build/../clang/include"), config.m_compilerConfig.m_include.end());
    ASSERT_NE(config.m_compilerConfig.m_include.find("../thirdparty/build/tools/clang/lib/Headers"), config.m_compilerConfig.m_include.end());
    ASSERT_NE(config.m_compilerConfig.m_include.find("../thirdparty/build/lib/clang/10.0.0/include"), config.m_compilerConfig.m_include.end());

    ASSERT_NE(config.m_compilerConfig.m_flags.find("-c"), config.m_compilerConfig.m_flags.end());
    ASSERT_NE(config.m_compilerConfig.m_flags.find("-std=c++17"), config.m_compilerConfig.m_flags.end());

    ASSERT_NE(config.m_fileFilter.m_ignore.find("src/main.cpp"), config.m_fileFilter.m_ignore.end());
    ASSERT_NE(config.m_fileFilter.m_ignore.find("src/matchers.cpp"), config.m_fileFilter.m_ignore.end());
    ASSERT_NE(config.m_fileFilter.m_ignore.find("src/NodeFilter.cpp"), config.m_fileFilter.m_ignore.end());
    ASSERT_NE(config.m_fileFilter.m_ignore.find("src/FDCodeAnalyser.cpp"), config.m_fileFilter.m_ignore.end());

    ASSERT_NE(config.m_fileFilter.m_parse.find("src/*"), config.m_fileFilter.m_parse.end());
}


#endif // TEST_CUSTOM_H

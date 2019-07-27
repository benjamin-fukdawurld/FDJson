#include <FDJson/Json_utils.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> FDJson::Json_helper::allocator;

rapidjson::Value FDJson::serialize(std::nullptr_t)
{
    return rapidjson::Value(rapidjson::kNullType);
}

rapidjson::Value FDJson::serialize(const char c)
{
    return rapidjson::Value(&c, 1u, Json_helper::allocator);
}

bool FDJson::unserialize(const rapidjson::Value &val, char &c, std::string *err)
{
    if(!val.IsString())
    {
        if(err)
            *err = "Value is not a string";

        return false;
    }

    if(val.GetStringLength() > 1)
    {
        if(err)
            *err = "Value length is greater than one char";

        return false;
    }

    c = val.GetString()[0];
    return true;
}

rapidjson::Value FDJson::serialize(const char *c)
{
    return rapidjson::Value(c, static_cast<rapidjson::SizeType>(strlen(c)));
}

rapidjson::Value FDJson::serialize(std::string &&c)
{
    return rapidjson::Value(c.c_str(), static_cast<rapidjson::SizeType>(c.size()));
}

rapidjson::Value FDJson::serialize(const std::string &c)
{
    return rapidjson::Value(c.c_str(), static_cast<rapidjson::SizeType>(c.size()));
}

bool FDJson::unserialize(const rapidjson::Value &val, std::string &str, std::string *err)
{
    if(!val.IsString())
    {
        if(err)
            *err = "Value is not a string";

        return false;
    }

    str = std::string(val.GetString(), val.GetStringLength());

    return true;
}

rapidjson::Value FDJson::serialize(const bool b)
{
    return rapidjson::Value(b);
}

bool FDJson::unserialize(const rapidjson::Value &val, bool &b, std::string *err)
{
    if(!val.IsBool())
    {
        if(err)
            *err = "Value is not a boolean";

        return false;
    }

    b = val.IsTrue();
    return true;
}


bool FDJson::unserialize(const rapidjson::Value &val, int64_t &i, std::string *err)
{
    if(!val.IsInt64())
    {
        if(err)
            *err = "Value is not a 64 bits integer";

        return false;
    }

    i = val.GetInt64();
    return true;
}

bool FDJson::unserialize(const rapidjson::Value &val, uint64_t &i, std::string *err)
{
    if(!val.IsUint64())
    {
        if(err)
            *err = "Value is not a 64 bits unsigned integer";

        return false;
    }

    i = val.GetUint64();
    return true;
}

bool FDJson::unserialize(const rapidjson::Value &val, float &f, std::string *err)
{
    if(!val.IsFloat())
    {
        if(err)
            *err = "Value is not a float";

        return false;
    }

    f = val.GetFloat();
    return true;
}

bool FDJson::unserialize(const rapidjson::Value &val, double &d, std::string *err)
{
    if(!val.IsDouble())
    {
        if(err)
            *err = "Value is not a double";

        return false;
    }

    d = val.GetDouble();
    return true;
}


std::ostream &operator<<(std::ostream &out, const rapidjson::Value &val)
{
    using namespace rapidjson;

    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    val.Accept(writer);
    out << sb.GetString();

    return out;
}

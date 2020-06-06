#include <FDJson/Json.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

rapidjson::Value FDJson::serialize(std::nullptr_t, Serializer &)
{
    return rapidjson::Value(rapidjson::kNullType);
}

rapidjson::Value FDJson::serialize(const char c, Serializer &serializer)
{
    return rapidjson::Value(&c, 1u, serializer.getAllocator());
}

bool FDJson::unserialize(const rapidjson::Value &val, char &c, Serializer &, std::string *err)
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

rapidjson::Value FDJson::serialize(const char *c, Serializer &)
{
    return rapidjson::Value(c, static_cast<rapidjson::SizeType>(strlen(c)));
}

rapidjson::Value FDJson::serialize(const std::string &c, Serializer &)
{
    return rapidjson::Value(c.c_str(), static_cast<rapidjson::SizeType>(c.size()));
}

bool FDJson::unserialize(const rapidjson::Value &val, std::string &str, Serializer &, std::string *err)
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

rapidjson::Value FDJson::serialize(const bool b, Serializer &)
{
    return rapidjson::Value(b);
}

bool FDJson::unserialize(const rapidjson::Value &val, bool &b, Serializer &, std::string *err)
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


bool FDJson::unserialize(const rapidjson::Value &val, int64_t &i, Serializer &, std::string *err)
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

bool FDJson::unserialize(const rapidjson::Value &val, uint64_t &i, Serializer &, std::string *err)
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

rapidjson::Value FDJson::serialize(const float f, Serializer &)
{
    return rapidjson::Value(f);
}

rapidjson::Value FDJson::serialize(const double &d, Serializer &)
{
    return rapidjson::Value(d);
}

bool FDJson::unserialize(const rapidjson::Value &val, float &f, Serializer &, std::string *err)
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

bool FDJson::unserialize(const rapidjson::Value &val, double &d, Serializer &, std::string *err)
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

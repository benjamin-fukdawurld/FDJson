#include <FDJson/JsonSerializer.h>

#include <FDCore/FileUtils.h>

#include <rapidjson/prettywriter.h>
#include <rapidjson/error/en.h>
#include <rapidjson/ostreamwrapper.h>

#include <fstream>

void FDJson::JsonSerializerImpl::clearMemory()
{
    m_doc.GetAllocator().Clear();
}

const FDJson::JsonSerializerImpl::Document &FDJson::JsonSerializerImpl::getCurrentDocument() const
{
    return m_doc;
}

FDJson::JsonSerializerImpl::Allocator &FDJson::JsonSerializerImpl::getAllocator()
{
    return m_doc.GetAllocator();
}

bool FDJson::JsonSerializerImpl::parseFile(const std::string_view path, std::string *err)
{
    std::unique_ptr<char[]> text(FDCore::readFile(path.data()).release());
    m_doc.Parse(text.get());

    if(m_doc.HasParseError())
    {
        if(err)
            *err = rapidjson::GetParseError_En(m_doc.GetParseError());

        return false;
    }

    return true;
}

bool FDJson::JsonSerializerImpl::parseString(const std::string_view str, std::string *err)
{
    m_doc.Parse(str.data());

    if(m_doc.HasParseError())
    {
        if(err)
            *err = rapidjson::GetParseError_En(m_doc.GetParseError());

        return false;
    }

    return true;
}

std::string FDJson::JsonSerializerImpl::print(const FDJson::JsonSerializerImpl::Value &val)
{
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writter;
    val.Accept(writter);
    return sb.GetString();
}

void FDJson::JsonSerializerImpl::save(const FDJson::JsonSerializerImpl::Value &val, const std::string_view path)
{
    std::ofstream ofs(path.data());
    rapidjson::OStreamWrapper osw(ofs);

    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    val.Accept(writer);
}

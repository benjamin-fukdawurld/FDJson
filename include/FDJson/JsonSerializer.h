#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <FDSerialize/SerializerBase.h>

#include <FDJson/Json_fwd.h>
#include <FDJson/FDJson.h>

#include <rapidjson/document.h>

namespace FDJson
{
    class FD_EXPORT JsonSerializerImpl
    {
        friend class FDSerialize::SerializerBase<JsonSerializerImpl>;
        public:
            typedef rapidjson::Document Document;
            typedef rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> Allocator;
            typedef rapidjson::Value Value;

        protected:
            Document m_doc;

        private:
            JsonSerializerImpl() = default;
            JsonSerializerImpl(JsonSerializerImpl&&) = delete;
            JsonSerializerImpl(const JsonSerializerImpl&) = delete;

            JsonSerializerImpl &operator=(JsonSerializerImpl&&) = delete;
            JsonSerializerImpl &operator=(const JsonSerializerImpl&) = delete;

        public:
            Allocator &getAllocator();

            void clearMemory();

            const Document &getCurrentDocument() const;


            bool parseFile(const std::string_view path, std::string *err = nullptr);

            bool parseString(const std::string_view str, std::string *err = nullptr);

            std::string print(const Value &val);

            void save(const Value &val, const std::string_view path);

            template<typename T>
            Value serialize(const T &obj, Serializer &serializer)
            {
                return FDJson::serialize(obj, serializer);
            }

            template<typename T>
            Value serialize(T obj[], size_t len, Serializer &serializer)
            {
                return FDJson::serialize(obj, len, serializer);
            }

            template<typename T>
            bool unserialize(const Value &val, T &out, Serializer &serializer, std::string *err = nullptr)
            {
                return FDJson::unserialize(val, out, serializer, err);
            }

            template<typename T>
            bool unserialize(const Value &val, T out[], size_t len, Serializer &serializer, std::string *err = nullptr)
            {
                return FDJson::unserialize(val, out, len, serializer, err);
            }
    };
}

#endif // JSONSERIALIZER_H

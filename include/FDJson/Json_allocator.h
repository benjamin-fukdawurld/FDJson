#ifndef JSON_ALLOCATOR_H
#define JSON_ALLOCATOR_H

#include <rapidjson/allocators.h>

namespace FDJson
{
    struct Json_helper
    {
        static rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> allocator;
    };
}

#endif // JSON_ALLOCATOR_H

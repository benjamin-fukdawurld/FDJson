#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include <FDJson/Json_fwd.h>

#include <FDJson/Json_primitive.h>
#include <FDJson/Json_array.h>
#include <FDJson/Json_list.h>
#include <FDJson/Json_tuple.h>
#include <FDJson/Json_set.h>
#include <FDJson/Json_map.h>

std::ostream &operator<<(std::ostream &out, const rapidjson::Value &val);

#endif // JSON_UTILS_H

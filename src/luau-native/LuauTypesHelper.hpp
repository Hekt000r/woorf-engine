#ifndef LUAU_TYPES_HELPER_HPP

#define LUAU_TYPES_HELPER_HPP

#include <string>
#include <lua.h>
using namespace std;

enum class ValueType: int32_t {
    Nil,
    Number,
    Boolean,
    String
};

struct NativeValue {
    ValueType type;
    double numberValue;
    int32_t boolValue;
    const char* stringValue;
};

using ObjectValue = void*;

NativeValue readValue(lua_State* L, int index);
void pushValue(lua_State* L, NativeValue& value);

#endif
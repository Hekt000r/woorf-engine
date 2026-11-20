/**
 * @file LuauTypesHelper.cpp
 * Contains helper objects and functions for C++/Lua interop
 */
#include <lua.h>
#include <string>

using ObjectHandle = void*;
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

/**
 * Helper function for Luau types conversion.
 * Reads a Luau value and returns a NativeValue
 * @param L The Luau instance
 * @param index The stack index where the value is located
 */
NativeValue readValue(lua_State* L, int index)
{
    NativeValue value{};

    switch (lua_type(L, index))
    {
        case LUA_TNUMBER:
            value.type = ValueType::Number;
            value.numberValue = lua_tonumber(L, index);
            break;

        case LUA_TBOOLEAN:
            value.type = ValueType::Boolean;
            value.boolValue = lua_toboolean(L, index);
            break;

        case LUA_TSTRING:
            value.type = ValueType::String;
            value.stringValue = lua_tostring(L, index);
            break;

        default:
            value.type = ValueType::Nil;
            break;
    }

    return value;
}

/**
 * Helper function for Luau types conversion.
 * Convert NativeValue->Luau type and push
 * @param L The Luau instance
 * @param value The NativeValue(&) to convert into a Luau type and push.
 */
void pushValue(lua_State* L, const NativeValue& value)
{
    switch (value.type)
    {
        case ValueType::Number:
            lua_pushnumber(L, value.numberValue);
            break;

        case ValueType::Boolean:
            lua_pushboolean(L, value.boolValue);
            break;

        case ValueType::String:
            lua_pushstring(L, value.stringValue);
            break;

        default:
            lua_pushnil(L);
            break;
    }
}
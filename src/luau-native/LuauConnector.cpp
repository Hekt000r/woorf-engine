
/**
 LuauConnector.cpp
 Connects Luau to C# by exposing a few c++ functions used to interact with Lua to C#
 @author Hektor
*/

#include "LuauConnector.hpp"
#include <lua.h>
#include <lualib.h>
#include <luacode.h>
#include <string>
#include <stdexcept>
#include <cstdlib>

using std::string;

LuauVM::LuauVM()
{
    L = luaL_newstate();
    luaL_openlibs(L);
}

LuauVM::~LuauVM()
{
    lua_close(L);
}

/**
 * Registers a function and makes it available in Lua
 * @param name The name of the function that will be registered
 * @param function The function to register, lua_CFunction compatible
 */
void LuauVM::registerFunctionToLua(const char *name, lua_CFunction function)
{
    lua_pushcfunction(L, function, nullptr); // temporary: cannot use the char *name because its a pointer to a temporary C# string
    lua_setglobal(L, name);
}

/**
 * Runs lua bytecode
 * @param source The source, Luau bytecode in text format
 * @param chunkName Label, appears in error messages and stack traces
 */
void LuauVM::run(const string source, const char *chunkName)
{
    /* turn into C char and get size, then compile*/
    size_t size = 0;
    char *bytecode = luau_compile(source.c_str(), source.size(), nullptr, &size);

    int status = luau_load(L, chunkName, bytecode, size, 0);
    free(bytecode);

    if (status != 0) // non-zero status means error
        throwTopError();

    if (lua_pcall(L, 0, 0, 0) != 0) // again, non-zero means error
        throwTopError();
}

/**
 * Helper that translates the luau string (error) at the top of the stack and throws it
 * Assumes the value at the top of the stack is an error message.
 **/
void LuauVM::throwTopError()
{
    const char *errorString = lua_tostring(L, -1);
    string msg = errorString ? errorString : "unknown error";
    lua_pop(L, 1);
    throw std::runtime_error(msg);
}

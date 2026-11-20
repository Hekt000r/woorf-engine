#ifndef LUAU_CONNECTOR_HPP
#define LUAU_CONNECTOR_HPP

#include <string>
#include <lua.h>

class LuauVM
{
public:
    LuauVM();
    ~LuauVM();

    void run(const std::string source, const char* chunkName = "=script");
    void registerFunctionToLua(const char* name, lua_CFunction function);

private:
    lua_State* L;
    void throwTopError();
};

#endif
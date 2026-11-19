#ifndef LUAU_CONNECTOR_HPP
#define LUAU_CONNECTOR_HPP

#include <string>
#include <lua.h>

using std::string;

class LuauVM {
    private:
    lua_State* L;

    public:
    LuauVM();
    void run(string &source,char* chunkName);
    void registerFunctionToLua(char* name, lua_CFunction function);
};

#endif
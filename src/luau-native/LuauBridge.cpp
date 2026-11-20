/**
 * LuauBridge.cpp
 * Exports c++ luau interface as a library, C-API export
 * Handles the connnection C# -> C++ -> Lua and vice-versa
 * @author Hektor
 */

#include <LuauConnector.hpp>
#include <string>

#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif

using namespace std;

/**
 * External Luau library function.
 * Creates a new LuauVM class
 * @returns pointer to a new LuauVM* object on success, will return a nullptr if failure
 */
EXPORT LuauVM* l_create_vm() {
    try {
        return new LuauVM;
    } catch (...) {
        return nullptr;
    }
}

/**
 * External Luau library function.
 * Deletes the provided LuauVM instance
 * @param vm Pointer to the LuauVM instance to destroy
 * @warning This is a destructive operation, use with care
 */
EXPORT void l_delete_vm(LuauVM* vm) {
    delete(vm);
}

/**
 * External Luau library function.
 * Runs the supplied Luau bytecode (string format) inside the supplied LuauVM instance
 * @param vm Pointer to the LuauVM where the code will run
 * @param source The Luau bytecode source in string& format
 * @returns 0 = success, 1/non-zero = failure
 * @todo Chunkname support should be added
 */
EXPORT int l_run_code(LuauVM* vm, char* source)  {
    if (!vm || !source) return 1;

    try {
        vm->run(string(source),"NOT_SUPPORTED");
        return 0;
    } catch (...) {
        return 1;
    }
}

/** 
 * External Luau library function
 * Registers the supplied function to Lua
 * @param vm The LuauVM instance where the function will be registered
 * @param function The function to register, compatible with lua_CFunction format
 * @param name The name that the function will be assigned char*
 * @returns 0 if success, 1/non-zero if failure
*/
EXPORT int l_register_function(LuauVM* vm, lua_CFunction function, char* name) {
    if (!vm || !function || !name) return 1;

    try {
        vm->registerFunctionToLua(name,function);
        return 0;
    } catch(...) {
        return 1;
    }
}
#include "LuaIncludes.h"

#include <iostream>

bool checkLua(lua_State* L, int result)
{
    if (!result == LUA_OK) {
        auto message = lua_tostring(L, -1);
        std::cout << "Error: " << message << std::endl;
        return false;
    }
    return true;
}
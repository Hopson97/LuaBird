#pragma once

extern "C" {
#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>
}

bool checkLua(lua_State* L, int result);
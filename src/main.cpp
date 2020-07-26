#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>
#include "LuaIncludes.h"
#include "LuaSprite.h"
#include "LuaKeyboard.h"

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    LuaSprite::luaRegister(L);
    luaRegisterKeyboard(L);

    if (checkLua(L, luaL_dofile(L, "game/main.lua"))) {
        /*
        lua_getglobal(L, "doStuff");
        if (lua_isfunction(L, -1)) {
            lua_pushnumber(L, 10);
            lua_pushnumber(L, 5);

            if (luaOk(L, lua_pcall(L, 2, 1, 0))) {
                std::cout << "C++ Called" << lua_tonumber(L, -1) << "\n";
            }
        }

        lua_getglobal(L, "test");
        if (lua_istable(L, -1)) {
            lua_pushstring(L, "name");
            lua_gettable(L, -2);
            test.name = lua_tostring(L, -1);
            lua_pop(L, 1);

            lua_pushstring(L, "by");
            lua_gettable(L, -2);
            test.by = lua_tostring(L, -1);
            lua_pop(L, 1);

            std::cout << test.name << ", by " << test.by <<  std::endl;
        }
        */
    }

    // Cleanup

    sf::RenderWindow window({1280, 720}, "Lua Bird");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update
        lua_getglobal(L, "update");
        if (lua_isfunction(L, -1)) {
            checkLua(L, lua_pcall(L, 0, 0, 0));
        }

        // Render
        window.clear();
        lua_getglobal(L, "sprites");
        if (lua_istable(L, -1)) {
            lua_pushnil(L);
            while (lua_next(L, -2)) {
                LuaSprite* sprite = (LuaSprite*)lua_touserdata(L, -1);
                
                sprite->draw(window);
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }
        window.display();
    }

    lua_close(L);

    return 0;
}

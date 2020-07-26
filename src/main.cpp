#include <SFML/Graphics.hpp>

#include "LuaIncludes.h"
#include "LuaKeyboard.h"
#include "LuaSprite.h"
#include <array>
#include <iostream>

template <typename T, typename F>
void itrTable(lua_State* L, const char* tableName, F func)
{
    lua_getglobal(L, tableName);
    if (lua_istable(L, -1)) {
        lua_pushnil(L);
        while (lua_next(L, -2)) {
            T* object = (T*)lua_touserdata(L, -1);
            func(object);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }
}

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    LuaSprite::luaRegister(L);
    luaRegisterKeyboard(L);

    if (!checkLua(L, luaL_dofile(L, "game/_lib.lua"))) {
        std::cout << "Failed to load engine library\n";
        return 1;
    }

    if (!checkLua(L, luaL_dofile(L, "game/main.lua"))) {
        std::cout << "Failed to load game\n";
        return 1;
    }

    // Cleanup

    sf::RenderWindow window({1280, 720}, "Lua Bird");
    window.setFramerateLimit(60);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update
        lua_getglobal(L, "update");
        if (lua_isfunction(L, -1)) {
            lua_pushnumber(L, clock.restart().asSeconds());
            checkLua(L, lua_pcall(L, 1, 0, 0));
        }

        // Render
        window.clear();
        itrTable<LuaSprite>(L, "sprites",
                            [&window](auto* sprite) { sprite->draw(window); });
        window.display();
    }

    lua_close(L);

    return 0;
}

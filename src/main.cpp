#include <SFML/Graphics.hpp>

#include <array>
#include <iostream>

extern "C" {
#include <lua/lauxlib.h>
#include <lua/lua.h>
#include <lua/lualib.h>
}

bool luaOk(lua_State* L, int result)
{
    if (!result == LUA_OK) {
        auto message = lua_tostring(L, -1);
        std::cout << "Error: " << message << std::endl;
        return false;
    }
    return true;
}

struct Rectangle {
    std::array<sf::Vertex, 4> verts;

    sf::Vector2f position;
    sf::Vector2f size;

    void init(float width, float height, float x, float y);
    void draw(sf::RenderWindow& window);
};

void Rectangle::init(float width, float height, float x, float y)
{
    verts[0].position = {x, y};
    verts[1].position = {x, y + height};
    verts[2].position = {x + width, y + height};
    verts[3].position = {x + width, y};

    verts[0].color = sf::Color::White;
    verts[1].color = sf::Color::White;
    verts[2].color = sf::Color::White;
    verts[3].color = sf::Color::White;

    position = {x, y};
    size = {width, height};
}

void Rectangle::draw(sf::RenderWindow& window)
{
    window.draw(verts.data(), verts.size(), sf::Quads);
}

// Rectangle.new(width, height, x, y)
int lua_Rectangle_new(lua_State* L)
{
    float w = (float)luaL_checknumber(L, -1);
    float h = (float)luaL_checknumber(L, -1);
    float x = (float)luaL_checknumber(L, -1);
    float y = (float)luaL_checknumber(L, -1);

    Rectangle* rect = (Rectangle*)lua_newuserdata(L, sizeof(Rectangle));
    rect->init(w, h, x, y);

    luaL_getmetatable(L, "Rectangle");
    lua_setmetatable(L, -2);

    return 1;
}

const luaL_Reg lua_rectLib[] = {
    {"new", lua_Rectangle_new},
    {NULL, NULL},
};

const luaL_Reg lua_rectMethods[] = {
    {NULL, NULL},
};

void openLibRectangle(lua_State* L)
{
    luaL_newmetatable(L, "Rectangle");
    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, lua_rectMethods, 0);
    luaL_newlib(L, lua_rectLib);
    lua_setglobal(L, "Rectangle");
}

int main()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // lua_register(L, "functionInCPP", lua_functionInCPP);

    openLibRectangle(L);

    if (luaOk(L, luaL_dofile(L, "game/main.lua"))) {
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

        window.clear();


        lua_getglobal(L, "rects");
        if (lua_istable(L, -1)) {
            lua_pushnil(L);
            while (lua_next(L, -2)) {
                Rectangle* rect = (Rectangle*)lua_touserdata(L, -1);
                rect->draw(window);
                lua_pop(L, 1);
            }
            lua_pop(L, 1);
        }

        window.display();
    }

    lua_close(L);

    return 0;
}

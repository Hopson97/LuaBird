#include "LuaSprite.h"

void LuaSprite::init(float width, float height, float x, float y)
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

void LuaSprite::draw(sf::RenderWindow& window)
{
    window.draw(verts.data(), verts.size(), sf::Quads);
}

int lua_Sprite_new(lua_State* L)
{
    float w = (float)luaL_checknumber(L, -1);
    float h = (float)luaL_checknumber(L, -1);
    float x = (float)luaL_checknumber(L, -1);
    float y = (float)luaL_checknumber(L, -1);

    LuaSprite* rect = (LuaSprite*)lua_newuserdata(L, sizeof(LuaSprite));
    rect->init(w, h, x, y);

    luaL_getmetatable(L, "Sprite");
    lua_setmetatable(L, -2);

    return 1;
}

const luaL_Reg lua_spriteLib[] = {
    {"new", lua_Sprite_new},
    {NULL, NULL},
};

const luaL_Reg lua_spriteMethods[] = {
    {NULL, NULL},
};

void LuaSprite::luaRegister(lua_State* L)
{
    luaL_newmetatable(L, "Sprite");

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    luaL_setfuncs(L, lua_spriteMethods, 0);
    luaL_newlib(L, lua_spriteLib);

    lua_setglobal(L, "Sprite");
}

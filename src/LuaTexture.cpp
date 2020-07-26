#include "LuaTexture.h"

void LuaTexture::init(const char* fileName) 
{
    m_texture.loadFromFile(fileName);
}

sf::Vector2u LuaTexture::getSize() const
{
    return m_texture.getSize();
}

const sf::Texture& LuaTexture::getTexture() const
{
    return m_texture;
}

namespace {
    // LuaSprite.new(x, y, width, height)
    int lua_Texture_new(lua_State* L)
    {
        const char* fileName = luaL_checkstring(L, 1);

        LuaTexture* texture = (LuaTexture*)lua_newuserdata(L, sizeof(LuaTexture));
        texture->init(fileName);

        luaL_getmetatable(L, "Texture");
        lua_setmetatable(L, -2);

        return 1;
    }

    const luaL_Reg lua_textureLib[] = {
        {"new", lua_Texture_new},
        {NULL, NULL},
    };

    const luaL_Reg lua_textureMethods[] = {
        {NULL, NULL},
    };

} // namespace

void LuaTexture::luaRegister(lua_State* L)
{
    luaL_newmetatable(L, "Texture");

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    luaL_setfuncs(L, lua_textureMethods, 0);
    luaL_newlib(L, lua_textureLib);

    lua_setglobal(L, "Texture");
}

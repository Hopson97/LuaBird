#include "LuaSprite.h"

#include "Resources.h"
#include <iostream>

#include "LuaTexture.h"

void LuaSprite::init(float width, float height, float x, float y)
{
    m_position = {x, y};
    m_size = {width, height};

    m_texture = nullptr;

    setPosition(x, y);

    m_verts[0].color = sf::Color::White;
    m_verts[1].color = sf::Color::White;
    m_verts[2].color = sf::Color::White;
    m_verts[3].color = sf::Color::White;
}

void LuaSprite::draw(sf::RenderWindow& window)
{
    sf::RenderStates states;
    if (m_texture) {
        states.texture = m_texture;
    }
    window.draw(m_verts.data(), m_verts.size(), sf::Quads, states);
}

void LuaSprite::move(float x, float y)
{
    m_position += {x, y};
    for (auto& vertex : m_verts) {
        vertex.position += {x, y};
    }
}

const sf::Vector2f& LuaSprite::getPosition() const
{
    return m_position;
}

void LuaSprite::setPosition(float x, float y)
{
    m_position = {x, y};
    m_verts[0].position = {x, y};
    m_verts[1].position = {x, y + m_size.y};
    m_verts[2].position = {x + m_size.x, y + m_size.y};
    m_verts[3].position = {x + m_size.x, y};
}

bool LuaSprite::intersecting(LuaSprite& other) const
{
    return bounds().intersects(other.bounds());
}

void LuaSprite::setTexture(const sf::Texture& texture)
{
    m_texture = &texture;
    m_verts[0].texCoords = {0, 0};
    m_verts[1].texCoords = {0, (float)texture.getSize().y};
    m_verts[2].texCoords = {(float)texture.getSize().x, (float)texture.getSize().y};
    m_verts[3].texCoords = {(float)texture.getSize().x, 0};
}

sf::FloatRect LuaSprite::bounds() const
{
    sf::FloatRect rect;
    rect.width = m_size.x;
    rect.height = m_size.y;
    rect.top = m_position.y;
    rect.left = m_position.x;
    return rect;
}

namespace {
    // LuaSprite.new(x, y, width, height)
    int lua_Sprite_new(lua_State* L)
    {
        float w = (float)luaL_checknumber(L, 1);
        float h = (float)luaL_checknumber(L, 2);
        float x = (float)luaL_checknumber(L, 3);
        float y = (float)luaL_checknumber(L, 4);

        LuaSprite* rect = (LuaSprite*)lua_newuserdata(L, sizeof(LuaSprite));
        rect->init(w, h, x, y);

        luaL_getmetatable(L, "Sprite");
        lua_setmetatable(L, -2);

        return 1;
    }

    // sprite:move(x, y)
    int lua_Sprite_move(lua_State* L)
    {
        LuaSprite* rect = (LuaSprite*)luaL_checkudata(L, 1, "Sprite");
        float x = (float)luaL_checknumber(L, 2);
        float y = (float)luaL_checknumber(L, 3);

        rect->move(x, y);
        return 0;
    }

    // sprite:getPosition()
    int lua_Sprite_getPosition(lua_State* L)
    {
        LuaSprite* sprite = (LuaSprite*)luaL_checkudata(L, 1, "Sprite");
        auto& pos = sprite->getPosition();
        lua_pushnumber(L, pos.x);
        lua_pushnumber(L, pos.y);
        return 2;
    }

    // sprite:setPosition(x, y)
    int lua_Sprite_setPosition(lua_State* L)
    {
        LuaSprite* sprite = (LuaSprite*)luaL_checkudata(L, 1, "Sprite");
        float x = (float)luaL_checknumber(L, 2);
        float y = (float)luaL_checknumber(L, 3);
        sprite->setPosition(x, y);
        return 0;
    }

    // sprite:intersects(Sprite)
    int lua_Sprite_intersects(lua_State* L)
    {
        LuaSprite* sprite = (LuaSprite*)luaL_checkudata(L, 1, "Sprite");
        LuaSprite* otherSprite = (LuaSprite*)luaL_checkudata(L, 2, "Sprite");
        lua_pushboolean(L, sprite->intersecting(*otherSprite));
        return 1;
    }

    // sprite:setTexture(name)
    int lua_Sprite_setTexture(lua_State* L)
    {
        LuaSprite* sprite = (LuaSprite*)luaL_checkudata(L, 1, "Sprite");
        const char* name = luaL_checkstring(L, 2);
        sprite->setTexture(ResourceManager::get().textures.getResource(name));
        return 0;
    }

    const luaL_Reg lua_spriteLib[] = {
        {"new", lua_Sprite_new},
        {NULL, NULL},
    };

    const luaL_Reg lua_spriteMethods[] = {
        {"move", lua_Sprite_move},
        {"getPosition", lua_Sprite_getPosition},
        {"setPosition", lua_Sprite_setPosition},
        {"intersects", lua_Sprite_intersects},
        {"setTexture", lua_Sprite_setTexture},
        {NULL, NULL},
    };

} // namespace

void LuaSprite::luaRegister(lua_State* L)
{
    luaL_newmetatable(L, "Sprite");

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    luaL_setfuncs(L, lua_spriteMethods, 0);
    luaL_newlib(L, lua_spriteLib);

    lua_setglobal(L, "Sprite");
}

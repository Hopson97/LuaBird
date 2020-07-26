#pragma once

#include <array>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "LuaIncludes.h"

struct LuaSprite {
    std::array<sf::Vertex, 4> verts;

    sf::Vector2f position;
    sf::Vector2f size;

    void init(float width, float height, float x, float y);
    void draw(sf::RenderWindow& window);

    static void luaRegister(lua_State* L);
};
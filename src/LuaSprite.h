#pragma once

#include <array>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "LuaIncludes.h"

class LuaTexture;

class LuaSprite {
  public:
    void init(float width, float height, float x, float y);
    void draw(sf::RenderWindow& window);

    void move(float x, float y);
    bool intersecting(LuaSprite& other) const;

    void setTexture(const LuaTexture& texture);

    static void luaRegister(lua_State* L);

  private:
    sf::FloatRect bounds() const; 
    std::array<sf::Vertex, 4> m_verts;

    sf::Vector2f m_position;
    sf::Vector2f m_size;

    const LuaTexture* m_texture;
};
#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "LuaIncludes.h"

class LuaTexture {
  public:
    void init(const char* fileName);

    sf::Vector2u getSize() const;
    const sf::Texture& getTexture() const;

    static void luaRegister(lua_State* L);

  private:
    sf::Texture m_texture;
};
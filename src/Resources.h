#pragma once

#include "LuaIncludes.h"
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>

template <typename T>
class ResourceHolder {
  public:
    T& getResource(const std::string& name)
    {
        auto itr = m_resources.find(name);
        if (itr == m_resources.end()) {
            auto resource = std::make_unique<T>();
            resource->loadFromFile(name);
            m_resources.emplace(name, std::move(resource));
        }
        return *m_resources.at(name);
    }

  private:
    std::unordered_map<std::string, std::unique_ptr<T>> m_resources;
};

class ResourceManager {
  public:
    static ResourceManager& get()
    {
        static ResourceManager manager;
        return manager;
    }
    ResourceHolder<sf::Texture> textures;

  private:
    ResourceManager() = default;
};

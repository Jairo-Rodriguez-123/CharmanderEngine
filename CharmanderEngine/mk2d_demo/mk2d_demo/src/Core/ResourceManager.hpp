#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>
#include <stdexcept>

class ResourceManager {
public:
    static ResourceManager& I(){ static ResourceManager i; return i; }

    sf::Texture& texture(const std::string& path){
        auto it = textures.find(path);
        if(it!=textures.end()) return *it->second;
        auto tex = std::make_unique<sf::Texture>();
        if(!tex->loadFromFile("assets/" + path))
            throw std::runtime_error("No se pudo cargar textura: " + path);
        tex->setSmooth(true);
        auto& ref = *tex;
        textures[path] = std::move(tex);
        return ref;
    }
private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> textures;
};

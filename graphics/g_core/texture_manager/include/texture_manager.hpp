#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager{
public:
    static TextureManager& instance();

    sf::Texture* get_texture(const std::string& texture_path);
    sf::Font& get_font(const std::string& font_path);
private:
    TextureManager() = default;
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    std::unordered_map<std::string, sf::Texture> textures_;
    std::unordered_map<std::string, sf::Font> fonts_;
};
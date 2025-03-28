#include "texture_manager.hpp"

TextureManager& TextureManager::instance(){
    static TextureManager instance;
    return instance;
}

sf::Texture* TextureManager::get_texture(const std::string& texture_path){
    if (!textures_.contains(texture_path)){
        sf::Texture texture;
        if (!texture.loadFromFile(texture_path)){
            throw std::logic_error("Texture manager: Can't open texture");
        }
        textures_[texture_path] = std::move(texture);
    }
    return &textures_[texture_path];
}

sf::Font& TextureManager::get_font(const std::string& font_path){
    if (!fonts_.contains(font_path)){
        sf::Font font;
        if (!font.loadFromFile(font_path)){
            throw std::logic_error("Texture manager: can't open font");
        }
        fonts_[font_path] = std::move(font);
    }
    return fonts_[font_path];
}
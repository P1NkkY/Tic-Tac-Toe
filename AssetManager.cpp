#include "AssetManager.h"

void AssetManager::LoadTexture(std::string name, std::string fileName) {
    sf::Texture texture;

    if (texture.loadFromFile(fileName)) {
        m_textures[name] = texture;
    }
}

sf::Texture &AssetManager::GetTexture(std::string name) {
    return m_textures.at(name);
}

void AssetManager::LoadFont(std::string name, std::string fileName) {
    sf::Font font;

    if (font.loadFromFile(fileName)) {
        m_fonts[name] = font;
    }
}

sf::Font &AssetManager::GetFont(std::string name) { return m_fonts.at(name); }
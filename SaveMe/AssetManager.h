#pragma once

#include "SFML\Graphics.hpp"
#include <memory>

class AssetManager
{
public:
	static AssetManager& GetInstance();
	sf::Texture& GetTexture(const std::string name);
	sf::Font& GetFont(const std::string name);
private:
	AssetManager();
	~AssetManager();
	std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
	std::map<std::string, std::shared_ptr<sf::Font>> m_fonts;
};
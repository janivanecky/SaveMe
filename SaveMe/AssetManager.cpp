#include "AssetManager.h"

AssetManager::AssetManager() :
m_textures(),
m_fonts()
{

}

AssetManager::~AssetManager()
{
}

AssetManager& AssetManager::GetInstance()
{
	static AssetManager assetManager;
	return assetManager;
}

sf::Texture& AssetManager::GetTexture(std::string name)
{
	if (m_textures.find(name) == m_textures.end())
	{
		sf::Texture *newTex = new sf::Texture();
		newTex->loadFromFile(name);
		std::shared_ptr<sf::Texture> texture(newTex);
		m_textures.emplace(name, texture);
	}

	return *m_textures.at(name).get();
}

sf::Font& AssetManager::GetFont(std::string name)
{
	if (m_fonts.find(name) == m_fonts.end())
	{
		sf::Font *newTex = new sf::Font();
		newTex->loadFromFile(name);
		std::shared_ptr<sf::Font> texture(newTex);
		m_fonts.emplace(name, texture);
	}

	return *m_fonts.at(name).get();
}




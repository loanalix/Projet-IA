#include "pch.h"

namespace
{
	TextureManager* instance = nullptr;
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

TextureManager* TextureManager::GetInstance() 
{
	if (instance == nullptr) {
		instance = new TextureManager();

	}
	return instance;
}

sf::Texture TextureManager::GetTexture(std::string filepath)
{

	if (not mTextureMap.contains(filepath))
	{
		sf::Texture tempTexture;
		if (!tempTexture.loadFromFile(filepath))
		{
			std::cerr << "Failed to load" << filepath << std::endl;
		}
		mTextureMap[filepath] = tempTexture;
	}
	return mTextureMap[filepath];

}
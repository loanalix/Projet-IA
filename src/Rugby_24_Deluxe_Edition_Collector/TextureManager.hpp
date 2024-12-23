#pragma once

class TextureManager
{

public:

	std::map<std::string, sf::Texture> mTextureMap;

	TextureManager();
	virtual ~TextureManager();

	static TextureManager* GetInstance();

	sf::Texture GetTexture(std::string filepath);

};


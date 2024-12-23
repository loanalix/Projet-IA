#pragma once

class Animator
{
	std::vector<sf::Texture> mSprites;

	float mSpeed; //s
	float mLastFrameTime;
	int mFrameIndex;

public:

	Animator();
	virtual ~Animator();

	void Anime(sf::Sprite* sprite);
	void AddSprite(const std::string& path);
	void SetSpeed(float speed);
};


#include "pch.h"

Animator::Animator()
{
    mLastFrameTime = Time::GetInstance()->GetActualTime();
	mFrameIndex = 0;
	mSpeed = 0.05f;
}

Animator::~Animator()
{

}

void Animator::Anime(sf::Sprite* sprite)
{
	float now = Time::GetInstance()->GetActualTime();

    if (now - mLastFrameTime >= mSpeed)
    {
        mFrameIndex++;
		mLastFrameTime = now;

        if (mFrameIndex < mSprites.size())
        {
			sprite->setTexture(mSprites[mFrameIndex]);
		}
		else
		{
            mFrameIndex = 0;
			sprite->setTexture(mSprites[mFrameIndex]);
		}
    }
}

void Animator::AddSprite(const std::string& path)
{
	TextureManager* manager = TextureManager::GetInstance();

	sf::Texture Texture = manager->GetTexture(path);

	mSprites.push_back(Texture);
}

void Animator::SetSpeed(float speed)
{
	mSpeed = speed;
}

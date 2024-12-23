#include "pch.h"
#include "Ball.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"
#include <iostream>

#define GRAB_COOLDOWN 3.5f

Ball::Ball(const sf::Vector2f& position)
{
    sf::CircleShape* shape = new sf::CircleShape();

    mSize = 30.f;

	if (!mTexture.loadFromFile("..\\..\\..\\src\\rugby\\Assets\\Ball.png"))
	{
		return;
	}
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mTexture.getSize().x / 2.f, mTexture.getSize().y / 2.f);
	mSprite.setScale(mSize / mTexture.getSize().x, mSize / mTexture.getSize().y);
	mSprite.setPosition(position);

    shape->setRadius(mSize / 2.f);
    shape->setFillColor(sf::Color::Transparent);
    shape->setOrigin(mSize / 2.f, mSize / 2.f);
    shape->setPosition(position);
    mShape = shape;
	mOwner = nullptr;
}

Ball::~Ball()
{
}

void Ball::setOwner(Player* player)
{
	if (player != nullptr)
	{
		player->setState(Context::State::Grace);
		mOwner = player;
	}
}

void Ball::throwAt(Player* player, float speed)
{
	if (mOwner == nullptr) {
		std::cout << "The ball has no owner to throw it\n";
		return;
	}
	if (player == nullptr) {
		std::cout << "Couldn't find player to throw the ball at\n";
		return;
	}
	if (player == mOwner)
	{
		std::cout << "Can't throw the ball at yourself\n";
		return;
	}
		
	std::cout << mOwner->getName() << " throws the ball at " << player->getName() << std::endl;
	mOwner = nullptr;
	mDirection = Utils::Vector2Normalize(player->getPosition() - getPosition());
	mSpeed = speed;
}

void Ball::Update()
{
    Entity::Update();
    
	mSprite.setPosition(getPosition());

	// check for collision to get picked up by a player
	if (mOwner == nullptr)
	{
		std::vector<Player*> players = GameManager::Get()->getPlayers();
		for (auto p : players)
		{
			
			if (p->getState() != Context::State::Throw) {
				if (p->getShape().getGlobalBounds().contains(mShape->getPosition())) {
					setOwner(p);
					std::cout << p->getName() << " grabs the ball\n";
					break;
				}
			}
		}
	}
	else
	{

		if (mOwner->getTeam() == Context::Team::Green) {

			mShape->setPosition(mOwner->getShape().getPosition()+ sf::Vector2f(-15,10));
		}
		else{
			mShape->setPosition(mOwner->getShape().getPosition()+ sf::Vector2f(15,10));
		}
	}

	mSpeed *= 1-drag;
	GameManager::Get()->getWindow()->draw(mSprite);
}

Player* Ball::getOwner() {


	return mOwner;
}


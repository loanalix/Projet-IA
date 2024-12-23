#include "pch.h"
#include "Player.hpp"
#include "StateMachine/Behaviour.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>
#include "Context.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <chrono>
#include <random>

Player::Player(const sf::Vector2f& position, Behaviour* behaviour, Context::Team team, Context::Lane lane) : mState(Context::State::Idle), mInitialPosition(position)
{
    mBehaviour = behaviour;

	mName = Utils::getRandomName();

	// random stats

	// Utiliser std::random_device pour g�n�rer une graine unique
	std::random_device rd;
	std::mt19937 rng(rd());

	std::uniform_int_distribution<int> rTol(90, 170); // uniform, unbiased
	mEnemyTolerance = rTol(rng);

	std::uniform_int_distribution<int> rSi(35, 60);
	mSize = rSi(rng);

	mBaseSpeed = std::lerp(80.f, 40.f, (mSize - 35) / 25); // more tolerance = slower

	std::uniform_int_distribution<int> rGSp(60, 80);
	mGraceSpeed = rGSp(rng);

	std::uniform_int_distribution<int> rTSp(110, 200);
	mThrowSpeed = rTSp(rng);

	mSpeed = mBaseSpeed;

	
	mTeam = team;
	mLane = lane;

	std::uniform_int_distribution<int> rGrT(1, 4);
	graceTime = std::lerp(1, 4, (mSize - 35) / 25); // fatter = longer grace

	mTexture.setSmooth(true);
	std::string path = "..\\..\\..\\src\\rugby\\Assets\\Player.png";
	if(mName == "Kenny"){
		path = "..\\..\\..\\src\\rugby\\Assets\\Kenny.png";
	}
	else if (mName == "Stanley") {
		path = "..\\..\\..\\src\\rugby\\Assets\\Stanley.png";
	}
	else if (mName == "Dany") {
		path = "..\\..\\..\\src\\rugby\\Assets\\Dany.png";
	}

	if (!mTexture.loadFromFile(path))
	{
		std::cout << "Error loading player texture with path " << path;
		return;
	}
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(mTexture.getSize().x / 2.f, mTexture.getSize().y / 2.f);
	mSprite.setScale(mSize / mTexture.getSize().x, mSize / mTexture.getSize().y);
	mSprite.setPosition(position);


	if (team == Context::Team::Green) {
		mSprite.setColor(sf::Color::Green);
		mSprite.setScale(-mSprite.getScale().x, mSprite.getScale().y);
	}
	else if (team == Context::Team::Red) {
		mSprite.setColor(sf::Color::Red);
	}

    sf::CircleShape* shape = new sf::CircleShape(10);
	shape->setRadius(mSize / 2.f);
	shape->setOrigin(mSize / 2.f, mSize / 2.f);
	shape->setPosition(position);

	if (team == Context::Team::Green) {
		shape->setFillColor(sf::Color::Green);
	}
	else if (team == Context::Team::Red) {
		shape->setFillColor(sf::Color::Red);
	}
	shape->setFillColor(sf::Color::Transparent);

    mShape = shape;

	std::cout << "Hello I'm " << mName << ", instance " << this << std::endl;
}

Player::~Player()
{
}

void Player::Update()
{
	Entity::Update();

	if (mLane== Context::Lane::Top) 
	{ 
		if (getPosition().y < TOP_LANE_Y_MIN) 
		{
			setPosition(sf::Vector2f(getPosition().x, TOP_LANE_Y_MIN));
		}
		else if (getPosition().y > TOP_LANE_Y_MAX) 
		{
			setPosition(sf::Vector2f(getPosition().x, TOP_LANE_Y_MAX));
		}
	}
	else if (mLane == Context::Lane::Middle) 
	{
		if (getPosition().y < MIDDLE_LANE_Y_MIN) 
		{
			setPosition(sf::Vector2f(getPosition().x, MIDDLE_LANE_Y_MIN));
		}
		else if (getPosition().y > MIDDLE_LANE_Y_MAX) 
		{
			setPosition(sf::Vector2f(getPosition().x, MIDDLE_LANE_Y_MAX));
		}
	}
	else if (mLane == Context::Lane::Bottom) 
	{
		if (getPosition().y < BOTTOM_LANE_Y_MIN) 
		{
			setPosition(sf::Vector2f(getPosition().x, BOTTOM_LANE_Y_MIN));
		}
		else if (getPosition().y > BOTTOM_LANE_Y_MAX) 
		{
			setPosition(sf::Vector2f(getPosition().x, BOTTOM_LANE_Y_MAX));
		}
	}

	mSprite.setPosition(getPosition());

	// check for collision with other players
	std::vector<Player*> players = GameManager::Get()->getPlayers();
	for (auto p : players)
	{
		if (p != this) {
			if (p->getShape().getGlobalBounds().intersects(this->getShape().getGlobalBounds())) {
				// push players aside so they're not into each other
				if(p == GameManager::Get()->getBall()->getOwner() && this->getTeam() != p->getTeam() && p->getState() != Context::State::Grace)
				{
					GameManager::Get()->getBall()->setOwner(this);
					p->setState(Context::State::Defense);
				}

				sf::Vector2f dist = p->getPosition() - this->getPosition();
				sf::Vector2f norm =  Utils::Vector2Normalize(dist);

				p->setPosition(p->getPosition() + norm);
				this->setPosition(this->getPosition() - norm);
				//std::cout << "Collision\n";
			}
		}
	}

	mBehaviour->Update(this);

	// show lines between players
	if (GameManager::Get()->getBall()->getOwner() == this)
	{
		for(auto team: players)
		{
			if(team != this && team->getTeam() == this->getTeam())
			{
				//angles betwen players
				sf::Vector2f direction = team->getPosition() - getPosition();
				float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

				sf::RectangleShape line(sf::Vector2f(length, 5.f)); 
				line.setFillColor(sf::Color::Yellow);

				line.setPosition(getPosition());
				line.setRotation(atan2(direction.y, direction.x) * 180.f / 3.14159f);
			}
		}
	}
	else
	{
		sf::CircleShape* shape = dynamic_cast<sf::CircleShape*>(mShape);
		shape->setOutlineThickness(0);
	}	

	// draw outline if in grace state
	if (mState == Context::State::Grace)
	{
		sf::CircleShape* shape = dynamic_cast<sf::CircleShape*>(mShape);
		shape->setOutlineThickness(2);
		shape->setOutlineColor(sf::Color::Blue);
	}
	else
	{
		sf::CircleShape* shape = dynamic_cast<sf::CircleShape*>(mShape);
		shape->setOutlineThickness(0);
	}
	
	
#ifdef _DEBUG

	// draw enemy threshold circle
	sf::CircleShape* dshape = new sf::CircleShape();
	dshape->setOutlineThickness(2);
	dshape->setOutlineColor(sf::Color::Red);
	dshape->setRadius(mEnemyTolerance);
	dshape->setOrigin(mEnemyTolerance, mEnemyTolerance);
	dshape->setPosition(getPosition());
	dshape->setFillColor(sf::Color::Transparent);


	// draw state text above player
	sf::Text* text = new sf::Text;
	text->setFont(*GameManager::Get()->getFont());
	text->setCharacterSize(12);
	text->setFillColor(sf::Color::Magenta);
	text->setPosition(getPosition() + sf::Vector2f(-20, -60));

	switch (mState)
	{
	case Context::State::Idle:
		text->setString("Idle");
		break;
	case Context::State::Offense:
		text->setString("Offense");
		break;
	case Context::State::Defense:
		text->setString("Defense");
		break;
	case Context::State::Fetch:
		text->setString("Fetch");
		break;
	case Context::State::HoldingBall:
		text->setString("Holding Ball");
		break;
	case Context::State::Grace:
		text->setString("Grace");
		break;
	case Context::State::Throw:
		text->setString("Throw");
		break;
	default:
		text->setString("Default");
		break;
	}
	GameManager::Get()->getWindow()->draw(*text);
#endif // DEBUG	

	// draw player name
	sf::Text* nameText = new sf::Text;
	nameText->setFont(*GameManager::Get()->getFont());
	nameText->setCharacterSize(12);
	nameText->setFillColor(sf::Color::Cyan);
	nameText->setString(mName);
	nameText->setOrigin(nameText->getGlobalBounds().getSize() / 2.f + nameText->getLocalBounds().getPosition());
	nameText->setPosition(getPosition() + sf::Vector2f(0, -35));

	GameManager::Get()->getWindow()->draw(*nameText);
	GameManager::Get()->getWindow()->draw(mSprite);	
}

double Player::getGraceTime() const
{
	return graceTime;
}

float Player::getBaseSpeed() const
{
	return mBaseSpeed;
}
float Player::getGraceSpeed() const
{
	return mGraceSpeed;
}

float Player::getEnemyThreshold() const
{
	return mEnemyTolerance;
}

float Player::getThrowSpeed() const
{
	return mThrowSpeed;
}

std::string Player::getName() const
{
	return mName;
}

void Player::endStateAction()
{
	mBehaviour->End(this);
}

void Player::startStateAction()
{
	mBehaviour->Start(this);
}

bool Player::hasGrace() const
{
	return mState == Context::State::Grace;
}

Context::Team Player::getTeam() const
{
	return mTeam;
}

Context::State Player::getState() const
{
    return mState;
}

void Player::setSpeed(float speed)
{
	mSpeed = speed;
}

void Player::setState(Context::State new_state) 
{
	endStateAction();
    mState = new_state;
	startStateAction();
}

sf::Vector2f Player::getInitialPosition() const
{
	return mInitialPosition;
}

void Player::resetPosition()
{
	setPosition(mInitialPosition);
}

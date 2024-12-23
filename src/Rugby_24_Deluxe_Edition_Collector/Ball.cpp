#include "pch.h"

Ball::Ball(const sf::Vector2f& position)
{
    mOwner = nullptr;
    mLastOwner = nullptr;

	mLobeTarget = sf::Vector2f(0, 0);
	mIsLobe = false;
    mLobeDistance = 0;
    mMidLobe = false;

    sf::CircleShape* shape = new sf::CircleShape();

    mPosition = position;

    mSize = 30.f;
    shape->setRadius(mSize / 2.f);
    shape->setFillColor(sf::Color::Transparent);
    shape->setOrigin(mSize / 2.f, mSize / 2.f);
    shape->setPosition(mPosition);
    mShape = shape;

    mSpeed = 240.f;

    if (!mTexture.loadFromFile("..\\..\\..\\src\\Rugby_24_Deluxe_Edition_Collector\\Assets\\Ball.png"))
    {
        std::cerr << "Failed to load Ball.png" << std::endl;
    }

    mSprite.setTexture(mTexture);
    mSprite.setScale(mSize / mSprite.getLocalBounds().width, mSize / mSprite.getLocalBounds().height);
    mSprite.setPosition(mPosition);
    mSprite.setOrigin(mTexture.getSize().x / 2, mTexture.getSize().y / 2);
}

Ball::~Ball()
{
}

void Ball::Update()
{
    if (mOwner == nullptr && mIsLobe == false)
    {
        move();
        DetectCollisionPlayers();
    }
    else if (mIsLobe == true)
    {
        Lobe();
    }
    else {
        MoveToOwner();
    }
}

void Ball::DetectCollisionPlayers()
{
	for (Player* player : GameManager::Get()->getPlayers())
	{
        if (DetectCollision(player,0))
        {
            if (player != mLastOwner)
            {
                setOwner(player);
				return;
            }
        }
	}
}

void Ball::Lobe()
{

    //move to the the mLobeTarget

	sf::Vector2f direction = mLobeTarget - mPosition;

	direction = Utils::Vector2Normalize(direction);

    float dt = GameManager::Get()->getDeltaTime();

    mPosition.x += dt * mSpeed * direction.x;
    mPosition.y += dt * mSpeed * direction.y;

	float distanceToTarget = Utils::GetDistance(mPosition, mLobeTarget);

    float Pourcent = distanceToTarget * M_PI / mLobeDistance;


    if (!mMidLobe) {

        mSprite.setScale(mSprite.getScale().x  - cos(Pourcent) / 10, mSprite.getScale().y - cos(Pourcent) / 10);
    }
    else {
        mSprite.setScale(mSprite.getScale().x - cos(Pourcent) / 10, mSprite.getScale().y - cos(Pourcent) / 10);
    }

    if (distanceToTarget <= mLobeDistance / 2)
        mMidLobe = true;

    if (distanceToTarget <= 2.f)
    {
		mIsLobe = false;
		mLobeTarget = sf::Vector2f(0, 0);
        mDirection = sf::Vector2f(0, 0);
        mSprite.setScale(mSize / mSprite.getLocalBounds().width, mSize / mSprite.getLocalBounds().height);
        mMidLobe = false;
    }
}

void Ball::move()
{
    float dt = GameManager::Get()->getDeltaTime();

    mPosition.x += dt * mSpeed * mDirection.x;
    mPosition.y += dt * mSpeed * mDirection.y;
}

void Ball::MoveToOwner() {
    if (mOwner != nullptr)
    {
        mPosition = mOwner->getPosition();
    }
}

void Ball::Draw(sf::RenderWindow* window)
{
    mShape->setPosition(mPosition);
    mSprite.setPosition(mPosition);
    window->draw(mSprite);
}

Player* Ball::getOwner() const
{
	return mOwner;
}

void Ball::setOwner(Player* owner)
{
    owner->Sprint();
	mOwner = owner;
    mLastOwner = owner;
}

void Ball::resetOwner()
{
    mOwner = nullptr;
}
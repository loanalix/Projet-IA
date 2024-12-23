#include "pch.h"

Entity::Entity()
{ 
}

Entity::~Entity()
{ 
}

void Entity::setPosition(const sf::Vector2f& position)
{
    mPosition = position;
}

const sf::Vector2f& Entity::getPosition() const
{
    return mPosition;
}

//void Entity::move()
//{
//	float dt = GameManager::Get()->getDeltaTime();
//
//	mPosition.x += dt * mSpeed * mDirection.x;
//	mPosition.y += dt * mSpeed * mDirection.y;
//}

bool Entity::DetectCollision(Entity* entity, int dst) const
{
	float distance = Utils::GetDistance(getPosition(), entity->getPosition());
	float distanceMin = (entity->mSize / 2) + (mSize / 2) + dst;

	if (distance < distanceMin)
	{
		return true;

	}
	return false;
}

void Entity::setDirection(const sf::Vector2f& new_direction)
{
    mDirection = new_direction;
}

void Entity::setDirectionByPosition(const sf::Vector2f& position)
{
    setDirection(Utils::Vector2Normalize(position - getPosition()));
}

const sf::Shape& Entity::getShape()
{
    return *mShape;
}

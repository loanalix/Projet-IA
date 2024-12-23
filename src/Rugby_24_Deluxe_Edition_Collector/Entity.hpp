#pragma once

#include <SFML/System/Vector2.hpp>

namespace sf 
{
	class Shape;
}

class Entity
{
protected:
    sf::Vector2f mDirection;
    float mSize;
	float mSpeed;

    sf::Vector2f mPosition;

	sf::Shape* mShape;

    Entity();

public:
    double mFullTime;

    virtual void Update() = 0;
	virtual void Draw(sf::RenderWindow* window) = 0;

    ~Entity();
    void setDirection(const sf::Vector2f& direction);
    void setDirectionByPosition(const sf::Vector2f& position);

    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;
    //void move();
    virtual void move() = 0;
    bool DetectCollision(Entity* entity,int dst) const;

    const sf::Shape& getShape();
};

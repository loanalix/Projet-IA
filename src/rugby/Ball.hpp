#pragma once

#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics.hpp>

class Player;

class Ball : public Entity
{
	float drag = 0.01f;
	Player* mOwner = nullptr;
	sf::Texture mTexture;
	sf::Sprite mSprite;
public:
    Ball(const sf::Vector2f& position);
    ~Ball();

	void setOwner(Player* player);
	void throwAt(Player* player, float speed);

    void Update() override;
    Player* getOwner();
};

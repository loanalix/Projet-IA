#pragma once

#include "Entity.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class Player;

class Ball : public Entity
{
	Player* mOwner;
	Player* mLastOwner;

	sf::Texture mTexture;
	sf::Sprite mSprite;

public:
	bool mIsLobe;
	sf::Vector2f mLobeTarget;
	int mLobeDistance;
	bool mMidLobe;

	Ball(const sf::Vector2f& position);
    ~Ball();

    void Update() override;
	void DetectCollisionPlayers();
	void Lobe();
	void move() override;
	void MoveToOwner();
	void Draw(sf::RenderWindow* window) override;
    Player* getOwner() const;
	void setOwner(Player* owner);
	void resetOwner();

	void flying();
};

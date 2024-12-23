#pragma once

#include "Entity.hpp"
#include "Context.hpp"
#include <SFML/Graphics.hpp>

class Behaviour;

class Player : public Entity
{
    Context::State mState;
    Behaviour * mBehaviour;
    Context::Team mTeam;
    Context::Lane mLane;
    sf::Vector2f mInitialPosition;
	sf::Texture mTexture;
	sf::Sprite mSprite;

    std::string mName;

    // stats
    float mBaseSpeed;
    float mGraceSpeed;
    float mEnemyTolerance;
	float mThrowSpeed;

    double graceTime;

    const float TOP_LANE_Y_MIN = 0;
    const float TOP_LANE_Y_MAX = 360;

    const float MIDDLE_LANE_Y_MIN = 180;
    const float MIDDLE_LANE_Y_MAX = 540;

    const float BOTTOM_LANE_Y_MIN = 360;
    const float BOTTOM_LANE_Y_MAX = 720;

public:
    Player(const sf::Vector2f& position, Behaviour* behaviour, Context::Team team, Context::Lane lane);
    ~Player();

	void setSpeed(float speed);

    void Update() override;

	bool hasGrace() const;
	double getGraceTime() const;
	float getBaseSpeed() const;
	float getGraceSpeed() const;
	float getEnemyThreshold() const;
	float getThrowSpeed() const;
	std::string getName() const;

	void endStateAction();
    void startStateAction();

	Context::Team getTeam() const;

    Context::State getState() const;
    void setState(Context::State);

    sf::Vector2f getInitialPosition() const;
	void resetPosition();
};

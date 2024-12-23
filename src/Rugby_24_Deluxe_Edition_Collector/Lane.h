#pragma once

class Lane
{
	int mTopLane, mBottomLane;
public:
	Lane(int topLane, int bottomLane);
	~Lane();

	int getTopLane() const;
	int getBottomLane() const;
	bool isInLane(sf::Vector2f vector2);
	int GetCorrectPosition(sf::Vector2f vector2);
};
#include "pch.h"


Lane::Lane(int topLane, int bottomLane)
{
	mTopLane = topLane;
	mBottomLane = bottomLane;
}

Lane::~Lane()
{
}

int Lane::getTopLane() const
{
	return mTopLane;
}

int Lane::getBottomLane() const
{
	return mBottomLane;
}

bool Lane::isInLane(sf::Vector2f vector2)
{
	if (vector2.y >= mTopLane && vector2.y <= mBottomLane)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Lane::GetCorrectPosition(sf::Vector2f vector2)
{
	if (vector2.y <= mTopLane)
	{
		return mTopLane;
	}
	else {
		return mBottomLane;
	}
}

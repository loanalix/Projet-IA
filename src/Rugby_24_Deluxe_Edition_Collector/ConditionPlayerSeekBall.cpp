#include "pch.h"

ConditionPlayerSeekBall::ConditionPlayerSeekBall()
{
}

ConditionPlayerSeekBall::~ConditionPlayerSeekBall()
{
}

bool ConditionPlayerSeekBall::Test(Player* player)
{
	//check if the ball is in the half part of the terrain for the defender
	if (player->GetIsDefender())
	{
		if (player->isBlack())
		{
			if (GameManager::Get()->getBall()->getPosition().x < 640)
			{
				return false;
			}
		}
		else
		{
			if (GameManager::Get()->getBall()->getPosition().x > 640)
			{
				return false;
			}
		}
	}

	Player* owner = GameManager::Get()->getBall()->getOwner();

	if (owner == nullptr)
	{
		return true;
	}
	return false;
}

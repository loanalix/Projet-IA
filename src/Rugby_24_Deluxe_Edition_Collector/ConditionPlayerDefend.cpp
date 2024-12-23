#include "pch.h"

ConditionPlayerDefend::ConditionPlayerDefend()
{
}

ConditionPlayerDefend::~ConditionPlayerDefend()
{
}

bool ConditionPlayerDefend::Test(Player* player)
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

	if (GameManager::Get()->getBall()->getOwner() == nullptr)
	{
		return false;
	}

	bool ownerIsBlack = GameManager::Get()->getBall()->getOwner()->isBlack();
	bool playerIsBlack = player->isBlack();

	if (ownerIsBlack != playerIsBlack)
	{
		return true;
	}
	return false;
}

#include "pch.h"

ConditionPlayerHaveBall::ConditionPlayerHaveBall()
{
}

ConditionPlayerHaveBall::~ConditionPlayerHaveBall()
{
}

bool ConditionPlayerHaveBall::Test(Player* player)
{
	Player* owner = GameManager::Get()->getBall()->getOwner();

	if (owner == player)
	{
		return true;
	}
	return false;
}

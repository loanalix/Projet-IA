#include "pch.h"

ConditionPlayerRunner::ConditionPlayerRunner()
{
}

ConditionPlayerRunner::~ConditionPlayerRunner()
{
}

bool ConditionPlayerRunner::Test(Player* player)
{
	std::vector<Player*> players;

	Player* owner = GameManager::Get()->getBall()->getOwner();

	if (owner == nullptr)
	{
		return false;
	}

	for (Player* player2 : GameManager::Get()->getPlayers())
	{
		if (player2->GetIsDefender() || owner == player2 || player->isBlack() != player2->isBlack())
		{

		}
		else {
			players.push_back(player2);
		}

	}


	float distance = 0;
	Player* further = nullptr;

	for (Player* player2 : players)
	{
		float tempDistance = Utils::GetDistance(owner->getPosition(), player2->getPosition());

		if (tempDistance > distance)
		{
			distance = tempDistance;
			further = player2;
		}
	}

	if (further == nullptr || further == player)
	{
		return true;
	}

	return false;
}

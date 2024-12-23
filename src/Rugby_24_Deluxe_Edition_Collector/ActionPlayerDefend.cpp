#include "pch.h"


ActionPlayerDefend::ActionPlayerDefend()
{
}

ActionPlayerDefend::~ActionPlayerDefend()
{
}

void ActionPlayerDefend::Start(Player* player)
{
}

void ActionPlayerDefend::Update(Player* player)
{
	player->MoveToBall();
	if (player->IsTouchingEnemyOwner())
	{
		GameManager::Get()->getBall()->setOwner(player);
	}
}

void ActionPlayerDefend::End(Player* player)
{
}
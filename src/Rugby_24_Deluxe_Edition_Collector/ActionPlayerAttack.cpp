#include "pch.h"


ActionPlayerAttack::ActionPlayerAttack()
{
}

ActionPlayerAttack::~ActionPlayerAttack()
{
}

void ActionPlayerAttack::Start(Player* player)
{

}

void ActionPlayerAttack::Update(Player* player)
{
	player->MoveToGoal();
}

void ActionPlayerAttack::End(Player* player)
{

}
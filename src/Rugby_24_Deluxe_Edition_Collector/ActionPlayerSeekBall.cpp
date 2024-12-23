#include "pch.h"


ActionPlayerSeekBall::ActionPlayerSeekBall()
{
}

ActionPlayerSeekBall::~ActionPlayerSeekBall()
{
}

void ActionPlayerSeekBall::Start(Player* player)
{
}

void ActionPlayerSeekBall::Update(Player* player)
{
	player->MoveToBall();
}

void ActionPlayerSeekBall::End(Player* player)
{
}
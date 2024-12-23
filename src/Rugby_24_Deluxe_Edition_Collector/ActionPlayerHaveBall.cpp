#include "pch.h"


ActionPlayerHaveBall::ActionPlayerHaveBall()
{
}

ActionPlayerHaveBall::~ActionPlayerHaveBall()
{
}

void ActionPlayerHaveBall::Start(Player* player)
{
	player->Sprint();
	////Get the actual time with chrono
	//auto start = std::chrono::high_resolution_clock::now();
	////convert start in float
	//player->invincibleStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
	//player->speedBoostStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();

	//player->invincible = true;
	//player->speedBoost = true;
	//player->SetMaxSpeed();
}

void ActionPlayerHaveBall::Update(Player* player)
{
	player->MoveToGoal();
}

void ActionPlayerHaveBall::End(Player* player)
{
}
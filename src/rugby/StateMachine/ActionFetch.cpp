#include "pch.h"
#include "ActionFetch.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"


void ActionFetch::Start(Player* Player)
{
}

void ActionFetch::Update(Player* Player)
{
	sf::Vector2f direction = GameManager::Get()->getBall()->getPosition() - Player->getPosition();

	Player->setDirection(Utils::Vector2Normalize(direction));
}

void ActionFetch::End(Player* Player)
{
}

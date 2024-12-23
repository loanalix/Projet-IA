#include "pch.h"
#include "ActionDefending.hpp"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"

void ActionDefending::Start(Player* player)
{
}

void ActionDefending::Update(Player* player)
{
	Player* ballOwner = GameManager::Get()->getBall()->getOwner();

	if (ballOwner != nullptr) {

		sf::Vector2f direction = GameManager::Get()->getBall()->getOwner()->getPosition() - player->getPosition();

		player->setDirection(Utils::Vector2Normalize(direction));
	}

}

void ActionDefending::End(Player* player)
{
}

#include "pch.h"
#include "ConditionEnemyNearby.h"
#include "Player.hpp"
#include "GameManager.hpp"
#include "Utils.hpp"
#include <iostream>

bool ConditionEnemyNearby::Test(Player* player) {
	std::vector<Player*> players = GameManager::Get()->getPlayers();
	for (auto p : players) {
		if (p != player) {
			if (p->getTeam() != player->getTeam()) {
				float dist = Utils::Vector2Magnitude(p->getPosition() - player->getPosition());
				if(dist < player->getEnemyThreshold())
				{
					if(player->getTeam() == Context::Team::Red && p->getPosition().x < player->getPosition().x)
					{
					#ifdef _DEBUG
						std::cout << player->getName() << "is scared" << std::endl;
					#endif // _DEBUG

						return true == mExpectedValue;

					}
					if (player->getTeam() == Context::Team::Green && p->getPosition().x > player->getPosition().x)
					{
					#ifdef _DEBUG
						std::cout << player->getName() << "is scared" << std::endl;
					#endif // _DEBUG
						return true == mExpectedValue;
					}
				}
			}
		}
	}
	return false == mExpectedValue;
}
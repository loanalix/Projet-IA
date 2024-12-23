#include "pch.h"
#include "ConditionTeamHasBall.h"
#include "GameManager.hpp"
#include "Player.hpp"

bool ConditionTeamHasBall::Test(Player* player){
	auto players = GameManager::Get()->getEntities();

	for(auto ent : players){
		// check if its player class
		Player* p = dynamic_cast<Player*>(ent);
		if(p!=NULL && p == GameManager::Get()->getBall()->getOwner())
		{
			if (mExpectedValue == Context::Team::Friendly) {
				return player->getTeam() == p->getTeam();
			}
			if (mExpectedValue == Context::Team::Enemy) {
				return player->getTeam() != p->getTeam();
			}
			return p->getTeam() == mExpectedValue;
		}
	}
	return Context::Team::None == mExpectedValue;
}
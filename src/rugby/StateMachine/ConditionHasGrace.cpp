#include "pch.h"
#include "ConditionHasGrace.h"
#include "Player.hpp"

bool ConditionHasGrace::Test(Player* player) {
	if(player->hasGrace())
		return true == mExpectedValue;
	return false == mExpectedValue;
}
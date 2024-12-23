#pragma once

#include "Condition.hpp"
#include "Context.hpp"

class Player;

class ConditionTeamHasBall : public Condition
{
    Context::Team mExpectedValue;
public:
    ConditionTeamHasBall(Context::Team expected_value = Context::Team::Friendly) : mExpectedValue(expected_value) {};
    bool Test(Player* Player) override;
    ~ConditionTeamHasBall() {};

};

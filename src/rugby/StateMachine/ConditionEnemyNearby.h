#pragma once

#include "Condition.hpp"

class Tower;
class Enemy;

class ConditionEnemyNearby : public Condition
{
    bool mExpectedValue;
public:
    ConditionEnemyNearby(bool expected_value = true) : mExpectedValue(expected_value) {};
    bool Test(Player* player) override;

    ~ConditionEnemyNearby() {};

};

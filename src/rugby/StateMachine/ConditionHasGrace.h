#pragma once

#include "Condition.hpp"

class Tower;
class Enemy;

class ConditionHasGrace : public Condition
{
    bool mExpectedValue;
public:
    ConditionHasGrace(bool expected_value = true) : mExpectedValue(expected_value) {};
    bool Test(Player* player) override;

    ~ConditionHasGrace() {};

};

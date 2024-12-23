#pragma once
#include "Action.hpp"

class Player;

class ActionGrace : public Action
{
    double mStartTime;
public:
    void Start(Player * Player) override;
    void Update(Player * Player) override;
    void End(Player * Player) override;
};
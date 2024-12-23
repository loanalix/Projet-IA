#pragma once
#include "Action.hpp"

class Player;

class ActionDefending : public Action
{
public:
    void Start(Player * player) override;
    void Update(Player * player) override;
    void End(Player * player) override;
};
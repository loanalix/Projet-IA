#pragma once
#include "Action.hpp"

class Player;

class ActionFetch : public Action
{
public:
    void Start(Player * Player) override;
    void Update(Player * Player) override;
    void End(Player * Player) override;
};
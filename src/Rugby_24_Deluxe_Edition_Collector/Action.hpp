#pragma once

class Player;

class Action
{
public:
    virtual void Start(Player * player) = 0;
    virtual void Update(Player * player) = 0;
    virtual void End(Player * player) = 0;
};
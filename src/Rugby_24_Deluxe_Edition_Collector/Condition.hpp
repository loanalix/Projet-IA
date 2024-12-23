#pragma once

class Playground;
class Player;

class Condition 
{
public:
    virtual bool Test(Player * player) = 0;
};
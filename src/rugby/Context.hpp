#pragma once
#include <string>
#include <random>
namespace Context
{
enum class State 
{
    // Etat des joueurs
    Idle,
    Offense,
    Defense,
    HoldingBall,
	Fetch,
    Grace,
    Throw
};

enum class Team
{
    // Equipe des joueurs
	None,
    Friendly,
	Enemy,
    Green,
	Red,
};

enum class Lane 
{
    Top,
    Middle,
    Bottom
};
};
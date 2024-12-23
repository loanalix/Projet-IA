#pragma once

class DebugClass
{
	Player* mPlayer;
	bool toggleLine;

public:
	DebugClass();
	~DebugClass() {};
	void Update();
	void FindPlayer();
	void ForceThrow();
	void SetPlayer(Player* player);
	void ResetPlayer();
	void SetPlayerPositionOnMouse();
	void handleUserInput(sf::Event event);

	void DebugShowTeammate();
};

#pragma once
#include <vector>

class Entity;

namespace sf 
{
	class RenderWindow;
}

class GameManager
{
	std::vector<Player*> mPlayers;
	Ball* mBall;
	sf::RenderWindow* mWindow;
	float mDeltaTime;

	int mWhiteTeamPoints;
	int mBlackTeamPoints;

	sf::Font mFont;

	sf::Text mWhiteScoreText;
	sf::Text mBlackScoreText;

	sf::Text mWinText;

	DebugClass* mDebug;

	Animator* mAnimator;

	GameManager();

	void resetPlaces();
	void CheckGoal();
	void CheckWin();

public:
	sf::Texture mBallTexture;

	~GameManager();

	static GameManager* Instantiate();
	void init(sf::Font font);
	void RandomGenerationPlayer(sf::Vector2f pos, int number, Behaviour* behaviour, Animator* animator, Lane* lane,
	                            sf::Font font, bool team, bool defender);
	static GameManager* Get();
	void Update();
	void Draw();

	void setWindow(sf::RenderWindow* window);
	sf::RenderWindow* getWindow();

	void setDeltaTime(float deltaTime);
	float getDeltaTime() const;
	std::vector<Player*> getPlayers() const;
	Ball* getBall() const;
	Animator* getAnimator() const;
	void handleUserInput(sf::Event event);

	friend Entity;
};
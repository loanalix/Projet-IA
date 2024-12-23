#pragma once

#include <vector>
#include "Player.hpp"
#include "Ball.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Entity;

namespace sf 
{
	class RenderWindow;
}

class GameManager
{
	std::vector<Entity*> mEntities;
	sf::RenderWindow* mWindow;
	sf::Font mFont;

	sf::Texture mBackgroundTexture;
	sf::Sprite mBackgroundSprite;

	sf::RectangleShape mGoalR;
	sf::RectangleShape mGoalG;

	float mDeltaTime;

	bool mGameOver = false;

	int mScoreGreen;  
	int mScoreRed;    
	sf::Text mScoreTextGreen; 
	sf::Text mScoreTextRed;


	GameManager();

	void addEntity(Entity* entity);

	void DebugMovePlayer();

	void ForcePassBall();

public:
	~GameManager();

	static GameManager* Instantiate();
	static GameManager* Get();
	void Update();
	void Draw();

	sf::Font* getFont();
	void setWindow(sf::RenderWindow* window);
	void setDeltaTime(float deltaTime);
	void CheckWin();
	void Reset(Context::Team team);
	float getDeltaTime() const;
	Ball* getBall();
	sf::RenderWindow* getWindow();

	std::vector<Entity*> getEntities();
	std::vector<Player*> getPlayers(Context::Team team = Context::Team::None);

	friend Entity;
};


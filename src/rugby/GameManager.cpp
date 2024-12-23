#include "pch.h"
#include "GameManager.hpp"

#include "StateMachine/Behaviour.hpp"

#include "Ball.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "StateMachine/ActionIdle.hpp"
#include "StateMachine/Transition.hpp"
#include "Ball.hpp"

#include "StateMachine/ActionDefending.hpp"
#include "StateMachine/ActionFetch.hpp"
#include "StateMachine/ActionGrace.hpp"
#include "StateMachine/ActionAttacking.hpp"
#include "StateMachine/ActionHoldingBall.hpp"
#include "StateMachine/ActionPass.hpp"

#include "StateMachine/ConditionHasGrace.h"
#include "StateMachine/ConditionTeamHasBall.h"
#include "StateMachine/ConditionEnemyNearby.h"

namespace 
{
static GameManager* mInstance = nullptr;
}

GameManager::GameManager() : mScoreGreen(0), mScoreRed(0)
{
	mDeltaTime = 0.0f;
    Behaviour * behaviour = new Behaviour();

	if (!mBackgroundTexture.loadFromFile("..\\..\\..\\src\\rugby\\Assets\\Background.png")) // Replace with your file path
	{
		std::cerr << "Failed to load background texture" << std::endl;
	}

	// Set up the background sprite
	mBackgroundSprite.setTexture(mBackgroundTexture);



	// init behaviour here
	Action * actionIdle = new ActionIdle();
	behaviour->AddAction(Context::State::Idle, actionIdle);


	///---------------------------------------------------------------------///
	///								Offense									///
	///---------------------------------------------------------------------///

	Action* actionAttacking = new ActionAttacking();
	behaviour->AddAction(Context::State::Offense, actionAttacking);

	Transition * toOffenseTransition = new Transition();
	toOffenseTransition->setTargetState(Context::State::Offense);
	toOffenseTransition->addCondition(new ConditionTeamHasBall());
	behaviour->AddTransition(Context::State::Idle, toOffenseTransition);
	behaviour->AddTransition(Context::State::Fetch, toOffenseTransition);
	behaviour->AddTransition(Context::State::Throw, toOffenseTransition);
	behaviour->AddTransition(Context::State::Defense, toOffenseTransition);


	///---------------------------------------------------------------------///
	///								Fetch									///
	///---------------------------------------------------------------------///

	Action* actionFetch = new ActionFetch();
	behaviour->AddAction(Context::State::Fetch, actionFetch);

	Transition* toFetchTransition = new Transition();
	toFetchTransition->setTargetState(Context::State::Fetch);
	toFetchTransition->addCondition(new ConditionTeamHasBall(Context::Team::None));
	behaviour->AddTransition(Context::State::Idle, toFetchTransition);
	behaviour->AddTransition(Context::State::Offense, toFetchTransition);
	behaviour->AddTransition(Context::State::Defense, toFetchTransition);


	///---------------------------------------------------------------------///
	///								Defense									///
	///---------------------------------------------------------------------///

	Action* actionDefending = new ActionDefending();
	behaviour->AddAction(Context::State::Defense, actionDefending);

	Transition* toDefenseTransition = new Transition();
	toDefenseTransition->setTargetState(Context::State::Defense);
	toDefenseTransition->addCondition(new ConditionTeamHasBall(Context::Team::Enemy));
	behaviour->AddTransition(Context::State::Fetch, toDefenseTransition);
	behaviour->AddTransition(Context::State::Idle, toDefenseTransition);
	behaviour->AddTransition(Context::State::Offense, toDefenseTransition);
	behaviour->AddTransition(Context::State::Throw, toDefenseTransition);


	///---------------------------------------------------------------------///
	///								Grace									///
	///---------------------------------------------------------------------///

	Action* actionGrace = new ActionGrace();
	behaviour->AddAction(Context::State::Grace, actionGrace);

	Transition* graceToHoldingBallTransition = new Transition();
	graceToHoldingBallTransition->setTargetState(Context::State::HoldingBall);
	graceToHoldingBallTransition->addCondition(new ConditionHasGrace(false));
	behaviour->AddTransition(Context::State::Grace, graceToHoldingBallTransition);


	///---------------------------------------------------------------------///
	///								HoldBall								///
	///---------------------------------------------------------------------///

	Action* actionHoldingBall = new ActionHoldingBall();
	behaviour->AddAction(Context::State::HoldingBall, actionHoldingBall);


	///---------------------------------------------------------------------///
	///								Throw									///
	///---------------------------------------------------------------------///

	Action* actionThrow = new ActionPass();
	behaviour->AddAction(Context::State::Throw, actionThrow);

	Transition* toThrowTransition = new Transition();
	toThrowTransition->setTargetState(Context::State::Throw);
	toThrowTransition->addCondition(new ConditionEnemyNearby());
	behaviour->AddTransition(Context::State::HoldingBall, toThrowTransition);



    Player * p1 = new Player(sf::Vector2f(100, 100), behaviour,Context::Team::Green,Context::Lane::Top);
    Player * p2 = new Player(sf::Vector2f(200, 200), behaviour,Context::Team::Green,Context::Lane::Top);
    Player * p3 = new Player(sf::Vector2f(300, 360), behaviour,Context::Team::Green, Context::Lane::Middle);
    Player * p4 = new Player(sf::Vector2f(200, 520), behaviour,Context::Team::Green, Context::Lane::Bottom);
    Player * p5 = new Player(sf::Vector2f(100, 620), behaviour,Context::Team::Green, Context::Lane::Bottom);
    Player * p6 = new Player(sf::Vector2f(1180, 100), behaviour, Context::Team::Red, Context::Lane::Top);
    Player * p7 = new Player(sf::Vector2f(1080, 200), behaviour, Context::Team::Red, Context::Lane::Top);
    Player * p8 = new Player(sf::Vector2f(980, 360), behaviour, Context::Team::Red, Context::Lane::Middle);
    Player * p9 = new Player(sf::Vector2f(1080, 520), behaviour, Context::Team::Red,Context::Lane::Bottom);
    Player * p10 = new Player(sf::Vector2f(1180, 620), behaviour, Context::Team::Red,Context::Lane::Bottom);

    mEntities.push_back(p1);
    mEntities.push_back(p2);
    mEntities.push_back(p3);
    mEntities.push_back(p4);
    mEntities.push_back(p5);
    mEntities.push_back(p6);
    mEntities.push_back(p7);
    mEntities.push_back(p8);
    mEntities.push_back(p9);
    mEntities.push_back(p10);


    Ball * ball = new Ball(sf::Vector2f(540, 360));
	mEntities.push_back(ball);

	if (!mFont.loadFromFile("..\\..\\..\\src\\rugby\\Assets\\Hack-Regular.ttf"))
	{
		std::cerr << "Failed to load font" << std::endl;
	}


	mScoreTextGreen.setFont(mFont);
	mScoreTextGreen.setCharacterSize(24);
	mScoreTextGreen.setFillColor(sf::Color::Black);
	mScoreTextGreen.setPosition(10, 10);
	mScoreTextGreen.setString("Score : 0");

	mScoreTextRed.setFont(mFont);
	mScoreTextRed.setCharacterSize(24);
	mScoreTextRed.setFillColor(sf::Color::White);
	mScoreTextRed.setPosition(1130, 10);
	mScoreTextRed.setString("Score : 0");
}

GameManager::~GameManager()
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		delete mEntities[i];
	}
}

GameManager* GameManager::Instantiate()
{
	if (!mInstance)
    {
        mInstance = new GameManager();
        return mInstance;
    }
    return nullptr;
}

GameManager* GameManager::Get()
{
	return mInstance;
}

sf::Font* GameManager::getFont()
{
	return &mFont;
}

void GameManager::setWindow(sf::RenderWindow* window)
{
	mWindow = window;

	mGoalR = sf::RectangleShape(sf::Vector2f(100, mWindow->getSize().y));
	mGoalR.setFillColor(sf::Color::Transparent);
	mGoalR.setOutlineThickness(5);
	mGoalR.setOutlineColor(sf::Color::Red);
	mGoalR.setPosition(mWindow->getSize().x - 100, 0);

	mGoalG = sf::RectangleShape(sf::Vector2f(100, mWindow->getSize().y));
	mGoalG.setFillColor(sf::Color::Transparent);
	mGoalG.setOutlineThickness(5);
	mGoalG.setOutlineColor(sf::Color::Green);
	mGoalG.setPosition(0, 0);

	mBackgroundSprite.setPosition(0, 0);
	// fill the window with the background
	mBackgroundSprite.setScale(mWindow->getSize().x / mBackgroundSprite.getLocalBounds().width, mWindow->getSize().y / mBackgroundSprite.getLocalBounds().height);
}

void GameManager::Update()
{
	if (!mGameOver) {

		DebugMovePlayer();
		ForcePassBall();
		for (Entity* entity : mEntities)
		{
			entity->Update();
		}

		CheckWin();
	}
}

void GameManager::Draw()
{
	mWindow->draw(mBackgroundSprite);
	mWindow->draw(mGoalR);
	mWindow->draw(mGoalG);

	mWindow->draw(mScoreTextGreen);
	mWindow->draw(mScoreTextRed);


	for (Entity* entity : mEntities)
	{
		mWindow->draw(entity->getShape());
	}

	if (mGameOver)
	{
		sf::Text gameOverText; 
		gameOverText.setFont(mFont); 
		gameOverText.setCharacterSize(48); 
		gameOverText.setFillColor(sf::Color::Red); 

		if (mScoreGreen >= 8) { 
			gameOverText.setString("Green Team Wins!"); 
		}
		else if(mScoreRed >= 8){
			gameOverText.setString("Red Team Wins!"); 
		}

		gameOverText.setOrigin(gameOverText.getGlobalBounds().getSize()/2.f + gameOverText.getLocalBounds().getPosition());
		gameOverText.setPosition(mWindow->getSize().x / 2, mWindow->getSize().y / 2 ); 

		mWindow->draw(gameOverText); 
	}
}

std::vector<Entity*> GameManager::getEntities()
{
	return mEntities;
}

void GameManager::setDeltaTime(float deltaTime)
{
	mDeltaTime = deltaTime;
}

void GameManager::CheckWin()
{
	if (mScoreGreen >= 8 || mScoreRed >= 8)
	{
		mGameOver = true; 
		return;
	}

	Ball* ball = getBall();	
	if(ball->getOwner()!=nullptr)
	{
		if (ball->getOwner()->getTeam() == Context::Team::Green)
		{
			if (mGoalR.getGlobalBounds().contains(ball->getPosition()))  
			{
				std::cout << "Green Team Wins" << std::endl;
				mScoreGreen++;
				mScoreTextGreen.setString("Score : " + std::to_string(mScoreGreen));
				Reset(Context::Team::Red);
			}
		}
		else if (ball->getOwner()->getTeam() == Context::Team::Red)
		{
			if (mGoalG.getGlobalBounds().contains(ball->getPosition()))
			{
				std::cout << "Red Team Wins" << std::endl;
				mScoreRed++;
				mScoreTextRed.setString("Score : " + std::to_string(mScoreRed));
				Reset(Context::Team::Green);
			}
		}
	}
}

void GameManager::Reset(Context::Team team)
{
	Ball* ball = getBall();

	ball->setOwner(nullptr);

	for (auto p : getPlayers())
	{
		p->resetPosition();
		p->setState(Context::State::Idle);
	}

	ball->setPosition(sf::Vector2f(640, 360));

	std::vector<Player*> players = getPlayers(team);

	if (!players.empty())
	{
		int random = rand() % players.size();
		players[random]->setState(Context::State::HoldingBall);
		ball->setOwner(players[random]);
	}
}


float GameManager::getDeltaTime() const
{
	return mDeltaTime;
}

Ball* GameManager::getBall()
{
	for (auto ent : mEntities)
	{
		Ball* b = dynamic_cast<Ball*>(ent);
		if (b != NULL) {
			return b;
		}
	}
	return nullptr;
}

sf::RenderWindow* GameManager::getWindow()
{
	return mWindow;
}

std::vector<Player*> GameManager::getPlayers(Context::Team team)
{
	std::vector<Player*> players;
	for (auto ent : mEntities)
	{
		Player* p = dynamic_cast<Player*>(ent);
		if (p != NULL) {
			if (team == Context::Team::None)
			{
				players.push_back(p);
			}
			else if (p->getTeam() == team) {
				players.push_back(p);
			}
		}
	}
	return players;
}



void GameManager::addEntity(Entity* entity)
{
	mEntities.push_back(entity);
}

void GameManager::DebugMovePlayer()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));

		for (auto p : getPlayers())
		{
			if (p->getShape().getGlobalBounds().contains(mousePos))
			{
				p->setPosition(mousePos);
			}
		}
	}
}


void GameManager::ForcePassBall()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		sf::Vector2f mousePos = mWindow->mapPixelToCoords(sf::Mouse::getPosition(*mWindow));

		Player* ballOwner = getBall()->getOwner();
		if (ballOwner != nullptr)
		{
			Player* targetPlayer = nullptr;

			for (auto p : getPlayers(ballOwner->getTeam())) 
			{
				if (p != ballOwner && p->getShape().getGlobalBounds().contains(mousePos))
				{

					targetPlayer = p;
					break;
				}
			}
			if (targetPlayer != nullptr)
			{
				Ball* ball = getBall();
				ball->throwAt(targetPlayer, ballOwner->getThrowSpeed());

			}
		}
	}
}



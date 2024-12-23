#include "pch.h"

namespace 
{
static GameManager* mInstance = nullptr;
}

GameManager::GameManager()
{
	mBlackTeamPoints = 0;
	mWhiteTeamPoints = 0;
}

void GameManager::init(sf::Font font)
{
	Animator* animatorWhite1 = new Animator();
	Animator* animatorWhite2 = new Animator();
	Animator* animatorWhite3 = new Animator();
	Animator* animatorWhite4 = new Animator();
	Animator* animatorWhite5 = new Animator();
	Animator* animatorBlack1 = new Animator();
	Animator* animatorBlack2 = new Animator();
	Animator* animatorBlack3 = new Animator();
	Animator* animatorBlack4 = new Animator();
	Animator* animatorBlack5 = new Animator();

	for (int i = 0; i < 8; i++) {
		std::string path = "..\\..\\..\\src\\Rugby_24_Deluxe_Edition_Collector\\Assets\\Wtile00" + std::to_string(i) + ".png";
		animatorWhite1->AddSprite(path);
		animatorWhite2->AddSprite(path);
		animatorWhite3->AddSprite(path);
		animatorWhite4->AddSprite(path);
		animatorWhite5->AddSprite(path);
	}

	for (int i = 0; i < 8; i++) {
		std::string path = "..\\..\\..\\src\\Rugby_24_Deluxe_Edition_Collector\\Assets\\Btile00" + std::to_string(i) + ".png";
		animatorBlack1->AddSprite(path);
		animatorBlack2->AddSprite(path);
		animatorBlack3->AddSprite(path);
		animatorBlack4->AddSprite(path);
		animatorBlack5->AddSprite(path);
	}

	Transition* transitionToAttack = new Transition();
	transitionToAttack->setTargetState(Context::State::PlayerAttack);
	transitionToAttack->addCondition(new ConditionPlayerAttack());

	Transition* transitionToDefend = new Transition();
	transitionToDefend->setTargetState(Context::State::PlayerDefend);
	transitionToDefend->addCondition(new ConditionPlayerDefend());

	Transition* transitionToHaveBall = new Transition();
	transitionToHaveBall->setTargetState(Context::State::PlayerHaveBalls);
	transitionToHaveBall->addCondition(new ConditionPlayerHaveBall());

	Transition* transitionToSeekBall = new Transition();
	transitionToSeekBall->setTargetState(Context::State::PlayerSeekBall);
	transitionToSeekBall->addCondition(new ConditionPlayerSeekBall());

	Transition* transitionToDefender = new Transition();
	transitionToDefender->setTargetState(Context::State::PlayerDefender);
	transitionToDefender->addCondition(new ConditionPlayerDefender());

	Transition* transitionToRunner = new Transition();
	transitionToRunner->setTargetState(Context::State::PlayerRunner);
	transitionToRunner->addCondition(new ConditionPlayerRunner());

	Behaviour* behaviour = new Behaviour();


	behaviour->AddAction(Context::State::PlayerAttack, new ActionPlayerAttack());
	behaviour->AddAction(Context::State::PlayerDefend, new ActionPlayerDefend());
	behaviour->AddAction(Context::State::PlayerHaveBalls, new ActionPlayerHaveBall());
	behaviour->AddAction(Context::State::PlayerSeekBall, new ActionPlayerSeekBall());
	behaviour->AddAction(Context::State::PlayerDefender, new ActionPlayerDefender());
	behaviour->AddAction(Context::State::PlayerRunner, new ActionPlayerRunner());

	behaviour->AddTransition(Context::State::PlayerAttack, transitionToSeekBall);
	behaviour->AddTransition(Context::State::PlayerAttack, transitionToDefend);
	behaviour->AddTransition(Context::State::PlayerAttack, transitionToHaveBall);
	behaviour->AddTransition(Context::State::PlayerAttack, transitionToDefender);
	behaviour->AddTransition(Context::State::PlayerAttack, transitionToRunner);

	behaviour->AddTransition(Context::State::PlayerDefend, transitionToAttack);
	behaviour->AddTransition(Context::State::PlayerDefend, transitionToSeekBall);
	behaviour->AddTransition(Context::State::PlayerDefend, transitionToHaveBall);
	behaviour->AddTransition(Context::State::PlayerDefend, transitionToDefender);

	behaviour->AddTransition(Context::State::PlayerHaveBalls, transitionToAttack);
	behaviour->AddTransition(Context::State::PlayerHaveBalls, transitionToDefend);
	behaviour->AddTransition(Context::State::PlayerHaveBalls, transitionToSeekBall);
	behaviour->AddTransition(Context::State::PlayerHaveBalls, transitionToDefender);

	behaviour->AddTransition(Context::State::PlayerSeekBall, transitionToAttack);
	behaviour->AddTransition(Context::State::PlayerSeekBall, transitionToDefend);
	behaviour->AddTransition(Context::State::PlayerSeekBall, transitionToHaveBall);
	behaviour->AddTransition(Context::State::PlayerSeekBall, transitionToDefender);

	behaviour->AddTransition(Context::State::PlayerDefender, transitionToAttack);
	behaviour->AddTransition(Context::State::PlayerDefender, transitionToDefend);
	behaviour->AddTransition(Context::State::PlayerDefender, transitionToHaveBall);
	behaviour->AddTransition(Context::State::PlayerDefender, transitionToSeekBall);

	behaviour->AddTransition(Context::State::PlayerRunner, transitionToHaveBall);
	behaviour->AddTransition(Context::State::PlayerRunner, transitionToSeekBall);
	behaviour->AddTransition(Context::State::PlayerRunner, transitionToDefend);



	Lane* topLane = new Lane(0, mWindow->getSize().y / 2);
	Lane* middleLane = new Lane(mWindow->getSize().y / 4, mWindow->getSize().y / 4 * 3);
	Lane* bottomLane = new Lane(mWindow->getSize().y / 2, mWindow->getSize().y);


	long long t = Time::GetInstance()->GetActualTime();
	srand(t);

	// Team Uno
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 20, mWindow->getSize().y / 8), 1, behaviour, animatorWhite1, topLane, font, false, true);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 7, mWindow->getSize().y / 6), 2, behaviour, animatorWhite2, topLane, font, false, false);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 5, mWindow->getSize().y / 2), 3, behaviour, animatorWhite3, middleLane, font, false, false);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 7, mWindow->getSize().y / 6 * 5), 4, behaviour, animatorWhite4, bottomLane, font, false, false);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 20, mWindow->getSize().y / 8 * 7), 5, behaviour, animatorWhite5, bottomLane, font, false, true);

	// Team Dos
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 20 * 19, mWindow->getSize().y / 8), 6, behaviour, animatorBlack1, topLane, font, true, true);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 7 * 6, mWindow->getSize().y / 6), 7, behaviour, animatorBlack2, topLane, font, true, false);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 5 * 4, mWindow->getSize().y / 2), 8, behaviour, animatorBlack3, middleLane, font, true, false);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 7 * 6, mWindow->getSize().y / 6 * 5), 9, behaviour, animatorBlack4, bottomLane, font, true, false);
	RandomGenerationPlayer(sf::Vector2f(mWindow->getSize().x / 20 * 19, mWindow->getSize().y / 8 * 7), 10, behaviour, animatorBlack5, bottomLane, font, true, true);

	//Player* p1 = new Player(sf::Vector2f(mWindow->getSize().x / 20, mWindow->getSize().y / 8), behaviour, animatorWhite1, false,1,font, topLane, 60, 120, 50, 100, true);
	//Player* p2 = new Player(sf::Vector2f(mWindow->getSize().x / 7, mWindow->getSize().y / 6), behaviour, animatorWhite2, false, 2, font, topLane, 60, 120, 50, 100, false);
	//Player* p3 = new Player(sf::Vector2f(mWindow->getSize().x / 5, mWindow->getSize().y / 2), behaviour, animatorWhite3, false, 3, font, middleLane, 60, 120, 50, 100, false);
	//Player* p4 = new Player(sf::Vector2f(mWindow->getSize().x / 7, mWindow->getSize().y / 6 * 5), behaviour, animatorWhite4, false, 4, font, bottomLane, 60, 120, 50, 100, false);
	//Player* p5 = new Player(sf::Vector2f(mWindow->getSize().x / 20, mWindow->getSize().y / 8 * 7), behaviour, animatorWhite5, false, 5, font, bottomLane, 60, 120, 50, 100, true);

	//// Team Dos
	//Player* p6 = new Player(sf::Vector2f(mWindow->getSize().x / 20 * 19, mWindow->getSize().y / 8), behaviour, animatorBlack1, true, 6, font, topLane, 60, 120, 50, 100, true);
	//Player* p7 = new Player(sf::Vector2f(mWindow->getSize().x / 7 * 6, mWindow->getSize().y / 6), behaviour, animatorBlack2, true, 7, font, topLane, 60, 120, 50, 100, false);
	//Player* p8 = new Player(sf::Vector2f(mWindow->getSize().x / 5 * 4, mWindow->getSize().y / 2), behaviour, animatorBlack3, true, 8, font, middleLane, 60, 120, 50, 100, false);
	//Player* p9 = new Player(sf::Vector2f(mWindow->getSize().x / 7 * 6, mWindow->getSize().y / 6 * 5), behaviour, animatorBlack4, true, 9, font, bottomLane, 60, 120, 50, 100, false);
	//Player* p10 = new Player(sf::Vector2f(mWindow->getSize().x / 20 * 19, mWindow->getSize().y / 8 * 7), behaviour, animatorBlack5, true, 10, font, bottomLane, 60, 120, 50, 100, true);


	//mPlayers.push_back(p1);
	//mPlayers.push_back(p2);
	//mPlayers.push_back(p3);
	//mPlayers.push_back(p4);
	//mPlayers.push_back(p5);

	//mPlayers.push_back(p6);
	//mPlayers.push_back(p7);
	//mPlayers.push_back(p8);
	//mPlayers.push_back(p9);
	//mPlayers.push_back(p10);

	Ball* ball = new Ball(sf::Vector2f(940, 360));
	mBall = ball;

	// Text
	mFont = font;

	mWhiteScoreText.setFont(mFont);
	mWhiteScoreText.setCharacterSize(20);
	mWhiteScoreText.setFillColor(sf::Color::White);
	mWhiteScoreText.setStyle(mWhiteScoreText.Bold);
	mWhiteScoreText.setPosition(mWindow->getSize().x / 20 * 1.5, 10);
	mWhiteScoreText.setString("score : \n" + std::to_string(mWhiteTeamPoints));

	mBlackScoreText.setFont(mFont);
	mBlackScoreText.setCharacterSize(20);
	mBlackScoreText.setFillColor(sf::Color::Black);
	mBlackScoreText.setStyle(mBlackScoreText.Bold);
	mBlackScoreText.setPosition(mWindow->getSize().x / 20 * 17, 10);
	mBlackScoreText.setString("score : \n" + std::to_string(mBlackTeamPoints));

	mWinText.setFont(mFont);
	mWinText.setCharacterSize(100);
	mWinText.setFillColor(sf::Color::Transparent);
	mWinText.setStyle(mWinText.Bold);
	mWinText.setPosition(mWindow->getSize().x / 4 + 15 , mWindow->getSize().y / 3);
	
	mDebug = new DebugClass();

	mAnimator = new Animator();

}

void GameManager::RandomGenerationPlayer(sf::Vector2f pos, int number, Behaviour* behaviour, Animator* animator, Lane* lane, sf::Font font, bool team, bool defender) {

	int speed = 45 + rand() % 26;
	int maxSpeed = speed * 2;
	int size = 30 + rand() % 41;
	int temerity = 25 + rand() % 51;

	Player* p = new Player(pos, behaviour, animator, team, number, font, lane, speed, maxSpeed, size, temerity, defender);

	mPlayers.push_back(p);
}

GameManager::~GameManager()
{
	for (int i = 0; i < mPlayers.size(); i++)
	{
		delete mPlayers[i];
	}
	delete mBall;
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

void GameManager::setWindow(sf::RenderWindow* window)
{
	mWindow = window;
}

sf::RenderWindow* GameManager::getWindow()
{
	return mWindow;
}

void GameManager::resetPlaces() 
{

	// Team white
	mPlayers[0]->setPosition(sf::Vector2f(mWindow->getSize().x / 20, mWindow->getSize().y / 8));
	mPlayers[1]->setPosition(sf::Vector2f(mWindow->getSize().x / 7, mWindow->getSize().y / 6));
	mPlayers[2]->setPosition(sf::Vector2f(mWindow->getSize().x / 5, mWindow->getSize().y / 2));
	mPlayers[3]->setPosition(sf::Vector2f(mWindow->getSize().x / 7, mWindow->getSize().y / 6 * 5));
	mPlayers[4]->setPosition(sf::Vector2f(mWindow->getSize().x / 20, mWindow->getSize().y / 8 * 7));

	// Team black
	mPlayers[5]->setPosition(sf::Vector2f(mWindow->getSize().x / 20 * 19, mWindow->getSize().y / 8));
	mPlayers[6]->setPosition(sf::Vector2f(mWindow->getSize().x / 7 * 6, mWindow->getSize().y / 6));
	mPlayers[7]->setPosition(sf::Vector2f(mWindow->getSize().x / 5 * 4, mWindow->getSize().y / 2));
	mPlayers[8]->setPosition(sf::Vector2f(mWindow->getSize().x / 7 * 6, mWindow->getSize().y / 6 * 5));
	mPlayers[9]->setPosition(sf::Vector2f(mWindow->getSize().x / 20 * 19,mWindow->getSize().y / 8 * 7));

}

void GameManager::CheckGoal()
{
	long long t = Time::GetInstance()->GetActualTime();

	srand(t);

	if (mBall->getOwner() != nullptr) {
		if (mBall->getPosition().x > mWindow->getSize().x / 10 * 9 + 20 && !mBall->getOwner()->isBlack()) {
			mWhiteTeamPoints += 1;
			mBall->setOwner(mPlayers[rand() % 5 + 5]);
			resetPlaces();
		}
		if (mBall->getPosition().x < mWindow->getSize().x / 10 - 20 && mBall->getOwner()->isBlack()) {
			mBlackTeamPoints += 1;
			mBall->setOwner(mPlayers[rand() % 5]);
			resetPlaces();
		}
	}
}

void GameManager::CheckWin()
{
	if (mWhiteTeamPoints >= 5) {
		mWinText.setString("White WIN");
		mWinText.setFillColor(sf::Color::White);
	}
	if (mBlackTeamPoints >= 5) {
		mWinText.setString("Black WIN");
		mWinText.setFillColor(sf::Color::Black);
	}

}

void GameManager::Update()
{
	Time* timer = Time::GetInstance();

	mDeltaTime = timer->GetElapsedTime();

	CheckGoal();
	mBlackScoreText.setString("score : \n" + std::to_string(mBlackTeamPoints));
	mWhiteScoreText.setString("score : \n" + std::to_string(mWhiteTeamPoints));
	CheckWin();

	mDebug->Update();

	for(Player* player : mPlayers){
		player->Update();
	}

	mBall->Update();
}

void GameManager::Draw()
{

	for (Player* player : mPlayers) {
		player->Draw(mWindow);
	}
	mBall->Draw(mWindow);

	mWindow->draw(mWhiteScoreText);
	mWindow->draw(mBlackScoreText);
	mWindow->draw(mWinText);
}

void GameManager::setDeltaTime(float deltaTime)
{
	mDeltaTime = deltaTime;
}

float GameManager::getDeltaTime() const
{
	return mDeltaTime;
}

std::vector<Player*> GameManager::getPlayers() const
{
	return mPlayers;
}

Ball* GameManager::getBall() const
{
	return mBall;
}

Animator* GameManager::getAnimator() const 
{
	return mAnimator;
}

void GameManager::handleUserInput(sf::Event event)
{
	mDebug->handleUserInput(event);
}

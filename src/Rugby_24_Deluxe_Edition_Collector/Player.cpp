#include "pch.h"

Player::Player(const sf::Vector2f& position, Behaviour* behaviour, Animator* animator,bool team,int num, sf::Font font, Lane* lane, float speed, float maxSpeed, float size, int temerity, bool isDefender)
{
    mBehaviour = behaviour;
	mSize = size;
	mSpeed = speed;
	baseSpeed = mSpeed;
	sprintSpeed = maxSpeed;
	invincible = false;
	invincibleStartTime = 0;
	invincibleDuration = INVINCIBLE_TIME;
	speedBoost = false;
	speedBoostStartTime = 0;
	speedBoostDuration = SPEED_TIME;
	canThrow = true;
	canThrowStartTime = 0;
	canThrowDuration = 2.5f;
	mLane = lane;
	mTemerity = temerity;
	mAnimator = animator;
	mIsDefender = isDefender;

	mNum = num;

	mFont = font;

	mIsBlack = team;

	mNumText.setFont(mFont);
	mNumText.setCharacterSize(20);
	if (mIsBlack)
		mNumText.setFillColor(sf::Color::Black);
	else
		mNumText.setFillColor(sf::Color::White);
	mNumText.setStyle(mNumText.Bold);
	mNumText.setString(std::to_string(mNum));

	mPosition = position;

    sf::CircleShape* shape = new sf::CircleShape(10);
	shape->setRadius(mSize / 2.f);
	shape->setFillColor(sf::Color::Transparent);
	shape->setOrigin(mSize / 2.f, mSize / 2.f);
	shape->setPosition(mPosition);
	shape->setOutlineColor(sf::Color::Yellow);

	TextureManager* manager = TextureManager::GetInstance();
	sf::Texture texture;

	if (mIsBlack) 
		texture = manager->GetTexture("..\\..\\..\\src\\Rugby_24_Deluxe_Edition_Collector\\Assets\\BlackTeam.png");
	
	else 
		texture = manager->GetTexture("..\\..\\..\\src\\Rugby_24_Deluxe_Edition_Collector\\Assets\\WhiteTeam.png");

	mSprite.setTexture(texture);
	mSprite.setScale(mSize / mSprite.getLocalBounds().width, mSize / mSprite.getLocalBounds().height);
	mSprite.setPosition(mPosition);
	mSprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	mOutlineThickness = false;

    mShape = shape;

	setState(Context::State::PlayerSeekBall);
}

Player::~Player()
{

}

void Player::Update()
{
	VerifyTimer();

	mBehaviour->Update(this);

	mAnimator->Anime(&mSprite);
}

void Player::Draw(sf::RenderWindow* window)
{
	mShape->setPosition(mPosition);
	if (mOutlineThickness) {
		mShape->setOutlineThickness(2);
	}
	else {
		mShape->setOutlineThickness(0);
	}
	
	mNumText.setPosition(sf::Vector2f(mPosition.x - mSize, mPosition.y - mSize));
	window->draw(*mShape);
	window->draw(mSprite);
	window->draw(mNumText);
}

Context::State Player::getState() const
{
    return mState;
}

void Player::setState(Context::State new_state) 
{
    mState = new_state;
	mBehaviour->Start(this);
}

void Player::Defender()
{
	int bottom = mLane->getBottomLane();
	int top = mLane->getTopLane();
	int middle = (bottom - top) + top - ((bottom - top) / 2);

	sf::Vector2f target;

	if (mIsBlack)
	{
		target = sf::Vector2f(1080, middle);
	}
	else {
		target = sf::Vector2f(200, middle);
	}

	float distance = Utils::GetDistance(mPosition, target);

	if (distance <= 10)
	{
		mDirection = sf::Vector2f(0, 0);
	}
	else {
		setDirectionByPosition(target);
	}

	move();
}

void Player::Runner() {

	Player* owner = GameManager::Get()->getBall()->getOwner();

	int bottom = mLane->getBottomLane();
	int top = mLane->getTopLane();
	int middle = (bottom - top) + top - ((bottom - top) / 2);

	sf::Vector2f target;

	int dir = 1;

	if (mIsBlack)
	{
		if (owner != nullptr && mPosition.x < owner->getPosition().x)
		{
			dir = -1;
		}
		target = sf::Vector2f(mPosition.x - 50 * dir, middle);
	}
	else {
		if (owner != nullptr && mPosition.x > owner->getPosition().x)
		{
			dir = -1;
		}
		target = sf::Vector2f(mPosition.x + 50 * dir, middle);
	}

	setDirectionByPosition(target);

	move();
}

void Player::MoveToBall()
{
	Ball* ball = GameManager::Get()->getBall();
	sf::Vector2f target;

	if (ball->mIsLobe)
	{
		target = ball->mLobeTarget;
	}
	else {
		target = ball->getPosition();
	}

	mOutlineThickness = false;

	float distance = Utils::GetDistance(mPosition, target);

	if (distance >= 2.f)
	{
		setDirectionByPosition(target);
	}
	else {
		mDirection = sf::Vector2f(0, 0);
	}

	move();
}

void Player::move()
{
	float dt = GameManager::Get()->getDeltaTime();

	sf::Vector2f initialPos = mPosition;
	sf::Vector2f initialDir = mDirection;

	HandleCollisions(initialPos);
	MovePlayer(dt);
	CheckLaneBounds(initialPos);

	//calcule the angle with the initial direction to avoid glitching rotation with collision

	float angle = atan2(initialDir.y , initialDir.x ) * 180 / M_PI;
	mSprite.setRotation(angle);

	mSprite.setPosition(mPosition);
	mShape->setPosition(mPosition);
}

void Player::MovePlayer(float dt)
{
	if (mState == Context::State::PlayerHaveBalls)
	{
		mPosition.x += dt * (mSpeed * 0.9f) * mDirection.x;
		mPosition.y += dt * (mSpeed * 0.9f) * mDirection.y;
	}
	else {
		mPosition.x += dt * mSpeed * mDirection.x;
		mPosition.y += dt * mSpeed * mDirection.y;
	}
}

void Player::HandleCollisions(const sf::Vector2f tempPos)
{
	std::vector<Player*> players = GameManager::Get()->getPlayers();
	float dt = GameManager::Get()->getDeltaTime();

	for (Player* player : players)
	{
		if (player != this)
		{
			if (player->isBlack() == mIsBlack && mState == Context::State::PlayerAttack)
			{
				if (DetectCollision(player, 50))
				{
					float distance = Utils::GetDistance(mPosition, player->getPosition());
					AdjustDirection(player);
				}
			}
			else if (!speedBoost)
			{
				if (DetectCollision(player, 0))
				{

					AdjustDirection(player);
				}
			}
			 //Check if the new position is still colliding with other players
			bool isColliding = false;
			for (Player* otherPlayer : players)
			{
				if (otherPlayer != this && DetectCollision(otherPlayer, 0))
				{
					isColliding = true;
				}
			}

			// If the new position is still colliding, revert back to the previous position
			if (isColliding)
			{
				mPosition = tempPos;
			}
		}
	}
}

void Player::AdjustDirection(Player* player)
{
	sf::Vector2f director = Utils::GetVector(mPosition, player->getPosition());
	director = Utils::Vector2Normalize(director);
	
	sf::Vector2f newDirection = mDirection - director;
	newDirection = Utils::Vector2Normalize(newDirection);



	setDirection(newDirection);
}

void Player::CheckLaneBounds(const sf::Vector2f tempPos)
{
	if (!mLane->isInLane(mPosition))
	{
		mPosition.y = mLane->GetCorrectPosition(mPosition);
	}
}

bool Player::IsTouchingEnemyOwner() const {
	Player* owner = GameManager::Get()->getBall()->getOwner();
	std::vector<Player*> players = GameManager::Get()->getPlayers();

	for (Player* player : players)
	{
		if (player->isBlack() != mIsBlack && CanSteal(player) && !player->invincible)
		{
			if (player == owner)
			{
				return true;
			}
		}
	}

	return false;
}

bool Player::CanSteal(Player* player) const
{
	float distance = Utils::GetDistance(getPosition(), player->getPosition());
	float distanceMin = (player->mSize / 2) + (mSize / 2) + 5;

	if (distance < distanceMin)
	{
		return true;
	}
	return false;
}

void Player::MoveToGoal() 
{
	sf::Vector2f direction;
	
	if (GameManager::Get()->getBall()->getOwner() != nullptr && GameManager::Get()->getBall()->getOwner()->getPosition() != mPosition) {
		if (mIsBlack)
		{
			if (GameManager::Get()->getBall()->getOwner()->getPosition().x > mPosition.x - 20 )
			{
				direction = sf::Vector2f(1, 0);
			}
			else {
				direction = sf::Vector2f(-1, 0);
			}
		}
		else
		{
			if (GameManager::Get()->getBall()->getOwner()->getPosition().x < mPosition.x + 20 )
			{
				direction = sf::Vector2f(-1, 0);
			}
			else {
				direction = sf::Vector2f(1, 0);
			}
		}
	}
	else {
		if (mIsBlack)
		{
			direction = sf::Vector2f(-1, 0);
		}
		else
		{
			direction = sf::Vector2f(1, 0);
		}
	}

	setDirection(direction);

	if (mState == Context::State::PlayerHaveBalls)
	{
		CheckEnnemyDistance();
	}

	move();
}

void Player::ThrowBall(Player* target)
{

	if (target != nullptr)
	{
		std::cout << "Throwing to player " << target->GetNumber() << "\n";
		GameManager::Get()->getBall()->setDirectionByPosition(target->getPosition());
		GameManager::Get()->getBall()->resetOwner(); 
		return;
	}

	sf::Vector2f tempPos = CheckTeamDistance();

	if (tempPos != sf::Vector2f(0.f, 0.f))
	{
		GameManager::Get()->getBall()->setDirectionByPosition(tempPos);
		GameManager::Get()->getBall()->resetOwner();
	}
	else {
		LobeBall();
	}
}

void Player::LobeBall() {
	//find the player wih the state PlayerRunner
	Player* runner = nullptr;
	for (Player* player : GameManager::Get()->getPlayers())
	{
		if (player->getState() == Context::State::PlayerRunner)
		{
			runner = player;
			break;
		}
	}

	if (runner == nullptr)
	{
		return;
	}

	if (mIsBlack)
	{
		if (runner->getPosition().x < mPosition.x)
		{
			return;
		}
	}
	else {
		if (runner->getPosition().x > mPosition.x)
		{
			return;
		}
	}

	sf::Vector2f receiver = runner->getPosition();

	long long t = Time::GetInstance()->GetActualTime();
	srand(t);

	receiver.x += (rand() % 201 - 100);
	receiver.y += (rand() % 201 - 100);

	float distance = Utils::GetDistance(mPosition, receiver);

	GameManager::Get()->getBall()->resetOwner();
	GameManager::Get()->getBall()->mIsLobe = true;
	GameManager::Get()->getBall()->mLobeTarget = receiver;
	GameManager::Get()->getBall()->mLobeDistance = distance;
}

sf::Vector2f Player::GetFurthestTeammate()
{
	std::vector<Player*> tempTeam;

	for (Player* player : GameManager::Get()->getPlayers())
	{
		if (GameManager::Get()->getBall()->getOwner() != player) {
			if (player->isBlack() == isBlack())
			{
				tempTeam.push_back(player);
			}
		}
	}

	Player* furthest = tempTeam[0];
	float maxDistance = 0;

	for (Player* player : tempTeam)
	{
		float distance = Utils::GetDistance(mPosition, player->getPosition());

		if (distance > maxDistance)
		{
			maxDistance = distance;
			furthest = player;
		}
	}

	return furthest->mPosition;
}

sf::Vector2f Player::CheckTeamDistance()
{
	long long t = Time::GetInstance()->GetActualTime();

	srand(t);

	std::vector<Player*> tempTeam;
	std::vector<Player*> tempEnnemies;

	std::vector<Player*> tempPossible;

	for (Player* player : GameManager::Get()->getPlayers())
	{
		if (GameManager::Get()->getBall()->getOwner() != player) {
			if (player->isBlack() == isBlack())
			{
				tempTeam.push_back(player);
			}
			else {
				tempEnnemies.push_back(player);
			}
		}
	}

	for (Player* teammate : tempTeam)
	{
		float dst = Utils::GetDistance(mPosition, teammate->getPosition());

		float angle = atan2(teammate->getPosition().y - mPosition.y, teammate->getPosition().x - mPosition.x) * 180 / M_PI;

		bool IsOkay = false;

		sf::RectangleShape line(sf::Vector2f(dst, 2));
		line.setPosition(mPosition);
		line.rotate(angle);

		for (Player* ennemy : tempEnnemies) {

			if (ennemy->getShape().getGlobalBounds().intersects(line.getGlobalBounds()))
			{
				IsOkay = false;
				break;
			}
			else
			{
				float ennemydst = Utils::GetDistance(teammate->getPosition(), ennemy->getPosition());

				if (ennemydst > 100) {
					IsOkay = true;
				}
				else {
					IsOkay = false;
					break;
				}
			}
		}

		if (IsOkay)
			tempPossible.push_back(teammate);

	}
	if (tempPossible.size() != 0) {
		return tempPossible[rand() % tempPossible.size()]->mPosition;
	}
	return sf::Vector2f(0, 0);
}

void Player::CheckEnnemyDistance()
{
	std::vector<Player*> tempEnnemies;

	for (Player* player : GameManager::Get()->getPlayers())
	{
		if (GameManager::Get()->getBall()->getOwner() != player) {
			if (player->isBlack() != isBlack())
			{
				tempEnnemies.push_back(player);
			}
		}
	}

	for (Player* ennemy : tempEnnemies)
	{
		float dst = Utils::GetDistance(mPosition, ennemy->getPosition());

		if (isBlack())
		{
			if (ennemy->getPosition().x < mPosition.x && dst <= mSize + mTemerity || dst <= mSize + 10) {
				if (canThrow) {
					ThrowBall();
					return;
				}
			}
		}
		if (!isBlack())
		{
			if (ennemy->getPosition().x > mPosition.x && dst <= mSize + mTemerity || dst <= mSize + 10) {
				if (canThrow) {
					ThrowBall();
					return;
				}

			}
		}
	}
}

bool Player::isBlack() const
{
	return mIsBlack;
}

float Player::GetInvincibleDuration() const
{
	return invincibleDuration;
}

void Player::VerifyTimer()
{
	
	auto now = std::chrono::high_resolution_clock::now();
	float currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

	if (currentTime - invincibleStartTime > invincibleDuration * 1000 && invincible)
	{
		invincible = false;
	}

	if (currentTime - speedBoostStartTime > speedBoostDuration * 1000 && speedBoost)
	{
		mAnimator->SetSpeed(0.05f);
		mSpeed = baseSpeed;
		speedBoost = false;
	}

	if (currentTime - canThrowStartTime > canThrowDuration * 1000 && !canThrow)
	{
		canThrow = true;
	}
	
}

void Player::Sprint() {
	mAnimator->SetSpeed(0.02f);
	//Get the actual time with chrono
	auto start = std::chrono::high_resolution_clock::now();
	//convert start in float
	invincibleStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
	speedBoostStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();
	canThrowStartTime = std::chrono::duration_cast<std::chrono::milliseconds>(start.time_since_epoch()).count();

	invincible = true;
	speedBoost = true;
	canThrow = false;
	mSpeed = sprintSpeed;
}

void Player::SetMaxSpeed() {
	mSpeed = sprintSpeed;
}

int Player::GetNumber() {
	return mNum;
}

bool Player::GetIsDefender()
{
	return mIsDefender;
}


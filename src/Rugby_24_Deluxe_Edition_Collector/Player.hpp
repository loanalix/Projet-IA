#pragma once

class Player : public Entity
{
    Context::State mState;
    Behaviour * mBehaviour;
    float invincibleDuration, speedBoostDuration, canThrowDuration, baseSpeed, sprintSpeed;

    int mNum, mTemerity;
    bool mIsBlack, mIsDefender;

    sf::Font mFont;
    sf::Text mNumText;

	Lane* mLane;

    Animator* mAnimator;

public:
    bool speedBoost;
    float speedBoostStartTime;
    bool invincible;
    float invincibleStartTime;
    bool canThrow;
    float canThrowStartTime;

    bool mOutlineThickness;

    sf::Sprite mSprite;

    Player(const sf::Vector2f& position, Behaviour* behaviour, Animator* animator, bool team, int num, sf::Font font, Lane* lane, float speed, float maxSpeed, float size, int temerity, bool isDefender);
    ~Player();

    void Update() override;
	void Draw(sf::RenderWindow* window) override;

    Context::State getState() const;
    void setState(Context::State);
    void Defender();
    void Runner();
    void MoveToBall();
    void move() override;
    void MovePlayer(float dt);
    void HandleCollisions(sf::Vector2f tempPos);
    void AdjustDirection(Player* player);
    void CheckLaneBounds(sf::Vector2f tempPos);
    bool IsTouchingEnemyOwner() const;
    bool CanSteal(Player* player) const;
    void MoveToGoal();
    void ThrowBall(Player* target = nullptr);

    void LobeBall();

    sf::Vector2f GetFurthestTeammate();

    sf::Vector2f CheckTeamDistance();
    void CheckEnnemyDistance();

	bool isBlack() const;

	float GetInvincibleDuration() const;
    void VerifyTimer();
    void Sprint();
    void SetMaxSpeed();

    int GetNumber();
	bool GetIsDefender();
};

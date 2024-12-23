#pragma once

class ActionPlayerSeekBall :
    public Action
{
public:
	ActionPlayerSeekBall();
	virtual ~ActionPlayerSeekBall();

	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};


#pragma once
class ConditionPlayerSeekBall :
	public Condition
{
public:
	ConditionPlayerSeekBall();
	virtual ~ConditionPlayerSeekBall();

	bool Test(Player* player) override;
};


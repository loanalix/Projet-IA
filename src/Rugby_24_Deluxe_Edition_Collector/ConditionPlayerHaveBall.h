#pragma once
class ConditionPlayerHaveBall :
	public Condition
{
public:
	ConditionPlayerHaveBall();
	virtual ~ConditionPlayerHaveBall();

	bool Test(Player* player) override;
};


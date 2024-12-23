#pragma once
class ConditionPlayerDefend :
	public Condition
{
public:
	ConditionPlayerDefend();
	virtual ~ConditionPlayerDefend();

	bool Test(Player* player) override;
};


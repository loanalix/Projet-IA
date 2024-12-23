#pragma once
class ConditionPlayerDefender :
    public Condition
{
public:
	ConditionPlayerDefender();
	virtual ~ConditionPlayerDefender();

	bool Test(Player* player) override;
};


#pragma once
class ConditionPlayerRunner :
    public Condition
{
public:
	ConditionPlayerRunner();
	virtual ~ConditionPlayerRunner();

	bool Test(Player* player) override;
};


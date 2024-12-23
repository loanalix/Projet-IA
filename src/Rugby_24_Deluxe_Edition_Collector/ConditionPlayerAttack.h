#pragma once
class ConditionPlayerAttack :
    public Condition
{
public:
	ConditionPlayerAttack();
	virtual ~ConditionPlayerAttack();

	bool Test(Player* player) override;
};


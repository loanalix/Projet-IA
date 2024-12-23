#pragma once

class ActionPlayerAttack :
    public Action
{
public:
	ActionPlayerAttack();
	virtual ~ActionPlayerAttack();

	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};


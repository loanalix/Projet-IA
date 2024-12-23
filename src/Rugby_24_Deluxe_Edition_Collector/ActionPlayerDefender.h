#pragma once

class ActionPlayerDefender :
    public Action
{
public:
	ActionPlayerDefender();
	virtual ~ActionPlayerDefender();

	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};


#pragma once

class ActionPlayerRunner :
    public Action
{
public:
	ActionPlayerRunner();
	virtual ~ActionPlayerRunner();

	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};


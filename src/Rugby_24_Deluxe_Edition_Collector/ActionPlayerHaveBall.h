#pragma once

class ActionPlayerHaveBall :
    public Action
{
public:
	ActionPlayerHaveBall();
	virtual ~ActionPlayerHaveBall();

	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};


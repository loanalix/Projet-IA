#pragma once

class ActionPlayerDefend : 
	public Action
{
public:
	ActionPlayerDefend();
	virtual ~ActionPlayerDefend();

	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};


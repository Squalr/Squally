#pragma once

#include "Engine/Maps/GameObject.h"

class Quest : public GameObject
{
public:
	virtual void activate();
	virtual void deactivate();
	std::string getQuestName();
	bool isQuestActive();

protected:
	Quest(std::string quest);
	~Quest();

	void initializeListeners() override;

private:
	typedef GameObject super;

	bool isActive;
	std::string quest;
};


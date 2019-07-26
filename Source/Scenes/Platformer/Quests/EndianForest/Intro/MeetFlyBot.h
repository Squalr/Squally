#pragma once

#include "Engine/Quests/Quest.h"

class MeetFlyBot : public Quest
{
public:
	static MeetFlyBot* create();

	static const std::string MapKeyQuest;

protected:
	MeetFlyBot();
	~MeetFlyBot();

private:
	typedef Quest super;
	void initializeListeners() override;
};


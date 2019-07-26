#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class TeachHackerMode : public QuestTask
{
public:
	static TeachHackerMode* create(GameObject* owner);

	static const std::string MapKeyQuest;

protected:
	TeachHackerMode(GameObject* owner);
	~TeachHackerMode();
	
	void onLoad(bool isQuestActive, bool isQuestActiveAsSkippable, bool isQuestComplete) override;
	void onActivate() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

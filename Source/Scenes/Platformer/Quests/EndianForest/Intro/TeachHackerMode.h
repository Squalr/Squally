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
	
	void onLoad(QuestTask::QuestState questState) override;
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

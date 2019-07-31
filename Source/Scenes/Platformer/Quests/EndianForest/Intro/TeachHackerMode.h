#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class TeachHackerMode : public QuestTask
{
public:
	static TeachHackerMode* create(GameObject* owner, std::string questLine);

	static const std::string MapKeyQuest;

protected:
	TeachHackerMode(GameObject* owner, std::string questLine);
	~TeachHackerMode();
	
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;
	void enable(bool isSkippable) override;
	void disable() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

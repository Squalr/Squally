#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class Task4 : public QuestTask
{
public:
	static Task4* create(GameObject* owner, std::string questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	Task4(GameObject* owner, std::string questLine, std::string questTag);
	~Task4();
	
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

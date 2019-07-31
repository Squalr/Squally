#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class MeetFlyBot : public QuestTask
{
public:
	static MeetFlyBot* create(GameObject* owner, std::string questLine);

	static const std::string MapKeyQuest;

protected:
	MeetFlyBot(GameObject* owner, std::string questLine);
	~MeetFlyBot();

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

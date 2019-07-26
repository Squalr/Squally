#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class MeetFlyBot : public QuestTask
{
public:
	static MeetFlyBot* create(GameObject* owner);

	static const std::string MapKeyQuest;

protected:
	MeetFlyBot(GameObject* owner);
	~MeetFlyBot();

	void onLoad(QuestTask::QuestState questState) override;
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

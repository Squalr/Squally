#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;
class QuestLine;

class MeetFlyBot : public QuestTask
{
public:
	static MeetFlyBot* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	MeetFlyBot(GameObject* owner, QuestLine* questLine, std::string questTag);
	~MeetFlyBot();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

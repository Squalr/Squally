#pragma once

#include "Engine/Quests/QuestTask.h"

class Blackbeard;
class QuestLine;

class FindSail : public QuestTask
{
public:
	static FindSail* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	FindSail(GameObject* owner, QuestLine* questLine);
	~FindSail();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Blackbeard* blackbeard;
};

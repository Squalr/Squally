#pragma once

#include "Engine/Quests/QuestTask.h"

class Blackbeard;
class QuestLine;

class RescueGuano : public QuestTask
{
public:
	static RescueGuano* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	RescueGuano(GameObject* owner, QuestLine* questLine, std::string questTag);
	~RescueGuano();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	Blackbeard* blackbeard;
};

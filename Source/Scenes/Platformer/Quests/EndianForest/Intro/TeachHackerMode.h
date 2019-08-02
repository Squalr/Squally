#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;
class QuestLine;

class TeachHackerMode : public QuestTask
{
public:
	static TeachHackerMode* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	TeachHackerMode(GameObject* owner, QuestLine* questLine, std::string questTag);
	~TeachHackerMode();

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

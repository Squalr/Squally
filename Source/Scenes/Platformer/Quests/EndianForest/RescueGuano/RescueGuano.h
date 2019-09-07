#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QuestLine;
class Squally;

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

	void runRescueSequence();
	void runRescueSequencePt2();

	bool hasRunEvent;
	Guano* guano;
	Squally* squally;

	static const std::string EventMulDoorUnlocked;
};

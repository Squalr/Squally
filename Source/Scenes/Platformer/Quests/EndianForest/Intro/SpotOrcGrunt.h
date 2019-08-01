#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class SpotOrcGrunt : public QuestTask
{
public:
	static SpotOrcGrunt* create(GameObject* owner, std::string questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	SpotOrcGrunt(GameObject* owner, std::string questLine, std::string questTag);
	~SpotOrcGrunt();
	
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

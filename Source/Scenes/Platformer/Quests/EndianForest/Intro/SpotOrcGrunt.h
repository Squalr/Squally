#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class SpotOrcGrunt : public QuestTask
{
public:
	static SpotOrcGrunt* create(GameObject* owner);

	static const std::string MapKeyQuest;

protected:
	SpotOrcGrunt(GameObject* owner);
	~SpotOrcGrunt();
	
	void onLoad(QuestTask::QuestState questState) override;
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

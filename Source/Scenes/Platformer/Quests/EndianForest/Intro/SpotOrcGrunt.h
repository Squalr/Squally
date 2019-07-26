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
	
	void onLoad(bool isQuestActive, bool isQuestActiveAsSkippable, bool isQuestComplete) override;
	void onActivate() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

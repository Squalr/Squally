#pragma once

#include "Engine/Quests/QuestTask.h"

class Scrappy;
class QuestLine;

class SpotTrainingDummy : public QuestTask
{
public:
	static SpotTrainingDummy* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	SpotTrainingDummy(GameObject* owner, QuestLine* questLine);
	virtual ~SpotTrainingDummy();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Scrappy* scrappy;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;
class QuestLine;

class SpotOrcGrunt : public QuestTask
{
public:
	static SpotOrcGrunt* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	SpotOrcGrunt(GameObject* owner, QuestLine* questLine, std::string questTag);
	~SpotOrcGrunt();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

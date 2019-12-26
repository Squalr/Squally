#pragma once

#include "Engine/Quests/QuestTask.h"

class Scrappy;
class Squally;
class QuestLine;

class TownArrival : public QuestTask
{
public:
	static TownArrival* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TownArrival(GameObject* owner, QuestLine* questLine);
	~TownArrival();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Scrappy* scrappy;
	Squally* squally;
};

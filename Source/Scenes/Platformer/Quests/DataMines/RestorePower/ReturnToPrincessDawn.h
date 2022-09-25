#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class PrincessDawn;
class QuestLine;
class Scrappy;
class Squally;

class ReturnToPrincessDawn : public QuestTask
{
public:
	static ReturnToPrincessDawn* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ReturnToPrincessDawn(GameObject* owner, QuestLine* questLine);
	virtual ~ReturnToPrincessDawn();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();

	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	PrincessDawn* princessDawn = nullptr;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QueenLiana;
class QuestLine;
class Scrappy;
class Squally;

class ReturnToQueenAgain : public QuestTask
{
public:
	static ReturnToQueenAgain* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ReturnToQueenAgain(GameObject* owner, QuestLine* questLine);
	virtual ~ReturnToQueenAgain();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Guano* guano;
	QueenLiana* queenLiana;
	Scrappy* scrappy;
	Squally* squally;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QuestLine;
class Scrappy;
class Squally;

class ArriveInAthens : public QuestTask
{
public:
	static ArriveInAthens* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ArriveInAthens(GameObject* owner, QuestLine* questLine);
	virtual ~ArriveInAthens();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();
	void runCinematicSequencePt4();
	void runCinematicSequencePt5();
	void runCinematicSequencePt6();

	Guano* guano;
	Scrappy* scrappy;
	Squally* squally;

	static const std::string TagTownCinematic;
};

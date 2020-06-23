#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Medusa;
class QuestLine;
class Scrappy;
class Squally;

class FightMedusa : public QuestTask
{
public:
	static FightMedusa* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	FightMedusa(GameObject* owner, QuestLine* questLine);
	virtual ~FightMedusa();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePart1();
	void runCinematicSequencePart2();

	Guano* guano;
	Medusa* medusa;
	Scrappy* scrappy;
	Squally* squally;
};

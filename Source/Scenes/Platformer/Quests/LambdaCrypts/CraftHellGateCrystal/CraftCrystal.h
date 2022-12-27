#pragma once

#include "Engine/Quests/QuestTask.h"

class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class CraftCrystal : public QuestTask
{
public:
	static CraftCrystal* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	CraftCrystal(GameObject* owner, QuestLine* questLine);
	virtual ~CraftCrystal();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequenceStrikeZone();

	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};

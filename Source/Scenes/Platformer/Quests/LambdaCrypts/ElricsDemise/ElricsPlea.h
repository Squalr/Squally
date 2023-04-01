#pragma once

#include "Engine/Quests/QuestTask.h"

class Elric;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class Squally;
class ZombieElric;

class ElricsPlea : public QuestTask
{
public:
	static ElricsPlea* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ElricsPlea(GameObject* owner, QuestLine* questLine);
	virtual ~ElricsPlea();

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
	Elric* elric = nullptr;
	ZombieElric* zombieElric = nullptr;
};

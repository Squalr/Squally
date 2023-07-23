#pragma once

#include "Engine/Quests/QuestTask.h"

class Elric;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class Squally;
class ZombieElric;

class ElricsDemise : public QuestTask
{
public:
	static ElricsDemise* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ElricsDemise(GameObject* owner, QuestLine* questLine);
	virtual ~ElricsDemise();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
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

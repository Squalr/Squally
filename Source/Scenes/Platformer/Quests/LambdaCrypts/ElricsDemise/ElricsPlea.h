#pragma once

#include "Engine/Quests/QuestTask.h"

class Elric;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class Squally;
class Zombie;
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
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void setPostText();

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();
	void runCinematicSequencePt4();
	void runCinematicSequencePt5();
	void runCinematicSequencePt6();

	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Elric* elric = nullptr;
	Zombie* zombie = nullptr;
};

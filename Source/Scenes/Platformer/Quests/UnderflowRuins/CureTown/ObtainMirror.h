#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class GuanoPetrified;
class Inventory;
class QuestLine;
class Scrappy;
class Squally;

class ObtainMirror : public QuestTask
{
public:
	static ObtainMirror* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ObtainMirror(GameObject* owner, QuestLine* questLine);
	virtual ~ObtainMirror();

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
	void regainGuano();
	void attachGuanoSpawnBehaviors();

	GuanoPetrified* guanoPetrified;
	Scrappy* scrappy;
	Guano* guano;
	Squally* squally;
	Inventory* inventory;

	bool doBehaviorAttach;
};

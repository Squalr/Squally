#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class GuanoPetrified;
class Inventory;
class Portal;
class QuestLine;
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

	void runCinematicSequence();
	void freeGuano();
	void regainGuano();
	void attachGuanoSpawnBehaviors();

	GuanoPetrified* guanoPetrified;
	Guano* guano;
	Squally* squally;
	Inventory* inventory;

	bool doBehaviorAttach;
};

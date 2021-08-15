#pragma once

#include "Engine/Quests/QuestTask.h"

class AnimationPart;
class InteractObject;
class Inventory;
class QuestLine;
class Ram;
class Scrappy;
class Squally;
class Sound;
class WorldSound;

class RepairRam : public QuestTask
{
public:
	static RepairRam* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	RepairRam(GameObject* owner, QuestLine* questLine);
	virtual ~RepairRam();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runDialogue();
	void refreshWheels();
	void onRamInteract();
	void runCinematicSequence();

	Ram* ram = nullptr;
	InteractObject* repairInteract = nullptr;
	AnimationPart* wheel1 = nullptr;
	AnimationPart* wheel2 = nullptr;
	AnimationPart* wheel3 = nullptr;
	Sound* impactSound = nullptr;
	WorldSound* rollSound = nullptr;

	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Inventory* inventory = nullptr;

	bool wasActivated = false;

	static const std::string WheelFoundCount;
};

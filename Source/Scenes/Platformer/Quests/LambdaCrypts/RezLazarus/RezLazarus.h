#pragma once

#include "Engine/Quests/QuestTask.h"

class AnimationPart;
class InteractObject;
class Inventory;
class QuestLine;
class Scrappy;
class Squally;
class Sound;
class WorldSound;

class RezLazarus : public QuestTask
{
public:
	static RezLazarus* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	RezLazarus(GameObject* owner, QuestLine* questLine);
	virtual ~RezLazarus();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runDialogue();
	void refreshGems();
	void onRamInteract();
	void runCinematicSequence();

	InteractObject* repairInteract = nullptr;
	GameObject* displayGemRed = nullptr;
	GameObject* displayGemPurple = nullptr;
	GameObject* displayGemBlue = nullptr;

	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Inventory* inventory = nullptr;

	bool wasActivated = false;

	static const std::string TurnedInGemCount;
	static const std::string GemTurnedInRed;
	static const std::string GemTurnedInPurple;
	static const std::string GemTurnedInBlue;
};

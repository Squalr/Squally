#pragma once

#include "Engine/Quests/QuestTask.h"

class AnimationPart;
class InteractObject;
class Inventory;
class Lazarus;
class QuestLine;
class Scrappy;
class Squally;
class Sound;
class Warp;
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
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runDialogue();
	void refreshGems();
	void onRezInteract();
	void runCinematicSequence();

	InteractObject* rezInteract = nullptr;
	GameObject* displayGemRed = nullptr;
	GameObject* displayGemPurple = nullptr;
	GameObject* displayGemBlue = nullptr;

	std::vector<Warp*> lazarusWarps;

	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Lazarus* lazarus = nullptr;
	Inventory* inventory = nullptr;

	bool wasActivated = false;

	static const std::string TurnedInGemCount;
	static const std::string GemTurnedInRed;
	static const std::string GemTurnedInPurple;
	static const std::string GemTurnedInBlue;
};

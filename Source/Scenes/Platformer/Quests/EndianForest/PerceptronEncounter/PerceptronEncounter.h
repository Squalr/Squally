#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Perceptron;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class SmartAnimationSequenceNode;
class Sound;
class Squally;

class PerceptronEncounter : public QuestTask
{
public:
	static PerceptronEncounter* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PerceptronEncounter(GameObject* owner, QuestLine* questLine);
	virtual ~PerceptronEncounter();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;
	void update(float dt) override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequenceStrikeZone();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();

	PlatformerEntity* cinematicKillTarget = nullptr;
	Perceptron* perceptron = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	SmartAnimationSequenceNode* lightningStrike = nullptr;
	Sound* lightningSound = nullptr;

	bool sprintActive = false;
	bool isInSafeZone = false;
	bool chaseInProgress = false;
	float elapsedChaseTime = 0.0f;
};

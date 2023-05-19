#pragma once

#include "Engine/Quests/QuestTask.h"

class CameraTarget;
class PlatformerEntity;
class Perceptron;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class SmartAnimationSequenceNode;
class Sound;
class Squally;

class MinesPerceptronEncounter : public QuestTask
{
public:
	static MinesPerceptronEncounter* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	MinesPerceptronEncounter(GameObject* owner, QuestLine* questLine);
	virtual ~MinesPerceptronEncounter();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequenceStrikeZone();

	PlatformerEntity* cinematicKillTarget = nullptr;
	Perceptron* perceptron = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	SmartAnimationSequenceNode* lightningStrike = nullptr;
	Sound* lightningSound = nullptr;
	CameraTarget* cinematicCameraTarget = nullptr;
};

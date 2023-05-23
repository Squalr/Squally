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

class PerceptronFight : public QuestTask
{
public:
	static PerceptronFight* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PerceptronFight(GameObject* owner, QuestLine* questLine);
	virtual ~PerceptronFight();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();
	void runCinematicSequencePt4();
	void runCinematicSequencePt5();

	Perceptron* perceptron = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	SmartAnimationSequenceNode* lightningStrike = nullptr;
	Sound* lightningSound = nullptr;
};

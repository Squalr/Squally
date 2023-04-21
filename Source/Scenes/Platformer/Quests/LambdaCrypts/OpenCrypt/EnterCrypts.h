#pragma once

#include "Engine/Quests/QuestTask.h"

class Perceptron;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class SmartAnimationSequenceNode;
class Sound;
class Squally;

class EnterCrypts : public QuestTask
{
public:
	static EnterCrypts* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	EnterCrypts(GameObject* owner, QuestLine* questLine);
	virtual ~EnterCrypts();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequenceStrikeZone();

	Perceptron* perceptron = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	SmartAnimationSequenceNode* lightningStrike = nullptr;
	Sound* lightningSound = nullptr;
};

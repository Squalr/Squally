#pragma once

#include "Engine/Quests/QuestTask.h"

class Perceptron;
class QuestLine;
class Scrappy;
class SmartAnimationSequenceNode;
class Sound;
class Squally;

class ThirdEncounter : public QuestTask
{
public:
	static ThirdEncounter* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ThirdEncounter(GameObject* owner, QuestLine* questLine);
	virtual ~ThirdEncounter();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequenceStrikeZone();

	Perceptron* perceptron = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	SmartAnimationSequenceNode* lightningStrike = nullptr;
	Sound* lightningSound = nullptr;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class PerceptronUnarmored;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class SmartAnimationSequenceNode;
class Sound;
class Squally;

class PerceptronFinale : public QuestTask
{
public:
	static PerceptronFinale* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PerceptronFinale(GameObject* owner, QuestLine* questLine);
	virtual ~PerceptronFinale();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();

	PerceptronUnarmored* perceptron = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};

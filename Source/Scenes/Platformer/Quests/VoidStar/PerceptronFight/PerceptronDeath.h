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

class PerceptronDeath : public QuestTask
{
public:
	static PerceptronDeath* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PerceptronDeath(GameObject* owner, QuestLine* questLine);
	virtual ~PerceptronDeath();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	PerceptronUnarmored* perceptron = nullptr;
};

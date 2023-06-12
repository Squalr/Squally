#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Perceptron;
class Portal;
class Squally;
class WorldSound;

class PerceptronEscape : public QuestTask
{
public:
	static PerceptronEscape* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PerceptronEscape(GameObject* owner, QuestLine* questLine);
	virtual ~PerceptronEscape();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();

	Perceptron* perceptron = nullptr;
	Squally* squally = nullptr;
	Portal* exitPortal = nullptr;
};

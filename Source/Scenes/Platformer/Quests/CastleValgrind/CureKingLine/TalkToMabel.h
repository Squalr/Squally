#pragma once

#include "Engine/Quests/QuestTask.h"

class CameraStop;
class CollisionObject;
class Perceptron;
class Gecky;
class Guano;
class Mabel;
class QuestLine;
class Scrappy;
class Squally;

class TalkToMabel : public QuestTask
{
public:
	static TalkToMabel* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToMabel(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToMabel();

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
	void runCinematicSequencePt6();
	void runCinematicSequencePt7();

	Perceptron* perceptron = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Mabel* mabel = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	CameraStop* cameraStop = nullptr;
	CollisionObject* wall = nullptr;

	static const std::string MapEventMabelRevealed;
};

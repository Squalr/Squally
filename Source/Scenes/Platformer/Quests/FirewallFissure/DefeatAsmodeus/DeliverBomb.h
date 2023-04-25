#pragma once

#include "Engine/Quests/QuestTask.h"

class CameraTarget;
class FloatingBomb;
class Gecky;
class Guano;
class LavaFall;
class Scaldor;
class QuestLine;
class Scrappy;
class Squally;

class DeliverBomb : public QuestTask
{
public:
	static DeliverBomb* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DeliverBomb(GameObject* owner, QuestLine* questLine);
	virtual ~DeliverBomb();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();

	Guano* guano = nullptr;
	Gecky* gecky = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Scaldor* scaldor = nullptr;
	FloatingBomb* floatingBomb = nullptr;
	Sound* explosionSound = nullptr;

	CameraTarget* cinematicFocus = nullptr;
	LavaFall* cinematicLavaFall = nullptr;
};

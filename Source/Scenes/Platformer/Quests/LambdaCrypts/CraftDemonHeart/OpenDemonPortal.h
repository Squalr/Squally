#pragma once

#include "Engine/Quests/QuestTask.h"

class Gecky;
class Guano;
class HellGate;
class QuestLine;
class Scrappy;
class Squally;

class OpenDemonPortal : public QuestTask
{
public:
	static OpenDemonPortal* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	OpenDemonPortal(GameObject* owner, QuestLine* questLine);
	virtual ~OpenDemonPortal();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequenceStrikeZone();

	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	HellGate* hellGate = nullptr;
};

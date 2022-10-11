#pragma once

#include "Engine/Quests/QuestTask.h"

class Irmik;
class Portal;
class QuestLine;
class Scrappy;
class Squally;

class RescueIrmik : public QuestTask
{
public:
	static RescueIrmik* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	RescueIrmik(GameObject* owner, QuestLine* questLine);
	virtual ~RescueIrmik();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePart1();
	void runCinematicSequencePart2();
	void runCinematicSequencePart3();
	void runCinematicSequencePart4();

	Irmik* irmik = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Portal* cutscenePortal = nullptr;

	static const std::string MapEventIrmikRescued;
	static const std::string TagIrmikExit;
	static const std::string TagCutscenePortal;
};

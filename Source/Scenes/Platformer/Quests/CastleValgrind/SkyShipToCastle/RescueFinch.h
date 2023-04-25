#pragma once

#include "Engine/Quests/QuestTask.h"

class Finch;
class Portal;
class QuestLine;
class Scrappy;
class Squally;

class RescueFinch : public QuestTask
{
public:
	static RescueFinch* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	RescueFinch(GameObject* owner, QuestLine* questLine);
	virtual ~RescueFinch();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePart1();
	void runCinematicSequencePart2();
	void runCinematicSequencePart3();
	void runCinematicSequencePart4();

	Finch* finch = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Portal* cutscenePortal = nullptr;

	static const std::string MapEventFinchRescued;
	static const std::string TagFinchExit;
	static const std::string TagCutscenePortal;
};

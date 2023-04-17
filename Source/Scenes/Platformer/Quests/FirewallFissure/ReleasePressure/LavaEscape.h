#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Scrappy;
class Squally;

class LavaEscape : public QuestTask
{
public:
	static LavaEscape* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	LavaEscape(GameObject* owner, QuestLine* questLine);
	virtual ~LavaEscape();

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

	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	static const std::string MapEventBeginLavaEvent;
	static const std::string MapEventPressureReleased;
	static const std::string MapTagRisingLava;
};

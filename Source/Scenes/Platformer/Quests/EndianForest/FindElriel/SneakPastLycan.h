#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Lycan;
class QuestLine;
class Scrappy;
class Squally;

class SneakPastLycan : public QuestTask
{
public:
	static SneakPastLycan* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	SneakPastLycan(GameObject* owner, QuestLine* questLine);
	virtual ~SneakPastLycan();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Lycan* lycan;
	Squally* squally;
};

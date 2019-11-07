#pragma once

#include "Engine/Quests/QuestTask.h"

class Scrappy;
class QuestLine;

class MeetScrappy : public QuestTask
{
public:
	static MeetScrappy* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	MeetScrappy(GameObject* owner, QuestLine* questLine, std::string questTag);
	~MeetScrappy();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();

	bool hasRunEvent;
	Scrappy* scrappy;

	static const std::string TagScrappyStop;
};

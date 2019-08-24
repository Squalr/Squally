#pragma once

#include "Engine/Quests/QuestTask.h"

class QueenLiana;
class QuestLine;

class TalkToQueen : public QuestTask
{
public:
	static TalkToQueen* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	TalkToQueen(GameObject* owner, QuestLine* questLine, std::string questTag);
	~TalkToQueen();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	QueenLiana* queenLiana;
};

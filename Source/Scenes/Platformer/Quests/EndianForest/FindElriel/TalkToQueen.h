#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QueenLiana;
class QuestLine;
class Scrappy;
class Squally;

class TalkToQueen : public QuestTask
{
public:
	static TalkToQueen* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToQueen(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToQueen();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();
	void setPostText();

	Guano* guano;
	QueenLiana* queenLiana;
	Scrappy* scrappy;
	Squally* squally;
};

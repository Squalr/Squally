#pragma once

#include "Engine/Quests/QuestTask.h"

class Sarude;
class QuestLine;
class Squally;

class TalkToMages : public QuestTask
{
public:
	static TalkToMages* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToMages(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToMages();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Sarude* sarude;
	Squally* squally;
};

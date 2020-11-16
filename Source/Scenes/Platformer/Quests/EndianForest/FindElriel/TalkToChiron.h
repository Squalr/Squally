#pragma once

#include "Engine/Quests/QuestTask.h"

class Chiron;
class QuestLine;
class Squally;

class TalkToChiron : public QuestTask
{
public:
	static TalkToChiron* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToChiron(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToChiron();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Chiron* chiron;
	Squally* squally;
};

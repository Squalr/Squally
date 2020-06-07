#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QuestLine;
class Scrappy;
class Squally;
class Cleopatra;

class TalkToCleopatra : public QuestTask
{
public:
	static TalkToCleopatra* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToCleopatra(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToCleopatra();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();
	void runCinematicSequencePt4();
	void runCinematicSequencePt5();

	Guano* guano;
	Scrappy* scrappy;
	Squally* squally;
	Cleopatra* cleopatra;
};

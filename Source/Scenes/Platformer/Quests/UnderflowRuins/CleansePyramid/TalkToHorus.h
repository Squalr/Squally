#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Horus;
class QuestLine;
class Scrappy;
class Squally;

class TalkToHorus : public QuestTask
{
public:
	static TalkToHorus* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToHorus(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToHorus();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();

	Guano* guano;
	Scrappy* scrappy;
	Squally* squally;
	Horus* horus;
};

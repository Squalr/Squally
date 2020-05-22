#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Aphrodite;
class QuestLine;
class Scrappy;
class Squally;

class TalkToHera : public QuestTask
{
public:
	static TalkToHera* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToHera(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToHera();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Guano* guano;
	Aphrodite* aphrodite;
	Scrappy* scrappy;
	Squally* squally;

	static const std::string TagExitDoor;
};

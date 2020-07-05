#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Aphrodite;
class QuestLine;
class Scrappy;
class Squally;

class TalkToAphrodite : public QuestTask
{
public:
	static TalkToAphrodite* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToAphrodite(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToAphrodite();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();
	void runShipmentsComplete();

	Guano* guano;
	Aphrodite* aphrodite;
	Scrappy* scrappy;
	Squally* squally;

	static const std::string TagExitDoor;
	static const std::string SaveKeyItemGiven;
};

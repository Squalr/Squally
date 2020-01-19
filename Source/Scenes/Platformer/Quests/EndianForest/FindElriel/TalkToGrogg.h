#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class KingGrogg;
class QuestLine;
class Scrappy;
class Squally;

class TalkToGrogg : public QuestTask
{
public:
	static TalkToGrogg* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToGrogg(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToGrogg();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Guano* guano;
	KingGrogg* kingGrogg;
	Scrappy* scrappy;
	Squally* squally;
};

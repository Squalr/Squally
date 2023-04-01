#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Amelia;
class QuestLine;
class Scrappy;
class Squally;

class TalkToAmelia : public QuestTask
{
public:
	static TalkToAmelia* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToAmelia(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToAmelia();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Guano* guano = nullptr;
	Amelia* amelia = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};

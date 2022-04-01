#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class Olive;
class QuestLine;
class Scrappy;
class Squally;

class TalkToOlive : public QuestTask
{
public:
	static TalkToOlive* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToOlive(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToOlive();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();

	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Olive* olive = nullptr;
};

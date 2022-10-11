#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class PrincessOpal;
class QuestLine;
class Scrappy;
class Squally;

class TalkToPrincessOpal : public QuestTask
{
public:
	static TalkToPrincessOpal* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToPrincessOpal(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToPrincessOpal();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Guano* guano = nullptr;
	PrincessOpal* princessOpal = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};

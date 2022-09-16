#pragma once

#include "Engine/Quests/QuestTask.h"

class Gecky;
class Guano;
class PrincessDawn;
class QuestLine;
class Scrappy;
class Squally;

class TalkToPrincessDawn : public QuestTask
{
public:
	static TalkToPrincessDawn* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToPrincessDawn(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToPrincessDawn();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();

	Guano* guano = nullptr;
	Gecky* gecky = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	PrincessDawn* princessDawn = nullptr;

	static const std::string MapTagCinematicGecky;
};

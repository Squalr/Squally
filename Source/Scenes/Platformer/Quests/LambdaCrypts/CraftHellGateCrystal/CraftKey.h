#pragma once

#include "Engine/Quests/QuestTask.h"

class Drak;
class Gecky;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class CraftKey : public QuestTask
{
public:
	static CraftKey* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	CraftKey(GameObject* owner, QuestLine* questLine);
	virtual ~CraftKey();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequenceStrikeZone();

	Drak* drak = nullptr;
	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};

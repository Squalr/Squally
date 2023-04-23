#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Asmodeus;
class ScreamingDoor;
class Squally;
class WorldSound;

class DefeatAsmodeus : public QuestTask
{
public:
	static DefeatAsmodeus* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DefeatAsmodeus(GameObject* owner, QuestLine* questLine);
	virtual ~DefeatAsmodeus();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();

	Asmodeus* asmodeus = nullptr;
	Squally* squally = nullptr;

	static const std::string MapEventEngageAsmodeus;
};

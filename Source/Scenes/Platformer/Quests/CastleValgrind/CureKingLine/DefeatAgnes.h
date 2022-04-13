#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Agnes;
class ScreamingDoor;
class Squally;
class WorldSound;

class DefeatAgnes : public QuestTask
{
public:
	static DefeatAgnes* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DefeatAgnes(GameObject* owner, QuestLine* questLine);
	virtual ~DefeatAgnes();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();

	Agnes* agnes = nullptr;
	Squally* squally = nullptr;

	static const std::string MapEventEngageAgnes;
};

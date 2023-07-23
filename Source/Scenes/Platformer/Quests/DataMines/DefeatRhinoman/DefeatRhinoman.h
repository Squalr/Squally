#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Rhinoman;
class ScreamingDoor;
class Squally;
class WorldSound;

class DefeatRhinoman : public QuestTask
{
public:
	static DefeatRhinoman* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DefeatRhinoman(GameObject* owner, QuestLine* questLine);
	virtual ~DefeatRhinoman();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();

	Rhinoman* rhinoman = nullptr;
	Squally* squally = nullptr;
	ScreamingDoor* screamingDoor = nullptr;

	static const std::string MapEventAwakenRhinoman;
};

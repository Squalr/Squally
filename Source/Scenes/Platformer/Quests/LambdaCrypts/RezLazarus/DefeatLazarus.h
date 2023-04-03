#pragma once

#include "Engine/Quests/QuestTask.h"

class Lazarus;
class QuestLine;
class ScreamingDoor;
class Squally;
class WorldSound;

class DefeatLazarus : public QuestTask
{
public:
	static DefeatLazarus* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DefeatLazarus(GameObject* owner, QuestLine* questLine);
	virtual ~DefeatLazarus();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Lazarus* lazarus = nullptr;
	Squally* squally = nullptr;
};

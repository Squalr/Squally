#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class ScreamingDoor;
class Squally;
class WorldSound;
class ZombieElric;

class DefeatElric : public QuestTask
{
public:
	static DefeatElric* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DefeatElric(GameObject* owner, QuestLine* questLine);
	virtual ~DefeatElric();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	ZombieElric* zombieElric = nullptr;
	Squally* squally = nullptr;
};

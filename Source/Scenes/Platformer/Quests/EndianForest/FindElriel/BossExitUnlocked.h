#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;
class Squally;

class BossExitUnlocked : public QuestTask
{
public:
	static BossExitUnlocked* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	BossExitUnlocked(GameObject* owner, QuestLine* questLine);
	virtual ~BossExitUnlocked();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal = nullptr;
};

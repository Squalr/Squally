#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;

class LianaDoorLocked : public QuestTask
{
public:
	static LianaDoorLocked* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	LianaDoorLocked(GameObject* owner, QuestLine* questLine);
	virtual ~LianaDoorLocked();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal;
};

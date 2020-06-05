#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;

class PowerWarpGateCV : public QuestTask
{
public:
	static PowerWarpGateCV* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateCV(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateCV();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal;
};

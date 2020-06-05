#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;

class PowerWarpGateEF : public QuestTask
{
public:
	static PowerWarpGateEF* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateEF(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateEF();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal;
};

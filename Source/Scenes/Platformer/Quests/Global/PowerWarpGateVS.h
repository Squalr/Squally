#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Portal;
class QuestLine;
class Trigger;

class PowerWarpGateVS : public QuestTask
{
public:
	static PowerWarpGateVS* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateVS(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateVS();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal;
	Trigger* trigger;
	PlatformerEntity* mage;
};

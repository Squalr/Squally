#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Portal;
class QuestLine;
class Trigger;

class PowerWarpGateLC : public QuestTask
{
public:
	static PowerWarpGateLC* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateLC(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateLC();

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

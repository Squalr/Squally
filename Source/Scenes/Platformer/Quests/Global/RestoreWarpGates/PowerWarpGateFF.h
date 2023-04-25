#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Portal;
class QuestLine;
class Trigger;

class PowerWarpGateFF : public QuestTask
{
public:
	static PowerWarpGateFF* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateFF(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateFF();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal = nullptr;
	Trigger* trigger = nullptr;
	PlatformerEntity* mage = nullptr;
};

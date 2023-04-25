#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Portal;
class QuestLine;
class Squally;
class Trigger;

class PowerWarpGateUR : public QuestTask
{
public:
	static PowerWarpGateUR* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateUR(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateUR();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Portal* portal = nullptr;
	Trigger* trigger = nullptr;
	PlatformerEntity* mage = nullptr;
	Squally* squally = nullptr;
};

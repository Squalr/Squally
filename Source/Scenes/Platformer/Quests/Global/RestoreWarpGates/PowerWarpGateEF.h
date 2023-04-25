#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Portal;
class QuestLine;
class Squally;
class Trigger;

class PowerWarpGateEF : public QuestTask
{
public:
	static PowerWarpGateEF* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateEF(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateEF();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Portal* portal = nullptr;
	Trigger* trigger = nullptr;
	Squally* squally = nullptr;
	PlatformerEntity* mage = nullptr;
};

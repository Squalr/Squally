#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;

class PowerWarpGateDM : public QuestTask
{
public:
	static PowerWarpGateDM* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	PowerWarpGateDM(GameObject* owner, QuestLine* questLine);
	virtual ~PowerWarpGateDM();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal;
};

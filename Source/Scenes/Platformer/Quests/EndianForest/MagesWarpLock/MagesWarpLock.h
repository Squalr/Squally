#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;
class Squally;

class MagesWarpLock : public QuestTask
{
public:
	static MagesWarpLock* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	MagesWarpLock(GameObject* owner, QuestLine* questLine);
	virtual ~MagesWarpLock();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal = nullptr;
	Squally* squally = nullptr;
};

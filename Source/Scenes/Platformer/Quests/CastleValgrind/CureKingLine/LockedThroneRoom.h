#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;
class Squally;

class LockedThroneRoom : public QuestTask
{
public:
	static LockedThroneRoom* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	LockedThroneRoom(GameObject* owner, QuestLine* questLine);
	virtual ~LockedThroneRoom();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Portal* portal = nullptr;
	Squally* squally = nullptr;
};

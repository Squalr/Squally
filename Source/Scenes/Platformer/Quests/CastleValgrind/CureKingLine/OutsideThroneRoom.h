#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class Squally;
class QuestLine;
class Tyracius;

class OutsideThroneRoom : public QuestTask
{
public:
	static OutsideThroneRoom* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	OutsideThroneRoom(GameObject* owner, QuestLine* questLine);
	virtual ~OutsideThroneRoom();
	
	void onEnter() override;
	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void attachTyraciusBehavior();

	Portal* cryptDoor = nullptr;
	Tyracius* tyracius = nullptr;
	Squally* squally = nullptr;
};

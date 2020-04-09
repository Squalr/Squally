#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;
class Squally;

class BusinessHours : public QuestTask
{
public:
	static BusinessHours* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	BusinessHours(GameObject* owner, QuestLine* questLine);
	virtual ~BusinessHours();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Portal* portal;
	Squally* squally;
};

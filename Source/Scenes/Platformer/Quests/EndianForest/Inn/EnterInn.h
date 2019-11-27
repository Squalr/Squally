#pragma once

#include "Engine/Quests/QuestTask.h"

class Portal;
class QuestLine;
class Squally;

class EnterInn : public QuestTask
{
public:
	static EnterInn* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	EnterInn(GameObject* owner, QuestLine* questLine, std::string questTag);
	~EnterInn();

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

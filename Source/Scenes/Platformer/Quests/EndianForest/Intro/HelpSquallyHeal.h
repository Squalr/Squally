#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class HelpSquallyHeal : public QuestTask
{
public:
	static HelpSquallyHeal* create(GameObject* owner);

	static const std::string MapKeyQuest;

protected:
	HelpSquallyHeal(GameObject* owner);
	~HelpSquallyHeal();
	
	void onLoad(QuestTask::QuestState questState) override;
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

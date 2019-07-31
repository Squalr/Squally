#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;

class HelpSquallyHeal : public QuestTask
{
public:
	static HelpSquallyHeal* create(GameObject* owner, std::string questLine);

	static const std::string MapKeyQuest;

protected:
	HelpSquallyHeal(GameObject* owner, std::string questLine);
	~HelpSquallyHeal();
	
	void onStateChange(QuestTask::QuestState questState, QuestTask::QuestState questStatePrevious) override;
	void onActivateRunOnce() override;
	void enable(bool isSkippable) override;
	void disable() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

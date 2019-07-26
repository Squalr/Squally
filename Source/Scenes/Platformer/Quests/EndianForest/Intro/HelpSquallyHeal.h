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
	
	void onLoad(bool isQuestActive, bool isQuestActiveAsSkippable, bool isQuestComplete) override;
	void onActivate() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

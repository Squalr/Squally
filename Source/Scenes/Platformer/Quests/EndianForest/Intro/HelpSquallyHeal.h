#pragma once

#include "Engine/Quests/QuestTask.h"

class FlyBot;
class QuestLine;

class HelpSquallyHeal : public QuestTask
{
public:
	static HelpSquallyHeal* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	HelpSquallyHeal(GameObject* owner, QuestLine* questLine, std::string questTag);
	~HelpSquallyHeal();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	bool hasRunEvent;
	FlyBot* flyBot;
};

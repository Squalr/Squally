#pragma once

#include "Engine/Quests/QuestTask.h"

class Marcel;
class QuestLine;
class Squally;

class WelcomeToMagesGuild : public QuestTask
{
public:
	static WelcomeToMagesGuild* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WelcomeToMagesGuild(GameObject* owner, QuestLine* questLine);
	virtual ~WelcomeToMagesGuild();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;
	
	void runCinematicSequence();

	Marcel* marcel;
	Squally* squally;
};

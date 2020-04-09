#pragma once

#include "Engine/Quests/QuestTask.h"

class Marcel;
class QuestLine;
class Squally;

class WindSpellbook : public QuestTask
{
public:
	static WindSpellbook* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WindSpellbook(GameObject* owner, QuestLine* questLine);
	virtual ~WindSpellbook();

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

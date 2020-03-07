#pragma once

#include "Engine/Quests/QuestTask.h"

class Marcel;
class QuestLine;
class Squally;

class WindBlessing : public QuestTask
{
public:
	static WindBlessing* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	WindBlessing(GameObject* owner, QuestLine* questLine);
	virtual ~WindBlessing();

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

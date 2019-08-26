#pragma once

#include "Engine/Quests/QuestTask.h"

class CollisionObject;
class Lycan;
class QuestLine;
class Squally;

class PersuadeGuard : public QuestTask
{
public:
	static PersuadeGuard* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	PersuadeGuard(GameObject* owner, QuestLine* questLine, std::string questTag);
	~PersuadeGuard();
	
	void onEnter() override;
	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runNoVisitorsSequence();

	CollisionObject* solidWall;
	Lycan* lycan;
	Squally* squally;

	static const std::string QuestTagPrison;
	static const std::string QuestTagSolidWall;
	static const std::string QuestTagInn;
};

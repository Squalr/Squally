#pragma once

#include "Engine/Quests/QuestTask.h"

class CollisionObject;
class Lycan;
class MulDoor;
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
	void runPersuasionSequencePart1a();
	void runPersuasionSequencePart1b();
	void runPersuasionSequencePart1c();
	void runPersuasionSequencePart2a();
	void runPersuasionSequencePart2b();
	void runPersuasionSequencePart2c();

	bool hasRunPersuasionSequence;
	CollisionObject* solidWall;
	MulDoor* mulDoor;
	Lycan* lycan;
	Squally* squally;

	static const std::string QuestTagInn;
	static const std::string TagSolidWall;
	static const std::string TagPrisonDoor;
	static const std::string TagExit;
	static const std::string EventExplainDoor;
};

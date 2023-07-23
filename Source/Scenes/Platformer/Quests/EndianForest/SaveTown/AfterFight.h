#pragma once

#include "Engine/Quests/QuestTask.h"

class MagePortal;
class Sarude;
class Scrappy;
class QuestLine;
class Squally;

class AfterFight : public QuestTask
{
public:
	static AfterFight* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	AfterFight(GameObject* owner, QuestLine* questLine);
	virtual ~AfterFight();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void despawnMages();
	void runCinematicSequencePart1();
	void runCinematicSequencePart2();

	Sarude* sarude = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	MagePortal* magePortal = nullptr;

	static const std::string TagQuestPortal;
};

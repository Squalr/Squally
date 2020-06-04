#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Osiris;
class Sarcophagus;
class Squally;

class DefeatOsiris : public QuestTask
{
public:
	static DefeatOsiris* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	DefeatOsiris(GameObject* owner, QuestLine* questLine);
	virtual ~DefeatOsiris();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();

	Osiris* osiris;
	Squally* squally;
	Sarcophagus* sarcophagus;

	static const std::string MapEventAwakenOsiris;
	static const std::string TagExitPortal;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class Scrappy;
class Squally;
class QuestLine;
class WorldSound;

class MeetScrappy : public QuestTask
{
public:
	static MeetScrappy* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	MeetScrappy(GameObject* owner, QuestLine* questLine);
	virtual ~MeetScrappy();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();
	void runCinematicSequencePt4();

	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	WorldSound* droidAlarmedSound = nullptr;

	static const std::string TagScrappyStop;
};

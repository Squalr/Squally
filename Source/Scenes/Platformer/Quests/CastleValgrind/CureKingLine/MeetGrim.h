#pragma once

#include "Engine/Quests/QuestTask.h"

class Gecky;
class Grim;
class Guano;
class QuestLine;
class Scrappy;
class Squally;

class MeetGrim : public QuestTask
{
public:
	static MeetGrim* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	MeetGrim(GameObject* owner, QuestLine* questLine);
	virtual ~MeetGrim();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();
	void runCinematicSequencePt4();

	Gecky* gecky = nullptr;
	Guano* guano = nullptr;
	Grim* grim = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	static const std::string MapEventMeetGrim;
	static const std::string MapTagCinematicGrim;
};

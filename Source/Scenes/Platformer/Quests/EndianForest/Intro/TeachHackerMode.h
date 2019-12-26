#pragma once

#include "Engine/Quests/QuestTask.h"

class HelpTotem;
class MagePortal;
class Marcel;
class QuestLine;
class Scrappy;
class Squally;
class WorldSound;

class TeachHackerMode : public QuestTask
{
public:
	static TeachHackerMode* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TeachHackerMode(GameObject* owner, QuestLine* questLine);
	~TeachHackerMode();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();

	HelpTotem* helpTotem;
	Scrappy* scrappy;
	Squally* squally;
	
	static const std::string TagHelpTotemHacking;
};

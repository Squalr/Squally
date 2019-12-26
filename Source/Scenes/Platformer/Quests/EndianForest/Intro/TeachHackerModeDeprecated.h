#pragma once

#include "Engine/Quests/QuestTask.h"

class HelpTotem;
class MagePortal;
class Marcel;
class QuestLine;
class Squally;
class WorldSound;

class TeachHackerModeDeprecated : public QuestTask
{
public:
	static TeachHackerModeDeprecated* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TeachHackerModeDeprecated(GameObject* owner, QuestLine* questLine);
	~TeachHackerModeDeprecated();

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
	void runCinematicSequencePt5();
	
	HelpTotem* helpTotem;
	MagePortal* portal;
	Marcel* marcel;
	Squally* squally;
	WorldSound* teleportSound;
	
	static const std::string TagQuestPortal;
	static const std::string TagHelpTotemHacking;
};

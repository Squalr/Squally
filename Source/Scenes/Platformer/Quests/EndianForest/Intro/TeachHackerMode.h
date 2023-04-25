#pragma once

#include "Engine/Quests/QuestTask.h"

class HelpTotem;
class QuestLine;
class Scrappy;
class Squally;

class TeachHackerMode : public QuestTask
{
public:
	static TeachHackerMode* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TeachHackerMode(GameObject* owner, QuestLine* questLine);
	virtual ~TeachHackerMode();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();

	HelpTotem* helpTotem = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	
	static const std::string TagHelpTotemHacking;
};

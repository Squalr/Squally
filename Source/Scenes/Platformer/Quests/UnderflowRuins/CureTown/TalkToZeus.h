#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QuestLine;
class Scrappy;
class Squally;
class Zeus;

class TalkToZeus : public QuestTask
{
public:
	static TalkToZeus* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToZeus(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToZeus();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();

	Guano* guano;
	Scrappy* scrappy;
	Squally* squally;
	Zeus* zeus;

	static const std::string TagTownCinematic;
};

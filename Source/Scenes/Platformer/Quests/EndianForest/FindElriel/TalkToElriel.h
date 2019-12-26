#pragma once

#include "Engine/Quests/QuestTask.h"

class Elriel;
class PlatformerEntity;
class QuestLine;
class Scrappy;
class Squally;

class TalkToElriel : public QuestTask
{
public:
	static TalkToElriel* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToElriel(GameObject* owner, QuestLine* questLine);
	~TalkToElriel();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePart1();
	void runCinematicSequencePart2();
	void runCinematicSequencePart3();
	void runCinematicSequencePart4();

	Elriel* elriel;
	Scrappy* scrappy;
	Squally* squally;

	static const std::string TagElrielExit;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QuestLine;
class MulDoor;
class Scrappy;
class Squally;

class BeatTutorialA : public QuestTask
{
public:
	static BeatTutorialA* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	BeatTutorialA(GameObject* owner, QuestLine* questLine, std::string questTag);
	~BeatTutorialA();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runChatSequence();
	void runChatSequencePt2();
	void runChatSequencePt3();
	void runChatSequencePt4();

	bool hasRunEvent;
	Guano* guano;
	Scrappy* scrappy;
	Squally* squally;
	MulDoor* mulDoor;
};

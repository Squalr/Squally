#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class QuestLine;
class MulDoor;
class Squally;

class ChatWithGuano : public QuestTask
{
public:
	static ChatWithGuano* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	ChatWithGuano(GameObject* owner, QuestLine* questLine, std::string questTag);
	~ChatWithGuano();

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
	Squally* squally;
	MulDoor* mulDoor;
};

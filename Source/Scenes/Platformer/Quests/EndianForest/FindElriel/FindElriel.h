#pragma once

#include "Engine/Quests/QuestTask.h"

class Blackbeard;
class QuestLine;

class FindElriel : public QuestTask
{
public:
	static FindElriel* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	FindElriel(GameObject* owner, QuestLine* questLine, std::string questTag);
	~FindElriel();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequence();

	Blackbeard* blackbeard;
};

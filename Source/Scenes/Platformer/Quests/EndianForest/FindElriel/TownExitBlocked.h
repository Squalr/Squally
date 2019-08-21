#pragma once

#include "Engine/Quests/QuestTask.h"

class Chiron;
class QuestLine;

class TownExitBlocked : public QuestTask
{
public:
	static TownExitBlocked* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	TownExitBlocked(GameObject* owner, QuestLine* questLine, std::string questTag);
	~TownExitBlocked();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	Chiron* chiron;
};

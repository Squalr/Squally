#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class PlatformerEntity;
class Squally;

class KillTheTroll : public QuestTask
{
public:
	static KillTheTroll* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	KillTheTroll(GameObject* owner, QuestLine* questLine, std::string questTag);
	~KillTheTroll();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	PlatformerEntity* troll;
	Squally* squally;
};

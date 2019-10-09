#pragma once

#include "Engine/Quests/QuestTask.h"

class QuestLine;
class Sarude;
class Squally;

class TalkToSarude : public QuestTask
{
public:
	static TalkToSarude* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	TalkToSarude(GameObject* owner, QuestLine* questLine, std::string questTag);
	~TalkToSarude();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void registerDialogue();

	Sarude* sarude;
	Squally* squally;
};

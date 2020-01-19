#pragma once

#include "Engine/Quests/QuestTask.h"

class MagePortal;
class QuestLine;
class Sarude;
class Squally;

class TalkToSarude : public QuestTask
{
public:
	static TalkToSarude* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToSarude(GameObject* owner, QuestLine* questLine);
	virtual ~TalkToSarude();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void registerDialogue();

	MagePortal* portal;
	Sarude* sarude;
	Squally* squally;

	static const std::string QuestPortalTag;
};

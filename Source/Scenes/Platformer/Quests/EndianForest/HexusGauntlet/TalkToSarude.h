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
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void registerDialogue();

	MagePortal* portal = nullptr;
	Sarude* sarude = nullptr;
	Squally* squally = nullptr;

	static const std::string QuestPortalTag;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class MagePortal;
class QuestLine;
class Marcel;
class Squally;

class TalkToMarcel : public QuestTask
{
public:
	static TalkToMarcel* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	TalkToMarcel(GameObject* owner, QuestLine* questLine);
	~TalkToMarcel();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void registerDialogue();

	MagePortal* portal;
	Marcel* marcel;
	Squally* squally;

	static const std::string QuestPortalTag;
};

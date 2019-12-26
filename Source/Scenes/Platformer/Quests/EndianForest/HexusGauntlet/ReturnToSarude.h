#pragma once

#include "Engine/Quests/QuestTask.h"

class MagePortal;
class QuestLine;
class Sarude;
class Squally;

class ReturnToSarude : public QuestTask
{
public:
	static ReturnToSarude* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	ReturnToSarude(GameObject* owner, QuestLine* questLine);
	~ReturnToSarude();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void registerDialogue(bool isActiveThroughSkippable);
	void onHexusWin();
	void onHexusLoss();
	void runPostHexusMatchCleanup();
	void runDialogueIntroWin();
	void runDialogueIntroLoss();
	void runDialogueOutro();

	MagePortal* portal;
	Sarude* sarude;
	Squally* squally;

	static const std::string QuestPortalTag;
};

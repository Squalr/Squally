#pragma once

#include "Engine/Quests/QuestTask.h"

class MagePortal;
class QuestLine;
class Marcel;
class Squally;

class ReturnToMarcel : public QuestTask
{
public:
	static ReturnToMarcel* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	ReturnToMarcel(GameObject* owner, QuestLine* questLine, std::string questTag);
	~ReturnToMarcel();

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
	Marcel* marcel;
	Squally* squally;

	static const std::string QuestPortalTag;
};

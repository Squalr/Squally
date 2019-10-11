#pragma once

#include "Engine/Quests/QuestTask.h"

class HexusOpponentData;
class MagePortal;
class Necron;
class QuestLine;
class Squally;

class BeatTutorialC : public QuestTask
{
public:
	static BeatTutorialC* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	BeatTutorialC(GameObject* owner, QuestLine* questLine, std::string questTag);
	~BeatTutorialC();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void registerDialogue();
	HexusOpponentData* createOpponentData();

	void onWin();
	void onLoss();

	MagePortal* portal;
	Necron* necron;
	Squally* squally;

	static const std::string QuestPortalTag;
	static const std::string WinLossTrackIdentifier;
};

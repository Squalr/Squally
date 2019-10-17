#pragma once

#include "Engine/Quests/QuestTask.h"

class HexusOpponentData;
class MagePortal;
class PlatformerEntity;
class QuestLine;
class Squally;

class BeatTutorialE : public QuestTask
{
public:
	static BeatTutorialE* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	BeatTutorialE(GameObject* owner, QuestLine* questLine, std::string questTag);
	~BeatTutorialE();

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
	PlatformerEntity* mage;
	Squally* squally;

	static const std::string QuestPortalTag;
	static const std::string WinLossTrackIdentifier;
};

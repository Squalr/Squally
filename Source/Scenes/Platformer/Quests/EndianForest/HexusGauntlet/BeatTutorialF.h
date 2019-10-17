#pragma once

#include "Engine/Quests/QuestTask.h"

class HexusOpponentData;
class Igneus;
class MagePortal;
class PlatformerEntity;
class QuestLine;
class Squally;

class BeatTutorialF : public QuestTask
{
public:
	static BeatTutorialF* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	BeatTutorialF(GameObject* owner, QuestLine* questLine, std::string questTag);
	~BeatTutorialF();

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

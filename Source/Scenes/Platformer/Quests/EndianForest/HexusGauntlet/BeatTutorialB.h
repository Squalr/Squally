#pragma once

#include "Engine/Quests/QuestTask.h"

class Aster;
class HexusOpponentData;
class MagePortal;
class QuestLine;
class Squally;

class BeatTutorialB : public QuestTask
{
public:
	static BeatTutorialB* create(GameObject* owner, QuestLine* questLine, std::string questTag);

	static const std::string MapKeyQuest;

protected:
	BeatTutorialB(GameObject* owner, QuestLine* questLine, std::string questTag);
	~BeatTutorialB();

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
	Aster* aster;
	Squally* squally;

	static const std::string QuestPortalTag;
	static const std::string WinLossTrackIdentifier;
};

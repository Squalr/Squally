#pragma once

#include "Engine/Quests/QuestTask.h"

class Alder;
class HexusOpponentData;
class Igneus;
class MagePortal;
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
	Igneus* igneus;
	Squally* squally;

	static const std::string QuestPortalTag;
	static const std::string WinLossTrackIdentifier;
};

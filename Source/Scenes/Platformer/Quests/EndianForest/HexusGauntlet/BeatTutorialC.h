#pragma once

#include "Engine/Quests/QuestTask.h"

class HexusOpponentData;
class MagePortal;
class PlatformerEntity;
class QuestLine;
class Squally;

class BeatTutorialC : public QuestTask
{
public:
	static BeatTutorialC* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	BeatTutorialC(GameObject* owner, QuestLine* questLine);
	~BeatTutorialC();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	MagePortal* portal;
	PlatformerEntity* mage;
	Squally* squally;

	static const std::string QuestPortalTag;
	static const std::string WinLossTrackIdentifier;
};

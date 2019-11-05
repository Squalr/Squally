#pragma once

#include "Engine/Quests/QuestTask.h"

class HexusOpponentData;
class MagePortal;
class PlatformerEntity;
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

	MagePortal* portal;
	PlatformerEntity* mage;
	Squally* squally;

	static const std::string QuestPortalTag;
	static const std::string WinLossTrackIdentifier;
};

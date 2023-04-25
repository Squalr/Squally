#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Portal;
class QuestLine;
class Squally;

class SkyShipUnlocked : public QuestTask
{
public:
	static SkyShipUnlocked* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	SkyShipUnlocked(GameObject* owner, QuestLine* questLine);
	virtual ~SkyShipUnlocked();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runNoSequence();
	void runYesSequence();

	PlatformerEntity* owner = nullptr;
	Squally* squally = nullptr;
	Portal* portal = nullptr;
	bool isReturnTrip = false;
	
	static const std::string PropertyIsReturnTrip;
	static const std::string QuestTagShipPortal;
	static const std::string QuestTagTempleAirship;
};

#pragma once

#include "Engine/Quests/QuestTask.h"

class PlatformerEntity;
class Portal;
class QuestLine;
class Squally;

class IrmikRescued : public QuestTask
{
public:
	static IrmikRescued* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	IrmikRescued(GameObject* owner, QuestLine* questLine);
	virtual ~IrmikRescued();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runYesSequence();

	PlatformerEntity* owner = nullptr;
	Squally* squally = nullptr;
	Portal* portal = nullptr;
	bool isReturnTrip = false;
	
	static const std::string PropertyIsReturnTrip;
	static const std::string QuestTagShipPortal;
};

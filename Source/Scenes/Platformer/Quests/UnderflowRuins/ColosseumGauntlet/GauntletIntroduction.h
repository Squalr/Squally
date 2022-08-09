#pragma once

#include "Engine/Quests/QuestTask.h"

class Guano;
class PlatformerEntity;
class QuestLine;
class Scrappy;
class Squally;
class Cleopatra;

class GauntletIntroduction : public QuestTask
{
public:
	static GauntletIntroduction* create(GameObject* owner, QuestLine* questLine);

	static const std::string MapKeyQuest;

protected:
	GauntletIntroduction(GameObject* owner, QuestLine* questLine);
	virtual ~GauntletIntroduction();

	void onLoad(QuestState questState) override;
	void onActivate(bool isActiveThroughSkippable) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();

	std::vector<PlatformerEntity*> guards;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Cleopatra* cleopatra = nullptr;
	CinematicMarker* guardTeleportMarker = nullptr;
	CinematicMarker* guardDestinationMarker = nullptr;
	CinematicMarker* squallyDestinationMarker = nullptr;

	static const std::string TagGuard;
	static const std::string TagGuardTeleport;
	static const std::string TagGuardDestination;
	static const std::string TagSquallyDestination;
};

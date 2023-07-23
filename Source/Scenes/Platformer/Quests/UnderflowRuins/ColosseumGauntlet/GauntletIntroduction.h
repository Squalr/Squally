#pragma once

#include "Engine/Quests/QuestTask.h"

class CinematicMarker;
class GatlingGun;
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
	void onActivate(bool isActiveThroughSkippable, bool isInitialActivation) override;
	void onComplete() override;
	void onSkipped() override;

private:
	typedef QuestTask super;

	void runCinematicSequencePt1();
	void runCinematicSequencePt2();
	void runCinematicSequencePt3();

	std::vector<PlatformerEntity*> guards;
	GatlingGun* gatlingGun = nullptr;
	Guano* guano = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	Cleopatra* cleopatra = nullptr;
	CinematicMarker* guardTeleportMarker = nullptr;
	CinematicMarker* guardArriveMarker = nullptr;
	CinematicMarker* guardLeaveMarker = nullptr;
	CinematicMarker* squallyDestinationMarker = nullptr;

	static const std::string TagGuard;
	static const std::string TagGuardTeleport;
	static const std::string TagGuardArrive;
	static const std::string TagGuardLeave;
	static const std::string TagSquallyDestination;
	static const std::string MapEventBeginGauntlet;
};

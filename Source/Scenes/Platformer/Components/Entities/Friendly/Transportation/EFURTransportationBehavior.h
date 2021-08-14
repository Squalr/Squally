#pragma once

#include "Engine/Components/GameComponent.h"

class DialogueSet;
class PlatformerEntity;
class Portal;
class Scrappy;
class Squally;

class EFURTransportationBehavior : public GameComponent
{
public:
	static EFURTransportationBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EFURTransportationBehavior(GameObject* owner);
	virtual ~EFURTransportationBehavior();

	void onLoad() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	DialogueSet* innerChoices = nullptr;

	Portal* backPortal = nullptr;
	Portal* leavePortal = nullptr;

	static const std::string QuestTagBackPortal;
	static const std::string QuestTagLeavePortal;
};

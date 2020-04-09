#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class DialogueSet;
class PlatformerEntity;
class Portal;
class Scrappy;
class Squally;

class EFURTransportationBehavior : public AttachedBehavior
{
public:
	static EFURTransportationBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EFURTransportationBehavior(GameObject* owner);
	virtual ~EFURTransportationBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
	DialogueSet* innerChoices;

	Portal* backPortal;
	Portal* leavePortal;

	static const std::string QuestTagBackPortal;
	static const std::string QuestTagLeavePortal;
};

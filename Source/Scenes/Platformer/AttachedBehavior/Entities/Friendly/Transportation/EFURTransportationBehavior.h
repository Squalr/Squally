#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class DialogueSet;
class PlatformerEntity;
class Scrappy;
class Squally;

class EFURTransportationBehavior : public AttachedBehavior
{
public:
	static EFURTransportationBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EFURTransportationBehavior(GameObject* owner);
	virtual ~EFURTransportationBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void rebuildDialogue();

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
	DialogueSet* innerChoices;
};

#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Scrappy;
class PlatformerEntity;
class PlatformerEntityDeserializer;

class ScrappyCombatManagerBehavior : public AttachedBehavior
{
public:
	static ScrappyCombatManagerBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyCombatManagerBehavior(GameObject* owner);
	virtual ~ScrappyCombatManagerBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void spawnScrappy();

	PlatformerEntity* entity;
	Scrappy* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
};

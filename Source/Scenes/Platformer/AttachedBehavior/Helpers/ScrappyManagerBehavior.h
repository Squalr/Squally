#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Scrappy;
class PlatformerEntity;
class PlatformerEntityDeserializer;

class ScrappyManagerBehavior : public AttachedBehavior
{
public:
	static ScrappyManagerBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	ScrappyManagerBehavior(GameObject* owner);
	~ScrappyManagerBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void spawnScrappy();

	PlatformerEntity* entity;
	Scrappy* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
};

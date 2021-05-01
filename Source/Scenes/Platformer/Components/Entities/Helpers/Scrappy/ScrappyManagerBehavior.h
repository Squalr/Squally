#pragma once

#include "Engine/Components/Component.h"

class Scrappy;
class PlatformerEntity;
class PlatformerEntityDeserializer;

class ScrappyManagerBehavior : public Component
{
public:
	static ScrappyManagerBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ScrappyManagerBehavior(GameObject* owner);
	virtual ~ScrappyManagerBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void spawnScrappy();

	PlatformerEntity* entity;
	Scrappy* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
};

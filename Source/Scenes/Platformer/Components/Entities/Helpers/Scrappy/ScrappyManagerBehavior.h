#pragma once

#include "Engine/Components/GameComponent.h"

class Scrappy;
class PlatformerEntity;
class PlatformerEntityDeserializer;

class ScrappyManagerBehavior : public GameComponent
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
	typedef GameComponent super;

	void spawnScrappy();

	PlatformerEntity* entity;
	Scrappy* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
};

#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class FlyBot;
class PlatformerEntity;
class PlatformerEntityDeserializer;

class FlyBotManagerBehavior : public AttachedBehavior
{
public:
	static FlyBotManagerBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FlyBotManagerBehavior(GameObject* owner);
	~FlyBotManagerBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void spawnFlyBot();

	PlatformerEntity* entity;
	FlyBot* helperRef;
	PlatformerEntityDeserializer* platformerEntityDeserializer;
};

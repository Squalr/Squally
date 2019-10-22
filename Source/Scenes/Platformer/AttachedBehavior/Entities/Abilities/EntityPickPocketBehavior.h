#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class PocketPoolDeserializer;
class Squally;

class EntityPickPocketBehavior : public AttachedBehavior
{
public:
	static EntityPickPocketBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityPickPocketBehavior(GameObject* owner);
	~EntityPickPocketBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void attemptPickPocket();

	PlatformerEntity* entity;
	Squally* squally;
	PocketPoolDeserializer* pocketPoolDeserializer;

	std::string currentHelperName;

	static const std::string MapKeyPocketPool;
};

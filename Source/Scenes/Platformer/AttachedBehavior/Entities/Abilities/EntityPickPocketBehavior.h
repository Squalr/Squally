#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class MinMaxPool;
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
	bool wasPickPocketed();

	PlatformerEntity* entity;
	Squally* squally;
	MinMaxPool* pocketPool;
	PocketPoolDeserializer* pocketPoolDeserializer;

	std::string currentHelperName;

	static const std::string SavePropertyKeyWasPickPocketed;
	static const std::string MapKeyPocketPool;
};

#include "SpawnPoolEF.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/Collectables/ManaOrb.h"

using namespace cocos2d;

const std::string SpawnPoolEF::MapKey = "spawn-pool-ef";

SpawnPoolEF* SpawnPoolEF::create(ValueMap& properties)
{
	SpawnPoolEF* instance = new SpawnPoolEF(properties);

	instance->autorelease();

	return instance;
}

SpawnPoolEF::SpawnPoolEF(ValueMap& properties) : super(properties)
{
}

SpawnPoolEF::~SpawnPoolEF()
{
}

Collectable* SpawnPoolEF::spawnCollectable()
{
	ValueMap spawnProperties = ValueMap();

	return ManaOrb::create(spawnProperties);
}

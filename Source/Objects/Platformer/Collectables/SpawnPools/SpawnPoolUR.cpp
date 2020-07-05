#include "SpawnPoolUR.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/Collectables/IOUDrop.h"
#include "Objects/Platformer/Collectables/ManaOrb.h"

using namespace cocos2d;

const std::string SpawnPoolUR::MapKey = "spawn-pool-ur";

SpawnPoolUR* SpawnPoolUR::create(ValueMap& properties)
{
	SpawnPoolUR* instance = new SpawnPoolUR(properties);

	instance->autorelease();

	return instance;
}

SpawnPoolUR::SpawnPoolUR(ValueMap& properties) : super(properties)
{
	this->addSpawnEvent(SpawnObjectEvent(0.50f, [=]()
	{
		ValueMap spawnProperties = ValueMap();
		return ManaOrb::create(spawnProperties);
	}));

	this->addSpawnEvent(SpawnObjectEvent(0.35f, [=]()
	{
		ValueMap spawnProperties = ValueMap();
		return IOUDrop::create(spawnProperties);
	}));
}

SpawnPoolUR::~SpawnPoolUR()
{
}

#include "SpawnPool.h"

#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Save/SaveManager.h"

#include "Objects/Platformer/Collectables/Collectable.h"

using namespace cocos2d;

const std::string SpawnPool::MapKeySpawnPool = "spawn-pool";
const std::string SpawnPool::SaveKeySpawnCollected = "SPAWN_POOL_COLLECTED";

SpawnPool::SpawnPool(ValueMap& properties) : super(properties)
{
	this->owner = nullptr;
}

SpawnPool::~SpawnPool()
{
}

void SpawnPool::onEnter()
{
	super::onEnter();
}

void SpawnPool::setOwner(GameObject* owner)
{
	this->owner = owner;
}

void SpawnPool::trySpawnCollectable()
{
	if (this->isCollected())
	{
		return;
	}

	Collectable* collectable = this->spawnCollectable();

	if (collectable == nullptr)
	{
		return;
	}
	
	collectable->setCollectCooldown();
	
	collectable->onCollected([=]()
	{
		this->saveCollected();
	});

	ObjectEvents::TriggerObjectSpawn(ObjectEvents::RequestObjectSpawnArgs(
		this,
		collectable,
		ObjectEvents::SpawnMethod::Above,
		ObjectEvents::PositionMode::SetToOwner,
		[&]()
		{
		},
		[&]()
		{
		}
	));
}

void SpawnPool::saveCollected()
{
	this->owner->saveTemporalObjectState(SpawnPool::SaveKeySpawnCollected, Value(true));
}

bool SpawnPool::isCollected()
{
	return this->owner->loadObjectStateOrDefault(SpawnPool::SaveKeySpawnCollected, Value(false)).asBool();
}
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
	this->spawnEvents = std::vector<SpawnObjectEvent>();
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

	collectable->onCollected([=]()
	{
		this->saveCollected();
	});

	ObjectEvents::TriggerObjectSpawn(RequestObjectSpawnArgs(
		this,
		collectable,
		SpawnMethod::Above,
		PositionMode::SetToOwner,
		[&]()
		{
		},
		[&]()
		{
		}
	));
}

void SpawnPool::addSpawnEvent(SpawnObjectEvent spawnEvent)
{
	this->spawnEvents.push_back(spawnEvent);
}

Collectable* SpawnPool::spawnCollectable()
{
	static float BadLuck = 0.0f;
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(this->spawnEvents.begin(), this->spawnEvents.end(), g);

	for (auto next : this->spawnEvents)
	{
		float rng = RandomHelper::random_real(0.0f, 1.0f) + BadLuck;

		if (rng >= (1.0f - next.probability))
		{
			BadLuck = 0.0f;

			return next.spawnFunc();
		}
	}

	BadLuck = BadLuck <= 0.0f ? 0.01f : BadLuck * 2.0f;

	return nullptr;
}


void SpawnPool::saveCollected()
{
	this->owner->saveTemporalObjectState(SpawnPool::SaveKeySpawnCollected, Value(true));
}

bool SpawnPool::isCollected()
{
	return this->owner->loadObjectStateOrDefault(SpawnPool::SaveKeySpawnCollected, Value(false)).asBool();
}
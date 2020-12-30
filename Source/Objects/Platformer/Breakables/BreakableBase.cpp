#include "BreakableBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Deserializers/Platformer/PlatformerObjectDeserializer.h"
#include "Objects/Platformer/Collectables/SpawnPools/SpawnPool.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

BreakableBase::BreakableBase(ValueMap& properties, Size collisionSize, int requiredHits) : super(properties)
{
	this->breakableCollision = CollisionObject::create(CollisionObject::createBox(collisionSize), (CollisionType)(PlatformerCollisionType::Breakable), CollisionObject::Properties(false, false));
	this->objectDeserializer = PlatformerObjectDeserializer::create();
	this->contentNode = Node::create();
	this->hasBroke = false;
	this->spawnPool = nullptr;

	ValueMap spawnPoolProperties = ValueMap();
	spawnPoolProperties[GameObject::MapKeyName] = GameUtils::getKeyOrDefault(this->properties, SpawnPool::MapKeySpawnPool, Value(""));

	this->objectDeserializer->deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs(spawnPoolProperties, [=](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		this->spawnPool = dynamic_cast<SpawnPool*>(args.gameObject);

		if (this->spawnPool != nullptr)
		{
			this->spawnPool->setOwner(this);

			this->addChild(this->spawnPool);
		}
	}));

	this->addChild(this->contentNode);
	this->addChild(this->breakableCollision);
	this->addChild(this->objectDeserializer);
}

BreakableBase::~BreakableBase()
{
}

void BreakableBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void BreakableBase::initializePositions()
{
	super::initializePositions();
}

void BreakableBase::initializeListeners()
{
	super::initializeListeners();

	this->breakableCollision->whenCollidesWith({(int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData data)
	{
		if (!this->hasBroke)
		{
			this->hasBroke = true;
			this->onBreak();
		}

		this->breakableCollision->setPhysicsEnabled(false);

		return CollisionResult::DoNothing;
	});
}

void BreakableBase::onBreak()
{
	SpawnPool* spawnPool = this->getSpawnPool();

	if (spawnPool != nullptr)
	{
		spawnPool->trySpawnCollectable();
	}
}

SpawnPool* BreakableBase::getSpawnPool()
{
	return this->spawnPool;
}

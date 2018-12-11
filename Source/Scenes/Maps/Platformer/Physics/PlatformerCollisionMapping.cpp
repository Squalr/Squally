#include "PlatformerCollisionMapping.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Physics/CollisionObject.h"

using namespace cocos2d;

const std::string PlatformerCollisionMapping::KeyCollisionTypeSolid = "solid";
const std::string PlatformerCollisionMapping::KeyCollisionTypePassThrough = "pass-through";
const std::string PlatformerCollisionMapping::KeyCollisionTypePlayer = "player";
const std::string PlatformerCollisionMapping::KeyCollisionTypeNpc = "npc";
const std::string PlatformerCollisionMapping::KeyCollisionTypeEnemy = "enemy";
const std::string PlatformerCollisionMapping::KeyCollisionTypeEnemyFlying = "enemy-flying";
const std::string PlatformerCollisionMapping::KeyCollisionTypeForce = "force";
const std::string PlatformerCollisionMapping::KeyCollisionTypeSolidNpc = "solid-npc";
const std::string PlatformerCollisionMapping::KeyCollisionTypeSolidNpcFlying = "solid-npc-flying";
const std::string PlatformerCollisionMapping::KeyCollisionTypeWater = "water";
const std::string PlatformerCollisionMapping::KeyCollisionTypeLava = "lava";

PlatformerCollisionMapping* PlatformerCollisionMapping::instance = nullptr;

void PlatformerCollisionMapping::registerGlobalNode()
{
	if (PlatformerCollisionMapping::instance == nullptr)
	{
		PlatformerCollisionMapping::instance = new PlatformerCollisionMapping();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(PlatformerCollisionMapping::instance);
	}
}

PlatformerCollisionMapping::PlatformerCollisionMapping()
{
}

PlatformerCollisionMapping::~PlatformerCollisionMapping()
{
}

void PlatformerCollisionMapping::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* mapRequestEventListener = EventListenerCustom::create(
		CollisionObject::RequestCollisionMappingEvent,
		CC_CALLBACK_1(PlatformerCollisionMapping::onMapRequest, this));

	this->addEventListener(mapRequestEventListener);
}

void PlatformerCollisionMapping::onMapRequest(EventCustom* eventCustom)
{
	CollisionObject::CollisionMapRequestArgs* args = (CollisionObject::CollisionMapRequestArgs*)(eventCustom->getUserData());

	if (args == nullptr || args->collisionObject == nullptr)
	{
		return;
	}

	if (args->deserializedCollisionName == KeyCollisionTypeSolid)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Solid);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypePassThrough)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::PassThrough);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypePlayer)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Player);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeNpc)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::FriendlyNpc);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeEnemy)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Enemy);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeEnemyFlying)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::EnemyFlying);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeForce)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Force);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeSolidNpc)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::SolidNpcOnly);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeSolidNpcFlying)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::SolidFlyingNpcOnly);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeWater)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Water);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeLava)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Lava);
	}
}

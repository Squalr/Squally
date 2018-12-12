#include "PlatformerCollisionMapping.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Physics/CollisionObject.h"

using namespace cocos2d;

const std::string PlatformerCollisionMapping::MapKeyCollisionTypeSolid = "solid";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypePassThrough = "pass-through";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypePlayer = "player";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeNpc = "npc";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeEnemy = "enemy";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeEnemyFlying = "enemy-flying";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeForce = "force";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeSolidNpc = "solid-npc";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeSolidNpcFlying = "solid-npc-flying";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeWater = "water";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeLava = "lava";

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

	EventListenerCustom* allowedCollisionsMappingRequestEventListener = EventListenerCustom::create(
		CollisionMappingEvents::RequestAllowedCollisionMappingEvent,
		CC_CALLBACK_1(PlatformerCollisionMapping::onAllowedCollisionsMapRequest, this));

	EventListenerCustom* mapKeyMappingRequestEventListener = EventListenerCustom::create(
		CollisionMappingEvents::RequestCollisionMapKeyMappingEvent,
		CC_CALLBACK_1(PlatformerCollisionMapping::onMapKeyMappingRequest, this));

	this->addEventListener(allowedCollisionsMappingRequestEventListener);
	this->addEventListener(mapKeyMappingRequestEventListener);
}

void PlatformerCollisionMapping::onAllowedCollisionsMapRequest(EventCustom* eventCustom)
{
	CollisionMappingEvents::AllowedCollisionsRequestArgs* args = (CollisionMappingEvents::AllowedCollisionsRequestArgs*)(eventCustom->getUserData());

	switch ((PlatformerCollisionType)args->collisionObject->getCollisionType())
	{
		case PlatformerCollisionType::Solid:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::FriendlyNpc,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Force,
			});

			break;
		}
		case PlatformerCollisionType::PassThrough:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::FriendlyNpc,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Force,
			});

			break;
		}
		case PlatformerCollisionType::Player:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::FriendlyNpc,
				(int)PlatformerCollisionType::Force,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Solid,
				(int)PlatformerCollisionType::PassThrough,
				(int)PlatformerCollisionType::Water,
				(int)PlatformerCollisionType::Lava,
			});

			break;
		}
		case PlatformerCollisionType::FriendlyNpc:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::Force,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Solid,
				(int)PlatformerCollisionType::PassThrough,
				(int)PlatformerCollisionType::Water,
				(int)PlatformerCollisionType::Lava,
			});

			break;
		}
		case PlatformerCollisionType::Enemy:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Force,
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Solid,
				(int)PlatformerCollisionType::PassThrough,
				(int)PlatformerCollisionType::Water,
				(int)PlatformerCollisionType::Lava,
			});

			break;
		}
		case PlatformerCollisionType::EnemyFlying:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Force,
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Solid,
				(int)PlatformerCollisionType::PassThrough,
				(int)PlatformerCollisionType::Water,
				(int)PlatformerCollisionType::Lava,
			});

			break;
		}
		case PlatformerCollisionType::Force:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Force,
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Solid,
				(int)PlatformerCollisionType::PassThrough,
				(int)PlatformerCollisionType::Water,
				(int)PlatformerCollisionType::Lava,
			});

			break;
		}
		case PlatformerCollisionType::SolidNpcOnly:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::FriendlyNpc,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
			});

			break;
		}
		case PlatformerCollisionType::SolidFlyingNpcOnly:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::EnemyFlying,
			});

			break;
		}
		case PlatformerCollisionType::Water:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::FriendlyNpc,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Force,
			});

			break;
		}
		case PlatformerCollisionType::Lava:
		{
			args->collisionObject->allowCollisionWith({
				(int)PlatformerCollisionType::Player,
				(int)PlatformerCollisionType::FriendlyNpc,
				(int)PlatformerCollisionType::Enemy,
				(int)PlatformerCollisionType::EnemyFlying,
				(int)PlatformerCollisionType::Force,
			});

			break;
		}
		default:
		{
			break;
		}
	}
}

void PlatformerCollisionMapping::onMapKeyMappingRequest(EventCustom* eventCustom)
{
	CollisionMappingEvents::CollisionMapRequestArgs* args = (CollisionMappingEvents::CollisionMapRequestArgs*)(eventCustom->getUserData());

	if (args == nullptr || args->collisionObject == nullptr)
	{
		return;
	}

	if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeSolid)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Solid);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypePassThrough)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::PassThrough);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypePlayer)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Player);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeNpc)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::FriendlyNpc);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeEnemy)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Enemy);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeEnemyFlying)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::EnemyFlying);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeForce)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Force);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeSolidNpc)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::SolidNpcOnly);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeSolidNpcFlying)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::SolidFlyingNpcOnly);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeWater)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Water);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeLava)
	{
		args->collisionObject->setCollisionType((int)PlatformerCollisionType::Lava);
	}
}

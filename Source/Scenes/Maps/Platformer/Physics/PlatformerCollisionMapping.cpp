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
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Player,
			(int)CollisionType::G_Npc,
			(int)CollisionType::G_Enemy,
			(int)CollisionType::G_EnemyFlying,
			(int)CollisionType::G_Force,
		});

		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_Solid,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypePassThrough)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Player,
			(int)CollisionType::G_Npc,
			(int)CollisionType::G_Enemy,
			(int)CollisionType::G_EnemyFlying,
			(int)CollisionType::G_Force,
		});

		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_PassThrough,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypePlayer)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Force,
			(int)CollisionType::G_EnemyFlying,
			(int)CollisionType::G_Solid,
			(int)CollisionType::G_PassThrough,
			(int)CollisionType::G_SolidNpc,
			(int)CollisionType::G_Lava,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_Player,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeNpc)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Solid,
			(int)CollisionType::G_PassThrough,
			(int)CollisionType::G_SolidNpc,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_Npc,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeEnemy)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Player,
			(int)CollisionType::G_Solid,
			(int)CollisionType::G_PassThrough,
			(int)CollisionType::G_SolidNpc,
			(int)CollisionType::G_Lava,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_Enemy,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeEnemyFlying)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Player,
			(int)CollisionType::G_Solid,
			(int)CollisionType::G_PassThrough,
			(int)CollisionType::G_SolidNpc,
			(int)CollisionType::G_SolidFlyingNpc,
			(int)CollisionType::G_Lava,
		});

		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_EnemyFlying,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeForce)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Player,
			(int)CollisionType::G_Solid,
			(int)CollisionType::G_PassThrough,
			(int)CollisionType::G_SolidNpc,
			(int)CollisionType::G_SolidFlyingNpc,
			(int)CollisionType::G_Lava,
		});

		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_Force,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeSolidNpc)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Npc,
			(int)CollisionType::G_Enemy,
			(int)CollisionType::G_EnemyFlying,
		});

		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_SolidNpc,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeSolidNpcFlying)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_EnemyFlying,
		});

		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_SolidFlyingNpc,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeWater)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Player,
			(int)CollisionType::G_Npc,
			(int)CollisionType::G_Enemy,
			(int)CollisionType::G_EnemyFlying,
			(int)CollisionType::G_Force,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_Water,
			&groups
		);
	}
	else if (args->deserializedCollisionName == KeyCollisionTypeLava)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CollisionType::G_Player,
			(int)CollisionType::G_Npc,
			(int)CollisionType::G_Enemy,
			(int)CollisionType::G_Force,
		});

		args->collisionObject->setCollisionGroups(
			(int)CollisionType::G_Lava,
			&groups
		);
	}
}

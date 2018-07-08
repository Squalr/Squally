#include "PlatformerCollisionMapping.h"

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

void PlatformerCollisionMapping::initializeEventListeners()
{
	EventListenerCustom* mapRequestEventListener = EventListenerCustom::create(
		CollisionObject::RequestCollisionMappingEvent,
		CC_CALLBACK_1(PlatformerCollisionMapping::onMapRequest, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mapRequestEventListener, this);
}

void PlatformerCollisionMapping::onMapRequest(EventCustom* eventCustom)
{
	CollisionObject::CollisionMapRequestArgs* args = (CollisionObject::CollisionMapRequestArgs*)(eventCustom->getUserData());

	if (args == nullptr || args->collisionObject == nullptr)
	{
		return;
	}

	if (args->categoryName == KeyCollisionTypeSolid)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_Solid,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Player,
				CategoryGroupType::G_Npc,
				CategoryGroupType::G_Enemy,
				CategoryGroupType::G_EnemyFlying,
				CategoryGroupType::G_Force,
			}));
	}
	else if (args->categoryName == KeyCollisionTypePassThrough)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_PassThrough,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Player,
				CategoryGroupType::G_Npc,
				CategoryGroupType::G_Enemy,
				CategoryGroupType::G_EnemyFlying,
				CategoryGroupType::G_Force,
				}));
	}
	else if (args->categoryName == KeyCollisionTypePlayer)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_Player,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Force,
				CategoryGroupType::G_EnemyFlying,
				CategoryGroupType::G_Solid,
				CategoryGroupType::G_PassThrough,
				CategoryGroupType::G_SolidNpc,
				CategoryGroupType::G_Lava,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeNpc)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_Npc,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Solid,
				CategoryGroupType::G_PassThrough,
				CategoryGroupType::G_SolidNpc,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeEnemy)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_Enemy,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Player,
				CategoryGroupType::G_Solid,
				CategoryGroupType::G_PassThrough,
				CategoryGroupType::G_SolidNpc,
				CategoryGroupType::G_Lava,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeEnemyFlying)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_EnemyFlying,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Player,
				CategoryGroupType::G_Solid,
				CategoryGroupType::G_PassThrough,
				CategoryGroupType::G_SolidNpc,
				CategoryGroupType::G_SolidFlyingNpc,
				CategoryGroupType::G_Lava,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeForce)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_Force,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Player,
				CategoryGroupType::G_Solid,
				CategoryGroupType::G_PassThrough,
				CategoryGroupType::G_SolidNpc,
				CategoryGroupType::G_SolidFlyingNpc,
				CategoryGroupType::G_Lava,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeSolidNpc)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_SolidNpc,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Npc,
				CategoryGroupType::G_Enemy,
				CategoryGroupType::G_EnemyFlying,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeSolidNpcFlying)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_SolidFlyingNpc,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_EnemyFlying,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeWater)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_Water,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Player,
				CategoryGroupType::G_Npc,
				CategoryGroupType::G_Enemy,
				CategoryGroupType::G_EnemyFlying,
				CategoryGroupType::G_Force,
				}));
	}
	else if (args->categoryName == KeyCollisionTypeLava)
	{
		args->collisionObject->setCollisionGroups(
			CategoryGroupType::G_Lava,
			&std::vector<CategoryGroup>({
				CategoryGroupType::G_Player,
				CategoryGroupType::G_Npc,
				CategoryGroupType::G_Enemy,
				CategoryGroupType::G_EnemyFlying,
				CategoryGroupType::G_Force,
				}));
	}
}

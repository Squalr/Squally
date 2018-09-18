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

void PlatformerCollisionMapping::initializeListeners()
{
	GlobalNode::initializeListeners();

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
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Player,
			(int)CategoryGroupType::G_Npc,
			(int)CategoryGroupType::G_Enemy,
			(int)CategoryGroupType::G_EnemyFlying,
			(int)CategoryGroupType::G_Force,
		});

		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_Solid,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypePassThrough)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Player,
			(int)CategoryGroupType::G_Npc,
			(int)CategoryGroupType::G_Enemy,
			(int)CategoryGroupType::G_EnemyFlying,
			(int)CategoryGroupType::G_Force,
		});

		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_PassThrough,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypePlayer)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Force,
			(int)CategoryGroupType::G_EnemyFlying,
			(int)CategoryGroupType::G_Solid,
			(int)CategoryGroupType::G_PassThrough,
			(int)CategoryGroupType::G_SolidNpc,
			(int)CategoryGroupType::G_Lava,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_Player,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeNpc)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Solid,
			(int)CategoryGroupType::G_PassThrough,
			(int)CategoryGroupType::G_SolidNpc,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_Npc,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeEnemy)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Player,
			(int)CategoryGroupType::G_Solid,
			(int)CategoryGroupType::G_PassThrough,
			(int)CategoryGroupType::G_SolidNpc,
			(int)CategoryGroupType::G_Lava,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_Enemy,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeEnemyFlying)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Player,
			(int)CategoryGroupType::G_Solid,
			(int)CategoryGroupType::G_PassThrough,
			(int)CategoryGroupType::G_SolidNpc,
			(int)CategoryGroupType::G_SolidFlyingNpc,
			(int)CategoryGroupType::G_Lava,
		});

		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_EnemyFlying,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeForce)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Player,
			(int)CategoryGroupType::G_Solid,
			(int)CategoryGroupType::G_PassThrough,
			(int)CategoryGroupType::G_SolidNpc,
			(int)CategoryGroupType::G_SolidFlyingNpc,
			(int)CategoryGroupType::G_Lava,
		});

		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_Force,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeSolidNpc)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Npc,
			(int)CategoryGroupType::G_Enemy,
			(int)CategoryGroupType::G_EnemyFlying,
		});

		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_SolidNpc,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeSolidNpcFlying)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_EnemyFlying,
		});

		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_SolidFlyingNpc,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeWater)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Player,
			(int)CategoryGroupType::G_Npc,
			(int)CategoryGroupType::G_Enemy,
			(int)CategoryGroupType::G_EnemyFlying,
			(int)CategoryGroupType::G_Force,
		});
		
		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_Water,
			&groups
		);
	}
	else if (args->categoryName == KeyCollisionTypeLava)
	{
		std::vector<CategoryGroup> groups = std::vector<CategoryGroup>({
			(int)CategoryGroupType::G_Player,
			(int)CategoryGroupType::G_Npc,
			(int)CategoryGroupType::G_Enemy,
			(int)CategoryGroupType::G_Force,
		});

		args->collisionObject->setCollisionGroups(
			(int)CategoryGroupType::G_Lava,
			&groups
		);
	}
}

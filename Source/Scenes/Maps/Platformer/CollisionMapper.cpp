#include "CollisionMapper.h"

const std::string CollisionMapper::KeyCollisionTypeSolid = "solid";
const std::string CollisionMapper::KeyCollisionTypeWater = "water";
const std::string CollisionMapper::KeyCollisionTypeSolidNpc = "npc";
const std::string CollisionMapper::KeyCollisionTypeSolidNpcFlying = "npc-flying";

CollisionMapper* CollisionMapper::instance = nullptr;

void CollisionMapper::registerGlobalNode()
{
	if (CollisionMapper::instance == nullptr)
	{
		CollisionMapper::instance = new CollisionMapper();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(CollisionMapper::instance);
	}
}


CollisionMapper::CollisionMapper()
{
}

CollisionMapper::~CollisionMapper()
{
}

void CollisionMapper::initializeEventListeners()
{
	EventListenerCustom* mapRequestEventListener = EventListenerCustom::create(
		DeserializationEvents::RequestCollisionMappingEvent,
		CC_CALLBACK_1(CollisionMapper::onMapRequest, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mapRequestEventListener, this);
}

void CollisionMapper::onMapRequest(EventCustom* eventCustom)
{
	DeserializationEvents::CollisionMapRequestArgs* args = (DeserializationEvents::CollisionMapRequestArgs*)(eventCustom->getUserData());

	/*
	if (args->categoryName == KeyCollisionTypeSolid)
	{

	}
	else if (args->categoryName == KeyCollisionTypeWater)
	{

	}
	else if (args->categoryName == KeyCollisionTypeSolidNpc)
	{

	}
	else if (args->categoryName == KeyCollisionTypeSolidNpcFlying)
	{

	}
	*/

	/*
	
	switch (this->categoryGroup)
	{
	case CategoryGroup::G_Solid:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Npc
			| CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Force
			);
	case CategoryGroup::G_PassThrough:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Npc
			| CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Force
			);
	case CategoryGroup::G_Player:
		return (CategoryGroup)(
			CategoryGroup::G_Enemy
			| CategoryGroup::G_Force
			| CategoryGroup::G_EnemyFlying
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_Npc:
		return (CategoryGroup)(
			CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			);
	case CategoryGroup::G_Enemy:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_EnemyFlying:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_SolidFlyingNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_Force:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Solid
			| CategoryGroup::G_PassThrough
			| CategoryGroup::G_SolidNpc
			| CategoryGroup::G_SolidFlyingNpc
			| CategoryGroup::G_Lava
			);
	case CategoryGroup::G_SolidNpc:
		return (CategoryGroup)(
			CategoryGroup::G_Npc
			| CategoryGroup::G_Enemy
			| CategoryGroup::G_EnemyFlying
			);
	case CategoryGroup::G_SolidFlyingNpc:
		return (CategoryGroup)(
			CategoryGroup::G_EnemyFlying
			);
	case CategoryGroup::G_Water:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Enemy
			);
	case CategoryGroup::G_Lava:
		return (CategoryGroup)(
			CategoryGroup::G_Player
			| CategoryGroup::G_Enemy
			);
	default:
		return CategoryGroup::G_None;
	}
	*/
}

#include "PlatformerCollisionMapping.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/CollisionMappingEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Physics/CollisionObject.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string PlatformerCollisionMapping::MapKeyCollisionTypePhysics = "physics";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeSolid = "solid";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypePassThrough = "pass-through";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypePlayer = "player";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypePlayerHover = "player-hover";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeNpc = "npc";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeEnemy = "enemy";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeForce = "force";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeSolidNpc = "solid-npc";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeWater = "water";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeDamage = "damage";

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

	EventListenerCustom* mapKeyMappingRequestEventListener = EventListenerCustom::create(
		CollisionMappingEvents::RequestCollisionMapKeyMappingEvent,
		CC_CALLBACK_1(PlatformerCollisionMapping::onMapKeyMappingRequest, this));

	this->addGlobalEventListener(mapKeyMappingRequestEventListener);
}

void PlatformerCollisionMapping::onMapKeyMappingRequest(EventCustom* eventCustom)
{
	CollisionMappingEvents::CollisionMapRequestArgs* args = (CollisionMappingEvents::CollisionMapRequestArgs*)(eventCustom->getUserData());

	if (args == nullptr || args->callback == nullptr)
	{
		return;
	}

	if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeSolid)
	{
		args->callback((int)PlatformerCollisionType::Solid);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypePassThrough)
	{
		args->callback((int)PlatformerCollisionType::PassThrough);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeSolidNpc)
	{
		args->callback((int)PlatformerCollisionType::SolidNpcOnly);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeForce)
	{
		args->callback((int)PlatformerCollisionType::Force);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeWater)
	{
		args->callback((int)PlatformerCollisionType::Water);
	}
	else if (args->deserializedCollisionName == PlatformerCollisionMapping::MapKeyCollisionTypeDamage)
	{
		args->callback((int)PlatformerCollisionType::Damage);
	}
}

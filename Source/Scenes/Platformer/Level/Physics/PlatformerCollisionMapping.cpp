#include "PlatformerCollisionMapping.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/CollisionMappingEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/LogUtils.h"
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
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeCartStop = "cart-stop";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeKill = "kill";
const std::string PlatformerCollisionMapping::MapKeyCollisionTypeKillAlt = "kill-plane";
std::map<std::string, int> PlatformerCollisionMapping::CollisionMap = std::map<std::string, int>();

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
	this->buildCollisionMap();
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

void PlatformerCollisionMapping::buildCollisionMap()
{
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeSolid] = (int)PlatformerCollisionType::Solid;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypePassThrough] = (int)PlatformerCollisionType::PassThrough;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeSolidNpc] = (int)PlatformerCollisionType::SolidNpcOnly;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeForce] = (int)PlatformerCollisionType::Force;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeWater] = (int)PlatformerCollisionType::Water;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeDamage] = (int)PlatformerCollisionType::Damage;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeCartStop] = (int)PlatformerCollisionType::CartStop;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeKill] = (int)PlatformerCollisionType::KillPlane;
	PlatformerCollisionMapping::CollisionMap[PlatformerCollisionMapping::MapKeyCollisionTypeKillAlt] = (int)PlatformerCollisionType::KillPlane;
}

void PlatformerCollisionMapping::onMapKeyMappingRequest(EventCustom* eventCustom)
{
	CollisionMappingEvents::CollisionMapRequestArgs* args = (CollisionMappingEvents::CollisionMapRequestArgs*)(eventCustom->getData());

	if (args == nullptr || args->callback == nullptr)
	{
		return;
	}

	if (PlatformerCollisionMapping::CollisionMap.contains(args->deserializedCollisionName))
	{
		args->callback(PlatformerCollisionMapping::CollisionMap[args->deserializedCollisionName]);
	}
	else
	{
		LogUtils::logError("Unknown collision type: " + args->deserializedCollisionName);
	}
}

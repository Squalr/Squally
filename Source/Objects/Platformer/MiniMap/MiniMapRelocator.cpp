#include "MiniMapRelocator.h"

#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

const std::string MiniMapRelocator::MapKey = "mini-map-relocator";
const std::string MiniMapRelocator::PropertyPosition = "position";

MiniMapRelocator* MiniMapRelocator::create(ValueMap& properties)
{
	MiniMapRelocator* instance = new MiniMapRelocator(properties);

	instance->autorelease();

	return instance;
}

MiniMapRelocator::MiniMapRelocator(ValueMap& properties) : super(properties)
{
	Size triggerSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->triggerCollision = CollisionObject::create(CollisionObject::createBox(triggerSize), (CollisionType)PlatformerCollisionType::Trigger, CollisionObject::Properties(false, false));
	this->position = GameUtils::getKeyOrDefault(this->properties, MiniMapRelocator::PropertyPosition, Value("")).asString();

	this->addChild(this->triggerCollision);
}

MiniMapRelocator::~MiniMapRelocator()
{
}

void MiniMapRelocator::initializeListeners()
{
	super::initializeListeners();

	this->triggerCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Player }, [=](CollisionData collisionData)
	{
		this->positionMiniMap();

		return CollisionResult::DoNothing;
	});

	this->triggerCollision->whenStopsCollidingWith({ (CollisionType)PlatformerCollisionType::Player }, [=](CollisionData collisionData)
	{
		this->endPositionMiniMap();

		return CollisionResult::DoNothing;
	});
}

void MiniMapRelocator::positionMiniMap()
{
	PlatformerEvents::TriggerRelocateMiniMap(PlatformerEvents::RelocateMiniMapArgs(this->position));
}

void MiniMapRelocator::endPositionMiniMap()
{
	PlatformerEvents::TriggerRelocateMiniMap(PlatformerEvents::RelocateMiniMapArgs("top-right"));
}

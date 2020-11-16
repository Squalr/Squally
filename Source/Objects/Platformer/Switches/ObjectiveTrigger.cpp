#include "ObjectiveTrigger.h"

#include "cocos/base/ccTypes.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Objectives/Objectives.h"

using namespace cocos2d;

const std::string ObjectiveTrigger::MapKey = "objective-trigger";

ObjectiveTrigger* ObjectiveTrigger::create(ValueMap& properties)
{
	ObjectiveTrigger* instance = new ObjectiveTrigger(properties);

	instance->autorelease();

	return instance;
}

ObjectiveTrigger::ObjectiveTrigger(ValueMap& properties) : super(properties)
{
	Size triggerSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->triggerCollision = CollisionObject::create(CollisionObject::createBox(triggerSize), (CollisionType)PlatformerCollisionType::Trigger, CollisionObject::Properties(false, false));

	this->addChild(this->triggerCollision);
}

ObjectiveTrigger::~ObjectiveTrigger()
{
}

void ObjectiveTrigger::initializeListeners()
{
	this->triggerCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerMovement }, [=](CollisionData data)
	{
		Objectives::SetCurrentObjective(this->getSendEvent());

		return CollisionResult::DoNothing;
	});
}

#include "Trigger.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Trigger::MapKeyTrigger = "trigger";

Trigger* Trigger::create(ValueMap& initProperties)
{
	Trigger* instance = new Trigger(initProperties);

	instance->autorelease();

	return instance;
}

Trigger::Trigger(ValueMap& initProperties) : super(initProperties)
{
	Size triggerSize = Size(this->properties.at(SerializableObject::MapKeyWidth).asFloat(), this->properties.at(SerializableObject::MapKeyHeight).asFloat());
	this->triggerCollision = CollisionObject::create(PhysicsBody::createBox(triggerSize), (CollisionType)PlatformerCollisionType::Trigger, false, false);
	this->triggerEventName = GameUtils::getKeyOrDefault(initProperties, SerializableObject::MapKeyEvent, Value("")).asString();
	this->wasActivated = false;

	this->addChild(this->triggerCollision);
}

Trigger::~Trigger()
{
}

void Trigger::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Trigger::initializePositions()
{
	super::initializePositions(); 
}

void Trigger::initializeListeners()
{
	super::initializeListeners();

	this->triggerCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		if (!this->wasActivated)
		{
			this->wasActivated = true;
			ValueMap args = ValueMap();

			ObjectEvents::TriggerBroadCastMapObjectState(this->triggerEventName, args);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Trigger::update(float dt)
{
	super::update(dt);
}

Vec2 Trigger::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Trigger::registerHackables()
{
	super::registerHackables();
}

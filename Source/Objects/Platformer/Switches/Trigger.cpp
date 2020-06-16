#include "Trigger.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Trigger::MapKey = "trigger";
const std::string Trigger::PropertySaveState = "save-state";
const std::string Trigger::PropertyMultiTrip = "multi";

Trigger* Trigger::create(ValueMap& properties)
{
	Trigger* instance = new Trigger(properties);

	instance->autorelease();

	return instance;
}

Trigger::Trigger(ValueMap& properties) : super(properties)
{
	Size triggerSize = Size(this->properties.at(GameObject::MapKeyWidth).asFloat(), this->properties.at(GameObject::MapKeyHeight).asFloat());
	this->triggerCollision = CollisionObject::create(CollisionObject::createBox(triggerSize), (CollisionType)PlatformerCollisionType::Trigger, CollisionObject::Properties(false, false));
	this->saveState = GameUtils::getKeyOrDefault(this->properties, Trigger::PropertySaveState, Value(false)).asBool();
	this->multiTrip = GameUtils::getKeyOrDefault(this->properties, Trigger::PropertyMultiTrip, Value(false)).asBool();
	this->wasActivated = false;

	this->addChild(this->triggerCollision);
}

Trigger::~Trigger()
{
}

void Trigger::onEnter()
{
	super::onEnter();

	if (this->saveState)
	{
		this->wasActivated = this->loadObjectStateOrDefault(Trigger::PropertySaveState, Value(false)).asBool();
	}

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
		if (!this->wasActivated || this->multiTrip)
		{
			this->wasActivated = true;
			
			if (this->saveState)
			{
				this->saveObjectState(Trigger::PropertySaveState, Value(this->wasActivated));
			}
			
			this->broadcastMapEvent(this->getSendEvent(), ValueMap());
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

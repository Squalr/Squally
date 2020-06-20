#include "Trigger.h"

#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

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

void Trigger::onCollide()
{
}

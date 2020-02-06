#include "WoodenGate.h"

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
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const float WoodenGate::DoorOpenDelta = 320.0f;

const std::string WoodenGate::MapKeyWoodenGate = "wooden-gate";

WoodenGate* WoodenGate::create(ValueMap& properties)
{
	WoodenGate* instance = new WoodenGate(properties);

	instance->autorelease();

	return instance;
}

WoodenGate::WoodenGate(ValueMap& properties) : super(properties)
{
	this->bridge2 = Sprite::create(ObjectResources::Doors_WoodStronghold_BRIDGE2);
	this->door = Sprite::create(ObjectResources::Doors_WoodStronghold_FENCE);
	this->doorCollision = CollisionObject::create(PhysicsBody::createBox(Size(96.0f, 420.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);
	this->doorClip = SmartClippingNode::create(this->doorCollision, Rect(Vec2(-64.0f, -312.0f), Size(160.0f, 416.0f)));

	this->isFlipped = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyFlipX, Value(false)).asBool();

	this->bridge2->setFlippedX(this->isFlipped);
	this->door->setFlippedX(this->isFlipped);

	this->doorCollision->addChild(this->door);
	this->addChild(this->doorClip);
	this->addChild(this->bridge2);
}

WoodenGate::~WoodenGate()
{
}

void WoodenGate::onEnter()
{
	super::onEnter();

	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->doorClip));
	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->bridge2));

	this->scheduleUpdate();
}

void WoodenGate::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(this->listenEvent, CC_CALLBACK_1(WoodenGate::onDoorEventTriggered, this));
}

void WoodenGate::initializePositions()
{
	super::initializePositions();

	const Vec2 Shift = Vec2(128.0f, 0.0f);
	const float FlipMultiplier = this->isFlipped ? -1.0f : 1.0f;

	this->door->setPosition(Vec2(0.0f, -32.0f));
	this->doorCollision->setPosition(Vec2(0.0f, -64.0f));
	this->doorClip->setPosition(Vec2(104.0f, 64.0f) + Shift);
	this->bridge2->setPosition(Vec2(80.0f, 112.0f) + Shift);

	this->doorClip->setPositionX(this->doorClip->getPositionX() * FlipMultiplier);
	this->bridge2->setPositionX(this->bridge2->getPositionX() * FlipMultiplier);

	this->doorClosedPosition = this->doorClip->getPositionY();
}

void WoodenGate::update(float dt)
{
	super::update(dt);
}

Vec2 WoodenGate::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void WoodenGate::registerHackables()
{
	super::registerHackables();
}

void WoodenGate::onDoorEventTriggered(cocos2d::ValueMap args)
{
	float progress = GameUtils::getKeyOrDefault(args, SwitchEvents::SwitchArgProgress, Value(0.0f)).asFloat();

	this->doorCollision->setPosition(Vec2(0.0f, this->doorClosedPosition + progress * WoodenGate::DoorOpenDelta));
}

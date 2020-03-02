#include "CastleGate.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/UI/SmartClippingNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const float CastleGate::DoorOpenDelta = 320.0f;

const std::string CastleGate::MapKeyCastleGate = "castle-gate";

CastleGate* CastleGate::create(ValueMap& properties)
{
	CastleGate* instance = new CastleGate(properties);

	instance->autorelease();

	return instance;
}

CastleGate::CastleGate(ValueMap& properties) : super(properties)
{
	this->castleBack = Sprite::create(ObjectResources::Doors_CastleGate_CASTLE_BACK);
	this->bridge1 = Sprite::create(ObjectResources::Doors_CastleGate_BRIDGE_1);
	this->bridge2 = Sprite::create(ObjectResources::Doors_CastleGate_BRIDGE_2);
	this->door = Sprite::create(ObjectResources::Doors_CastleGate_STELL_FENCE);
	this->doorCollision = CollisionObject::create(CollisionObject::createBox(Size(96.0f, 420.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));
	this->doorClip = SmartClippingNode::create(this->doorCollision, Rect(Vec2(-64.0f, -224.0f), Size(160.0f, 416.0f)));
	this->castleDoorFront = Sprite::create(ObjectResources::Doors_CastleGate_CASTLE_FRONT);
	this->castleDoorFront2 = Sprite::create(ObjectResources::Doors_CastleGate_CASTLE_FRONT);

	this->isFlipped = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyFlipX, Value(false)).asBool();

	this->castleBack->setFlippedX(this->isFlipped);
	this->bridge1->setFlippedX(this->isFlipped);
	this->bridge2->setFlippedX(this->isFlipped);
	this->door->setFlippedX(this->isFlipped);
	this->castleDoorFront->setFlippedX(this->isFlipped);
	this->castleDoorFront2->setFlippedX(this->isFlipped);

	this->doorCollision->addChild(this->door);
	this->addChild(this->castleBack);
	this->addChild(this->doorClip);
	this->addChild(this->bridge1);
	this->addChild(this->bridge2);
	this->addChild(this->castleDoorFront2);
	this->addChild(this->castleDoorFront);
}

CastleGate::~CastleGate()
{
}

void CastleGate::onEnter()
{
	super::onEnter();

	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->doorClip));
	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->bridge2));
	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->castleDoorFront2));
	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->castleDoorFront));

	this->scheduleUpdate();
}

void CastleGate::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(this->listenEvent, CC_CALLBACK_1(CastleGate::onDoorEventTriggered, this));
}

void CastleGate::initializePositions()
{
	super::initializePositions();

	Vec2 shift = Vec2(128.0f, 0.0f);
	float flipMultiplier = this->isFlipped ? -1.0f : 1.0f;

	this->castleBack->setPosition(shift);
	this->door->setPosition(Vec2(0.0f, -96.0f));
	this->doorClip->setPosition(Vec2(104.0f, 0.0f) + shift);
	this->bridge1->setPosition(Vec2(-224.0f, 88.0f) + shift);
	this->bridge2->setPosition(Vec2(80.0f, 88.0f) + shift);
	this->castleDoorFront->setPosition(Vec2(0.0f, -64.0f));
	this->castleDoorFront2->setPosition(Vec2(-412.0f, -64.0f));

	this->castleBack->setPositionX(this->castleBack->getPositionX() * flipMultiplier);
	this->doorClip->setPositionX(this->doorClip->getPositionX() * flipMultiplier);
	this->bridge1->setPositionX(this->bridge1->getPositionX() * flipMultiplier);
	this->bridge2->setPositionX(this->bridge2->getPositionX() * flipMultiplier);

	this->castleDoorFront->setPositionX(this->castleDoorFront->getPositionX() * flipMultiplier);
	this->castleDoorFront2->setPositionX(this->castleDoorFront2->getPositionX() * flipMultiplier);

	this->doorClosedPosition = this->doorClip->getPositionY();
}

void CastleGate::update(float dt)
{
	super::update(dt);
}

Vec2 CastleGate::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void CastleGate::registerHackables()
{
	super::registerHackables();
}

void CastleGate::onDoorEventTriggered(cocos2d::ValueMap args)
{
	float progress = GameUtils::getKeyOrDefault(args, SwitchEvents::SwitchArgProgress, Value(0.0f)).asFloat();

	this->doorCollision->setPosition(Vec2(0.0f, this->doorClosedPosition + progress * CastleGate::DoorOpenDelta));
}

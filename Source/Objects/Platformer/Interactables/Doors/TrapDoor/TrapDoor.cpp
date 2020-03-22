#include "TrapDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

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

const float TrapDoor::DoorOpenDelta = 320.0f;
const float TrapDoor::DoorOpenSpeed = 64.0f;

const std::string TrapDoor::MapKey = "trap-door";

TrapDoor* TrapDoor::create(ValueMap& properties)
{
	TrapDoor* instance = new TrapDoor(properties);

	instance->autorelease();

	return instance;
}

TrapDoor::TrapDoor(ValueMap& properties) : super(properties)
{
	this->door = Sprite::create(ObjectResources::Doors_TrapDoor_TrapDoor);
	this->doorCollision = CollisionObject::create(CollisionObject::createBox(Size(256.0f, 80.0f)), (CollisionType)PlatformerCollisionType::Solid, CollisionObject::Properties(false, false));
	this->destinationProgress = 0.0f;

	DrawNode* clipStencil = DrawNode::create();
	clipStencil->drawSolidRect(Vec2(-112.0f, -64.0f), Vec2(112.0f, 48.0f), Color4F::GREEN);
	this->doorClip = ClippingNode::create(clipStencil);

	this->isFlipped = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyFlipX, Value(false)).asBool();

	this->door->setFlippedX(this->isFlipped);

	// Enable to debug clipping:
	// this->doorClip->addChild(clipStencil);

	this->doorClip->addChild(this->doorCollision);
	this->doorCollision->addChild(this->door);
	this->addChild(this->doorClip);
}

TrapDoor::~TrapDoor()
{
}

void TrapDoor::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void TrapDoor::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(this->listenEvent, CC_CALLBACK_1(TrapDoor::onDoorEventTriggered, this));
}

void TrapDoor::initializePositions()
{
	super::initializePositions();

	float flipMultiplier = this->isFlipped ? -1.0f : 1.0f;

	this->door->setPosition(Vec2(0.0f, 0.0f));
	this->doorClip->setPosition(Vec2(0.0f, 0.0f));

	this->doorClip->setPositionX(this->doorClip->getPositionX() * flipMultiplier);

	this->doorClosedPosition = this->doorClip->getPositionX();
}

void TrapDoor::update(float dt)
{
	super::update(dt);

	float currentProgress = MathUtils::clamp((this->doorCollision->getPositionX() - this->doorClosedPosition) / TrapDoor::DoorOpenDelta, 0.0f, 1.0f);
	float direction = currentProgress > this->destinationProgress ? -1.0f : 1.0f;

	if (MathUtils::fuzzyEquals(currentProgress, this->destinationProgress, 0.001f))
	{
		return;
	}

	float offset = currentProgress * TrapDoor::DoorOpenDelta + TrapDoor::DoorOpenSpeed * dt * direction;

	this->doorCollision->setPositionX(this->doorClosedPosition + offset);
}

Vec2 TrapDoor::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void TrapDoor::registerHackables()
{
	super::registerHackables();
}

void TrapDoor::onDoorEventTriggered(cocos2d::ValueMap args)
{
	this->destinationProgress = MathUtils::clamp(GameUtils::getKeyOrDefault(args, SwitchEvents::SwitchArgProgress, Value(0.0f)).asFloat(), 0.0f, 1.0f);
}

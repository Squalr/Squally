#include "CastleDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

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

const float CastleDoor::DoorOpenDelta = 320.0f;

const std::string CastleDoor::MapKeyCastleDoor = "castle-door";

CastleDoor* CastleDoor::create(ValueMap& initProperties)
{
	CastleDoor* instance = new CastleDoor(initProperties);

	instance->autorelease();

	return instance;
}

CastleDoor::CastleDoor(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->castleBack = Sprite::create(ObjectResources::Doors_CastleGate_CASTLE_BACK);
	this->bridge1 = Sprite::create(ObjectResources::Doors_CastleGate_BRIDGE_1);
	this->bridge2 = Sprite::create(ObjectResources::Doors_CastleGate_BRIDGE_2);
	this->door = Sprite::create(ObjectResources::Doors_CastleGate_STELL_FENCE);
	this->doorCollision = CollisionObject::create(PhysicsBody::createBox(Size(96.0f, 420.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);

	DrawNode* clipStencil = DrawNode::create();
	clipStencil->drawSolidRect(Vec2(-64.0f, -224.0f), Vec2(96.0f, 192.0f), Color4F::GREEN);
	this->doorClip = ClippingNode::create(clipStencil);

	this->isFlipped = GameUtils::getKeyOrDefault(initProperties, SerializableObject::MapKeyFlipX, Value(false)).asBool();
	this->doorOpenEventName = GameUtils::getKeyOrDefault(initProperties, SerializableObject::MapKeyEvent, Value("")).asString();

	this->castleBack->setFlippedX(this->isFlipped);
	this->bridge1->setFlippedX(this->isFlipped);
	this->bridge2->setFlippedX(this->isFlipped);
	this->door->setFlippedX(this->isFlipped);

	// Enable to debug clipping:
	// this->doorClip->addChild(clipStencil);

	this->doorClip->addChild(this->doorCollision);
	this->doorCollision->addChild(this->door);
	this->addChild(this->castleBack);
	this->addChild(this->doorClip);
	this->addChild(this->bridge1);
	this->addChild(this->bridge2);
}

CastleDoor::~CastleDoor()
{
}

void CastleDoor::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CastleDoor::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(this->doorOpenEventName, CC_CALLBACK_1(CastleDoor::onDoorEventTriggered, this));
}

void CastleDoor::initializePositions()
{
	super::initializePositions();

	Vec2 shift = Vec2(128.0f, 0.0f);
	float flipMultiplier = this->isFlipped ? -1.0f : 1.0f;

	this->castleBack->setPosition(shift);
	this->door->setPosition(Vec2(0.0f, -96.0f));
	this->doorClip->setPosition(Vec2(104.0f, 0.0f) + shift);
	this->bridge1->setPosition(Vec2(-224.0f, 88.0f) + shift);
	this->bridge2->setPosition(Vec2(80.0f, 88.0f) + shift);

	this->castleBack->setPositionX(this->castleBack->getPositionX() * flipMultiplier);
	this->doorClip->setPositionX(this->doorClip->getPositionX() * flipMultiplier);
	this->bridge1->setPositionX(this->bridge1->getPositionX() * flipMultiplier);
	this->bridge2->setPositionX(this->bridge2->getPositionX() * flipMultiplier);

	this->doorClosedPosition = this->doorClip->getPositionY();
}

void CastleDoor::update(float dt)
{
	super::update(dt);
}

Vec2 CastleDoor::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}

void CastleDoor::registerHackables()
{
	super::registerHackables();
}

void CastleDoor::onDoorEventTriggered(cocos2d::ValueMap args)
{
	float progress = GameUtils::getKeyOrDefault(args, SwitchEvents::SwitchArgProgress, Value(0.0f)).asFloat();

	this->doorCollision->setPosition(Vec2(0.0f, this->doorClosedPosition + progress * CastleDoor::DoorOpenDelta));
}

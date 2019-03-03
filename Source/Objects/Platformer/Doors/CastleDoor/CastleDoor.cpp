#include "CastleDoor.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

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
	this->doorCollision = CollisionObject::create(PhysicsBody::createBox(Size(128.0f, 420.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);

	this->isFlipped = GameUtils::getKeyOrDefault(initProperties, SerializableObject::MapKeyFlipX, Value(false)).asBool();

	this->castleBack->setFlippedX(this->isFlipped);
	this->bridge1->setFlippedX(this->isFlipped);
	this->bridge2->setFlippedX(this->isFlipped);
	this->door->setFlippedX(this->isFlipped);

	this->doorCollision->addChild(this->door);
	this->addChild(this->castleBack);
	this->addChild(this->doorCollision);
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

void CastleDoor::initializePositions()
{
	super::initializePositions();

	Vec2 shift = Vec2(128.0f, 0.0f);
	float flipMultiplier = this->isFlipped ? -1.0f : 1.0f;

	this->castleBack->setPosition(shift);
	this->doorCollision->setPosition(Vec2(112.0f, -64.0f) + shift);
	this->bridge1->setPosition(Vec2(-224.0f, 88.0f) + shift);
	this->bridge2->setPosition(Vec2(80.0f, 88.0f) + shift);

	this->castleBack->setPositionX(this->castleBack->getPositionX() * flipMultiplier);
	this->doorCollision->setPositionX(this->doorCollision->getPositionX() * flipMultiplier);
	this->bridge1->setPositionX(this->bridge1->getPositionX() * flipMultiplier);
	this->bridge2->setPositionX(this->bridge2->getPositionX() * flipMultiplier);
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

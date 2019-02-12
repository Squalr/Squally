#include "Dart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Maps/Platformer/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

#define LOCAL_FUNC_ID_SWING 1

Dart* Dart::create(float rotation, float speed)
{
	Dart* instance = new Dart(rotation, speed);

	instance->autorelease();

	return instance;
}

Dart::Dart(float rotation, float speed) : CollisionObject(ValueMap(),
	PhysicsBody::createBox(
		Size(64.0f, 16.0f),
		PHYSICSBODY_MATERIAL_DEFAULT,
		Vec2::ZERO
	),
	(int)PlatformerCollisionType::Damage,
	false,
	false
)
{
	this->dartSprite = Sprite::create(ObjectResources::War_Machines_Dartgun_DART);
	this->setRotation(rotation);

	float rotationInRad = (-rotation) * M_PI / 180.0f;
	this->setVelocity(Vec2(speed * std::cos(rotationInRad), speed * std::sin(rotationInRad)));

	this->registerHackables();

	this->addChild(this->dartSprite);
}

Dart::~Dart()
{
}

void Dart::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Dart::initializePositions()
{
	super::initializePositions();
}

void Dart::update(float dt)
{
	super::update(dt);
}

void Dart::registerHackables()
{
}

Vec2 Dart::getButtonOffset()
{
	return Vec2(0.0f, 0.0f);
}
